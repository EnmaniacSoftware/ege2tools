#pragma once

#include <QMap>
#include <QObject>
#include <QStringList>
#include <QQmlApplicationEngine>

#include <list>
#include <memory>

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
  void setPluginsDirectory(const QString& path);

  //! Loads plugins.
  //! @note May throw on error.
  void loadPlugins(QQmlApplicationEngine& engine);
  //! Unloads plugins.
  void unloadPlugins();

private:
  //! Returns path to plugin directory.
  const QString& pluginPath() const;

private:
  QString m_path;               //<! Plugins directory path.
  std::list<Plugin*> m_plugins; //<! List of all plugin in initialization order.
};

} // namespace ege
