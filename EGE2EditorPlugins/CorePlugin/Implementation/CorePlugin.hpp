#pragma once

#include "CorePlugin_global.h"

#include <Plugins/Plugin.hpp>

#include <memory>

namespace ege
{
// class LoadSaveServer;
class ProjectFactory;
// class Settings;

//! @brief
//! Core plugin acts as a base for all other plugins.
//! The common data types and interfaces are defined here.
class COREPLUGIN_API CorePlugin : public QObject,
                                  public Plugin
{
  Q_OBJECT
  Q_INTERFACES(ege::Plugin)

public:
  explicit CorePlugin(QObject* parent = nullptr);
  ~CorePlugin() override;

private:
  //! @see Plugin::initialize.
  void initialize(QQmlApplicationEngine& engine) override;
  //! @see Plugin::deinitialize.
  void deinitialize() override;
  //! @see Plugin::name.
  QString name() const override;
  //! @see Plugin::dependecies.
  QStringList dependencies() const override;

  //! Registers meta data types.
  void registerMetaDataTypes();

private:
  //! Load/Save server.
  //  std::unique_ptr<LoadSaveServer> m_loadSaveServer;
  //! Project factory.
  std::unique_ptr<ProjectFactory> m_projectFactory;
  //! Settings.
  // std::unique_ptr<Settings> m_settings;
};

} // namespace ege
