#include "Application.hpp"

#include <QCommandLineParser>
#include <QQmlApplicationEngine>
#include <QString>

#include <stdexcept>

namespace
{
constexpr char KPluginsDirectoryOption[] = "plugins-dir";
}

namespace ege
{

Application::Application(int& argc, char** argv)
  : QGuiApplication(argc, argv)
{
  QObject::connect(
    &m_engine,
    &QQmlApplicationEngine::objectCreationFailed,
    this,
    [](const QUrl& url) {
      qCritical() << "Couldn't load" << url;
      QCoreApplication::exit(-1);
    },
    Qt::QueuedConnection);

  // process commandline
  QCommandLineParser parser;
  parser.addHelpOption();
  parser.addVersionOption();
  QCommandLineOption pluginDirOption(KPluginsDirectoryOption, QCoreApplication::tr("Directory containing plugins (xml and dynamic libraries)."), "directory");
  parser.addOption(pluginDirOption);
  parser.process(*this);

  const auto& pluginDir = parser.value(KPluginsDirectoryOption);
  if (pluginDir.isEmpty())
  {
    const auto& error = QCoreApplication::tr("Mandatory plugin directory not set!");
    throw std::runtime_error(error.toStdString());
  }

  // setup plugin location
  m_pluginManager.setPluginsDirectory(pluginDir);

  // load plugins
   m_pluginManager.loadPlugins(m_engine);
}

} // namespace ege
