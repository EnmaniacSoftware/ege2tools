#include "Project/ProjectFactory.hpp"
#include "Project/Project.hpp"

#include <QDebug>

namespace ege
{

ProjectFactory::ProjectFactory(QObject* parent)
: QAbstractItemModel(parent)
{
}

ProjectFactory::~ProjectFactory()
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

Project* ProjectFactory::createProject(QObject* parent, const QString& typeName, const QString& name, const QString& path) const
{
  Project* project = nullptr;

  // get project create function for a given type name
  foreach (const ProjectData& projectData, m_registeredProjects)
  {
    if (projectData.typeNameFunc() == typeName)
    {
      project = projectData.createFunc(parent, name, path);
      break;
    }
  }

  return project;
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

  if (Qt::DisplayRole != role)
  {
    // done
    return QVariant();
  }

  return m_registeredProjects[index.row()].typeNameFunc();
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
