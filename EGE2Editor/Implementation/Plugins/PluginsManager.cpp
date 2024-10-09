#include "Plugins/PluginsManager.hpp"
#include "Plugins/Plugin.hpp"

#include <QDebug>
#include <QDir>
#include <QLibrary>

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

void PluginsManager::setPluginsDirectory(const QString& path)
{
  qDebug() << "Setting plugins directory to" << path;
  m_path = path;
}

void PluginsManager::loadPlugins(QQmlApplicationEngine& engine)
{
  struct PluginInfo
  {
    QString path;
    QStringList dependencies;
    Plugin* instance;
  };

  std::list<PluginInfo> plugins;

  QDir dir(pluginPath());
  dir.setFilter(QDir::Files | QDir::NoSymLinks);

  const auto& fileList = dir.entryInfoList();
  for (const auto& fileInfo : fileList)
  {
    const auto& pluginPath = QDir::toNativeSeparators(fileInfo.absoluteFilePath());

    // try to load file as a plugin
    QLibrary library(pluginPath, this);

    auto pluginCreateInstance = reinterpret_cast<PFPLUGINCREATEINSTANCE>(library.resolve("ege_plugin_create_instance"));
    if (pluginCreateInstance != nullptr)
    {
      auto* plugin = qobject_cast<Plugin*>(pluginCreateInstance());
      if (plugin != nullptr)
      {
        PluginInfo info{};
        info.instance     = plugin;
        info.path         = pluginPath;
        info.dependencies = plugin->dependencies();

        qDebug() << "Plugin found at" << info.path;
        plugins.push_back(std::move(info));
      }
    }
  }

  plugins.sort([](const auto& p1, const auto& p2) { return p1.dependencies.size() < p2.dependencies.size(); });

  auto done{ true };
  while (!plugins.empty())
  {
    auto plugin = plugins.front();
    if (!plugin.dependencies.empty())
    {
      qWarning() << "Plugin" << plugin.instance->name() << "has missing remaining dependencies" << plugin.dependencies << "and may not work correctly.";
    }

    plugins.pop_front();

    for (auto& nextPlugin : plugins)
    {
      nextPlugin.dependencies.removeAll(plugin.instance->name());
    }

    m_plugins.push_back(plugin.instance);
  }

  for (auto& plugin : m_plugins)
  {
    qDebug() << "Initializing plugin" << plugin->name();
    plugin->initialize(engine);
  }
}

void PluginsManager::unloadPlugins()
{
  m_plugins.reverse();
  for (auto& plugin : m_plugins)
  {
    qDebug() << "Deinitializing plugin" << plugin->name();
    plugin->deinitialize();
  }

  m_plugins.clear();
}

const QString& PluginsManager::pluginPath() const
{
  return m_path;
}

} // namespace ege
