#include "Plugins/PluginsManager.hpp"
#include "Plugins/Plugin.hpp"

#include <QDebug>
#include <QDir>
#include <QLibrary>
#include <QXmlStreamReader>

namespace ege
{

PluginsManager::PluginsManager(QObject* parent)
  : QObject(parent)
{
}

PluginsManager::~PluginsManager()
{
  unloadPlugins();
}

void PluginsManager::loadPlugins(QQmlApplicationEngine& engine)
{
  QDir dir(pluginPath());
  dir.setFilter(QDir::Files | QDir::NoSymLinks);
  dir.setNameFilters(QStringList() << "*.xml");

  // process all plugin definition files
  const auto& fileList = dir.entryInfoList();
  foreach (const auto& fileInfo, fileList)
  {
    qDebug() << Q_FUNC_INFO << QString("Loading plugin definition: %1...").arg(QDir::toNativeSeparators(fileInfo.absoluteFilePath()));

    QFile file(fileInfo.absoluteFilePath());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      // error!
      qWarning() << Q_FUNC_INFO << "Could not open plugin xml file" << QDir::toNativeSeparators(fileInfo.absoluteFilePath());
      continue;
    }

    auto pluginData = std::make_unique<PluginData>();

    QXmlStreamReader stream(&file);
    while (!stream.atEnd())
    {
      QXmlStreamReader::TokenType token = stream.readNext();
      switch (token)
      {
        case QXmlStreamReader::StartElement:
          if (QString::fromLatin1("plugin") == stream.name())
          {
            pluginData->name = stream.attributes().value(QString::fromLatin1("name")).toString();
          }
          else if (QString::fromLatin1("dependency") == stream.name())
          {
            pluginData->dependencies.append(stream.attributes().value(QString::fromLatin1("name")).toString());
          }
          break;

        default: break;
      }
    }

    if (stream.hasError())
    {
      // error!
      qWarning() << Q_FUNC_INFO << "Plugin XML read error" << QDir::toNativeSeparators(fileInfo.absoluteFilePath());
      continue;
    }

    pluginData->instance = nullptr;
    pluginData->path     = dir.absolutePath();

    // add to pool
    m_plugins[pluginData->name] = std::move(pluginData);
  }

  // process found plugins
  auto queue = computeLoadQueue();
  foreach (auto& pluginData, queue)
  {
    // load plugin
    const QString libraryFullPath = QDir::toNativeSeparators(pluginData->path + QDir::separator() + pluginData->name);
    QLibrary library(libraryFullPath, this);

    // resolve
    PFPLUGININSTANCE instance = reinterpret_cast<PFPLUGININSTANCE>(library.resolve("ege_plugin_instance"));
    if (instance == nullptr)
    {
      qWarning() << Q_FUNC_INFO << QString("Could not resolve for plugin: %1. Error: %2").arg(libraryFullPath, library.errorString());
      continue;
    }

    // create instance
    pluginData->instance = qobject_cast<Plugin*>(instance());
    if (pluginData->instance != nullptr)
    {
      qDebug() << Q_FUNC_INFO << QString("Plugin instance created: %1...").arg(libraryFullPath);
      pluginData->instance->initialize(engine);
    }
  }
}

void PluginsManager::unloadPlugins()
{
  auto queue = computeLoadQueue();
  while (!queue.isEmpty())
  {
    auto* pluginData = queue.takeLast();

    if ((pluginData->instance != nullptr) && m_plugins.contains(pluginData->name))
    {
      pluginData->instance->deinitialize();
    }
  }

  m_plugins.clear();
}

void PluginsManager::setPluginPath(const QString& path)
{
  qDebug() << "Setting plugins path: " << path;
  m_path = path;
}

QList<PluginsManager::PluginData*> PluginsManager::computeLoadQueue() const
{
  QList<PluginData*> queue;

  // go thru all plugins
  for (auto& [name, pluginData] : m_plugins)
  {
    QList<PluginData*> loopQueue;
    loadQueue(pluginData.get(), queue, loopQueue);
  }

  return queue;
}

void PluginsManager::loadQueue(PluginData* plugin, QList<PluginData*>& queue, QList<PluginData*>& loopQueue) const
{
  // check if already in load queue
  if (queue.contains(plugin))
  {
    // done
    return;
  }

  // check if circular dependancy found
  if (loopQueue.contains(plugin))
  {
    // error!
    throw std::runtime_error(tr("PluginsManager: circular dependency found").toStdString());
  }

  // add to loop queue pool
  loopQueue << plugin;

  // resolve dependencies
  foreach (const QString& dep, plugin->dependencies)
  {
    auto& depPlugin = m_plugins.at(dep);
    loadQueue(depPlugin.get(), queue, loopQueue);
  }

  // add to queue
  queue << plugin;
}

const QString& PluginsManager::pluginPath() const
{
  return m_path;
}

} // namespace ege
