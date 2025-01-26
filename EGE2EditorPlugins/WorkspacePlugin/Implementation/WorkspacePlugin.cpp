#include "WorkspacePlugin.hpp"
#include "NewProject.hpp"
#include "QmlStatusBar.hpp"

#include <QQmlApplicationEngine>

namespace ege
{

WorkspacePlugin::WorkspacePlugin(QObject* parent)
  : QObject(parent)
{
  qmlRegisterType<qml::StatusBar>("EgeControls", 1, 0, "StatusBar");
  qmlRegisterType<qml::NewProject>("EgeEditor", 1, 0, "NewProject");
}

WorkspacePlugin::~WorkspacePlugin()
{
}

void WorkspacePlugin::initialize(QQmlApplicationEngine& engine)
{
  engine.addImportPath("qrc:/");

  engine.load("qrc:/workspaceplugin/qml/main.qml");

  // create objects
  // m_mainWindow.reset(new MainWindow());

  // m_configuration.reset(new ConfigurationDefault(*qobject_cast<StatusBar*>(m_mainWindow.get())));
  // if ( ! ObjectPool::Instance()->addObject(*m_configuration))
  // {
  //   qCritical() << "Could not add ConfigurationDefault into pool";
  // }

  // m_propertiesWindow.reset(new PropertiesWindowImpl(m_mainWindow.get()));

  // // show main window
  // m_mainWindow->show();
}

void WorkspacePlugin::deinitialize()
{
  // ObjectPool::Instance()->removeObject(*m_configuration);

  // CleanupResources();
}

QString WorkspacePlugin::name() const
{
  return "WorkspacePlugin";
}

QStringList WorkspacePlugin::dependencies() const
{
  return { "CorePlugin" };
}

} // namespace ege

EGE_EXPORT_PLUGIN(ege::WorkspacePlugin)
