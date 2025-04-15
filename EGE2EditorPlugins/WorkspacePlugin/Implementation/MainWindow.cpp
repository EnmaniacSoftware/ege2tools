#include "MainWindow.hpp"

#include <ObjectPool.hpp>
#include <Project/Project.hpp>

namespace ege
{
MainWindow::MainWindow(QObject* parent)
  : QObject(parent)
{
    // connect
    connect(ObjectPool::Instance(), SIGNAL(objectAdded(QObject*)), this, SLOT(onObjectAdded(QObject*)));
    connect(ObjectPool::Instance(), SIGNAL(objectRemoved(QObject*)), this, SLOT(onObjectRemoved(QObject*)));
}

void MainWindow::onObjectAdded(QObject *object)
{
  // check if project added
  if (qobject_cast<Project*>(object) != nullptr)
  {
    // connect for notification
    connect(object, SIGNAL(dirtyFlagChanged()), this, SLOT(onUpdateTitle()));
  }
}

void MainWindow::onObjectRemoved(QObject *object)
{
  // check if project removed
  if (qobject_cast<Project*>(object))
  {
    // update title
    onUpdateTitle();
  }
}

void MainWindow::onUpdateTitle()
{
  const auto* project = ObjectPool::Instance()->getObject<Project>();

  QString title;

  if (project)
  {
    title = project->name() + " [" + project->typeName() + "] - ";
  }

  title += tr("Enmaniac Game Engine 2 Editor");

  if (project && project->isDirty())
  {
    title += " *";
  }

  emit setWindowTitle(title);
}

} // namespace ege
