#include "CorePlugin.hpp"
// #include "LoadSave/LoadSaveServer.h"
// #include "ObjectPool.h"
// #include "Point3.h"
// #include "Point3F.h"
#include "Project/ProjectFactory.hpp"
// #include "Settings.h"
#include <QDebug>
#include <QQmlApplicationEngine>

namespace ege
{

CorePlugin::CorePlugin(QObject* parent)
  : QObject(parent)
{
}

CorePlugin::~CorePlugin()
{
}

void CorePlugin::initialize(QQmlApplicationEngine& engine)
{
  // m_loadSaveServer.reset(new LoadSaveServer());
  // if ( ! ObjectPool::Instance()->addObject(m_loadSaveServer.get()))
  // {
  //   qCritical() << "Could not add LoadSaveServer into pool!";
  // }

  m_projectFactory = std::make_unique<ProjectFactory>();
  // if ( ! ObjectPool::Instance()->addObject(m_projectFactory.get()))
  // {
  //   qCritical() << "Could not add ProjectFactory into pool!";
  // }

  // m_settings.reset(new Settings());
  // if ( ! ObjectPool::Instance()->addObject(m_settings.get()))
  // {
  //   qCritical() << "Could not add Settings into pool!";
  // }

  registerMetaDataTypes();
}

void CorePlugin::deinitialize()
{
  // ObjectPool::Instance()->addObject(m_settings.get());
  // ObjectPool::Instance()->removeObject(m_projectFactory.get());
  // ObjectPool::Instance()->removeObject(m_loadSaveServer.get());
}

QString CorePlugin::name() const
{
  return "CorePlugin";
}

QStringList CorePlugin::dependencies() const
{
  return {};
}

void CorePlugin::registerMetaDataTypes()
{
  // if ( ! QMetaType::registerDebugStreamOperator<Point3>())
  // {
  //   qWarning() << "Failed to register debug stream operator for Point3!";
  // }

  // if ( ! QMetaType::registerDebugStreamOperator<Point3F>())
  // {
  //   qWarning() << "Failed to register debug stream operator for Point3F!";
  // }
}

} // namespace ege

EGE_EXPORT_PLUGIN(ege::CorePlugin)
