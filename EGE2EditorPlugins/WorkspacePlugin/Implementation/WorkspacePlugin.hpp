#pragma once

#include "WorkspacePlugin_global.h"

#include <Plugins/Plugin.hpp>

namespace ege
{

//! @brief
//! Workspace plugin acts as entry point to graphical user interface.
//! It offers main application window support which can be used by another plugins to place their UI on.
//! Main window provides the menu bar which can be further extended by another plugins.
class WORKSPACEPLUGIN_API WorkspacePlugin : public QObject,
                                            public Plugin
{
  Q_OBJECT
  Q_INTERFACES(ege::Plugin)

public:
  explicit WorkspacePlugin(QObject* parent = nullptr);
  ~WorkspacePlugin() override;

private:
  //! @see Plugin::initialize.
  void initialize(QQmlApplicationEngine& engine) override;
  //! @see Plugin::deinitialize.
  void deinitialize() override;
  //! @see Plugin::name.
  QString name() const override;
  //! @see Plugin::dependecies.
  QStringList dependencies() const override;

private:
  //! Main window.
//  std::unique_ptr<MainWindow> m_mainWindow;
};

} // namespace ege
