#pragma once

#include "CorePlugin_global.h"
#include "Project.hpp"

#include <QAbstractItemModel>
#include <QHash>
#include <QMap>
#include <QModelIndex>
#include <QString>
#include <QUrl>
#include <QVariant>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QtQml>

#include <functional>
#include <memory>

namespace ege
{

//! @brief
//! Project factory object.
//! It is possible to register custom project types with the factory.
//! It can also serve as data model.
//! Factory is also responsible managing project loading/saving.
class COREPLUGIN_API ProjectFactory : public QAbstractItemModel
{
  Q_OBJECT
  QML_ELEMENT

  enum Roles
  {
    ProjectNameRole = Qt::UserRole + 1
  };

public:
  using ProjectCreateFunction   = std::function<std::unique_ptr<Project>(const QString&, const QString&)>;
  using ProjectTypeNameFunction = std::function<QString()>;

public:
  explicit ProjectFactory(QObject* parent = nullptr);

signals:
  //! Signal emitted when project is created.
  //! @param project  Newly created project.
  void projectCreated(Project* project) const;

public:
  //! Registers custom project type.
  //! @param typeNameFunc Function that returns type name of the project being registered.
  //! @param  createFunc Function create function.
  //! @returns TRUE if project type was registered successfully (e.g. it type name wasnt registered yet). Otherwise, FALSE.
  bool registerProject(ProjectTypeNameFunction typeNameFunc, ProjectCreateFunction createFunc);

  //! Creates instance of project of the type given by name.
  //! @param typeName Name of the type of the project to be created.
  //! @param name     Name of the project.
  //! @param url      Location where project is to be created.
  //! @note On successful project creation, @ref projectCreated is emitted.
  Q_INVOKABLE void createProject(const QString& typeName, const QString& name, const QUrl& url);

  //! Check if project type is registered already.
  //! @param typeName Name of the type of the project.
  //! @returns TRUE if given project type is registered. Otherwise, FALSE.
  bool isProjectRegistered(const QString& typeName) const;

protected:
  QHash<int, QByteArray> roleNames() const override;

private:
  //! @see QAbstractItemModel::parent.
  QModelIndex parent(const QModelIndex& index) const override;
  //! @see QAbstractItemModel::index.
  QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
  //! @see QAbstractItemModel::data.
  QVariant data(const QModelIndex& index, int role) const override;
  //! @see QAbstractItemModel::columnCount.
  int columnCount(const QModelIndex& parent = QModelIndex()) const override;
  //! @see QAbstractItemModel::rowCount.
  int rowCount(const QModelIndex& parent = QModelIndex()) const override;

private:
  //! Data struct of registered project.
  struct ProjectData
  {
    ProjectTypeNameFunction typeNameFunc;
    ProjectCreateFunction createFunc;
  };

  typedef QList<ProjectData> ProjectRegisterList;

private:
  //! List of registered projects.
  ProjectRegisterList m_registeredProjects;
  //! Created project.
  std::unique_ptr<Project> m_project;
};

} // namespace ege
