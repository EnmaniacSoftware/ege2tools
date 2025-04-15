#include "Project/ProjectFactory.hpp"

#include <ObjectPool.hpp>

#include <QDebug>

namespace ege
{

ProjectFactory::ProjectFactory(QObject* parent)
: QAbstractItemModel(parent)
{
}

bool ProjectFactory::registerProject(ProjectTypeNameFunction projectTypeNameFunc, ProjectCreateFunction projectCreateFunc)
{
  if (isProjectRegistered(projectTypeNameFunc()))
  {
    return false;
  }

  m_registeredProjects.append({ .typeNameFunc = projectTypeNameFunc, .createFunc = projectCreateFunc });

  return true;
}

void ProjectFactory::createProject(const QString& typeName, const QString& name, const QUrl& path)
{
  foreach (const ProjectData& projectData, m_registeredProjects)
  {
    if (projectData.typeNameFunc() == typeName)
    {
      m_project = std::move(projectData.createFunc(name, path.toLocalFile()));
      emit projectCreated(m_project.get());

      ObjectPool::Instance()->addObject(m_project.get());

      m_project->setDirty(true);
      return;
    }
  }

  qWarning() << "Could not create project of type" << typeName;
}

bool ProjectFactory::isProjectRegistered(const QString& typeName) const
{
  foreach (const ProjectData& projectData, m_registeredProjects)
  {
    if (projectData.typeNameFunc() == typeName)
    {
      return true;
    }
  }
  
  return false;
}

QHash<int, QByteArray> ProjectFactory::roleNames() const
{
  QHash<int, QByteArray> roles;
  roles[ProjectNameRole] = "projectName";
  return roles;
}

QModelIndex ProjectFactory::parent(const QModelIndex& index) const
{
  Q_UNUSED(index)

  return QModelIndex();
}

QModelIndex ProjectFactory::index(int row, int column, const QModelIndex& parent) const
{
  Q_UNUSED(parent)

  return createIndex(row, column);
}

QVariant ProjectFactory::data(const QModelIndex& index, int role) const
{
  // check if invalid index
  if ( ! index.isValid() || (index.row() >= m_registeredProjects.count()))
  {
    // done
    return QVariant();
  }

  if (role == ProjectNameRole)
  {
    return m_registeredProjects[index.row()].typeNameFunc();
  }

  return QVariant();
}

int ProjectFactory::columnCount(const QModelIndex& parent) const
{
  Q_UNUSED(parent)

  return 1;
}

int ProjectFactory::rowCount(const QModelIndex& parent) const
{
  Q_UNUSED(parent)

  return m_registeredProjects.count();
}

} // namespace ege
