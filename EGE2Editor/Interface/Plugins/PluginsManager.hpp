#pragma once

#include <QMap>
#include <QObject>
#include <QStringList>
#include <QQmlApplicationEngine>

#include <memory>
#include <map>

namespace ege
{

class Plugin;

//! @brief
//! Object managing plugins.
class PluginsManager : public QObject
{
public:
  explicit PluginsManager(QObject* parent = nullptr);
  ~PluginsManager();

  //! Sets plugin directory.
  //! @param  path  Path where both XML definitions and binaries of plugins are be located.
  void setPluginPath(const QString& path);

  //! Loads plugins.
  //! @note May throw on error.
  void loadPlugins(QQmlApplicationEngine& engine);
  //! Unloads plugins.
  void unloadPlugins();

private:
  //<! Plugin data.
  struct PluginData
  {
    QString name;
    QString path;
    QStringList dependencies;
    Plugin* instance;
  };

private:
  //! Generates load queue from all plugins.
  QList<PluginData*> computeLoadQueue() const;
  //! Processes given plugin resolving its dependencies and updating load queue.
  void loadQueue(PluginData* plugin, QList<PluginData*>& queue, QList<PluginData*>& loopQueue) const;
  //! Returns path to plugin directory.
  const QString& pluginPath() const;

private:
  QString m_path;                                           //<! Plugins directory path.
  std::map<QString, std::unique_ptr<PluginData>> m_plugins; //<! Map of all plugins.
};

} // namespace ege
