#pragma once

#include <QObject>
#include <QStringList>
#include <QtPlugin>

class QQmlApplicationEngine;

namespace ege
{

//! @brief
//! Interface for editor plugin.
class Plugin
{
  public:
    virtual ~Plugin() = default;

  public:
    //! Initializes the plugin.
    //! @param engine QML engine object.
    //! @note May throw on error.
    virtual void initialize(QQmlApplicationEngine& engine) = 0;
    //! Deinitializes the plugin.
    virtual void deinitialize() = 0;
    //! Name of the plugin.
    //! @note Other plugins may use this name in their dependencies.
    virtual QString name() const = 0;
    //! Returns a list of dependencies, that this plugin requires.
    //! @note Dependency is a name of another plugin that is required to be present and loaded beforehand.
    virtual QStringList dependencies() const = 0;
};

} // namespace ege

Q_DECLARE_INTERFACE(ege::Plugin, "com.enmaniacsoftware.ege2tools.editor.plugin/1.0")

#define EGE_EXPORT_PLUGIN(pluginClass) \
  extern "C" Q_DECL_EXPORT QT_PREPEND_NAMESPACE(QObject)* ege_plugin_instance() Q_PLUGIN_INSTANCE(pluginClass)

typedef QT_PREPEND_NAMESPACE(QObject)* (*PFPLUGININSTANCE)();
