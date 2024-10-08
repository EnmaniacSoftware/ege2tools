#pragma once

#include "Plugins/PluginsManager.hpp"

#include <QGuiApplication>

namespace ege
{

//! @brief
//! Entry point of entire application. It's sole purpose is to manage available plugins.
class Application : public QGuiApplication
{
  Q_OBJECT

  public:

    //! Constructs application.
    //! @note May throw on error.
    Application(int& argc, char** argv);

  private:
    QQmlApplicationEngine m_engine;
    PluginsManager m_pluginManager;
};

} // namespace ege
