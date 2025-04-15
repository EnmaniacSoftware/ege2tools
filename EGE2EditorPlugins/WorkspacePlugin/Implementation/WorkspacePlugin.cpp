#include "WorkspacePlugin.hpp"
#include "QmlStatusBar.hpp"

#include <QQmlApplicationEngine>
#include <QQmlContext>

namespace ege
{

WorkspacePlugin::WorkspacePlugin(QObject* parent)
  : QObject(parent),
    m_mainWindow(std::make_unique<MainWindow>(this))
{
  qmlRegisterType<qml::StatusBar>("EgeControls", 1, 0, "StatusBar");
}

WorkspacePlugin::~WorkspacePlugin()
{
}

void WorkspacePlugin::initialize(QQmlApplicationEngine& engine)
{
  engine.addImportPath("qrc:/");

  // expose plugin as main window
  engine.rootContext()->setContextProperty("native_mainWindow", m_mainWindow.get());

  // m_configuration.reset(new ConfigurationDefault(*qobject_cast<StatusBar*>(m_mainWindow.get())));
  // if ( ! ObjectPool::Instance()->addObject(*m_configuration))
  // {
  //   qCritical() << "Could not add ConfigurationDefault into pool";
  // }

  // m_propertiesWindow.reset(new PropertiesWindowImpl(m_mainWindow.get()));

  // load main view
  engine.load("qrc:/workspaceplugin/qml/main.qml");
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
