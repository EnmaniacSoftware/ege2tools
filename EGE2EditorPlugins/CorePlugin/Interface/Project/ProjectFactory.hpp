#pragma once

#include "CorePlugin_global.h"
#include <QAbstractItemModel>
#include <QMap>
#include <QModelIndex>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QString>
#include <QVariant>
#include <functional>

namespace ege
{

class Project;

//! @brief
//! Project factory object.
//! It is possible to register custom project types with the factory.
//! It can also serve as data model.
//! Factory is also responsible managing project loading/saving.
class COREPLUGIN_API ProjectFactory : public QAbstractItemModel
{
  Q_OBJECT

  public:
    using ProjectCreateFunction   = std::function<Project*(QObject*, const QString&, const QString&)>;
    using ProjectTypeNameFunction = std::function<QString()>;

  public:

    explicit ProjectFactory(QObject* parent = nullptr);
   ~ProjectFactory() override;

  public:
    //! Registeres custom project type.
    //! @param typeNameFunc Function that returns type name of the project being registered.
    //! @param  createFunc Function create function.
    //! @returns TRUE if project type was registered successfully (e.g. it type name wasnt registered yet). Otherwise, FALSE.
    bool registerProject(ProjectTypeNameFunction typeNameFunc, ProjectCreateFunction createFunc);
    //! Creates instance of project of the type given by name.
    //! @param parent   Parent object new project instance is to be attached to.
    //! @param typeName Name of the type of the project to be created.
    //! @param name     Name of the project.
    //! @param path     Location where project file is to be created.
    //! @returns Pointer to newly create project. Otherwise, NULL.
    Project* createProject(QObject* parent, const QString& typeName, const QString& name, const QString& path) const;
    //! Check if project type is registered already.
    //! @param typeName Name of the type of the project.
    //! @returns TRUE if given project type is registered. Otherwise, FALSE.
    bool isProjectRegistered(const QString& typeName) const;

  private:

    //! @see QAbstractItemModel::parent.
    QModelIndex parent(const QModelIndex &index) const override;
    //! @see QAbstractItemModel::index.
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    //! @see QAbstractItemModel::data.
    QVariant data(const QModelIndex &index, int role) const override;
    //! @see QAbstractItemModel::columnCount.
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    //! @see QAbstractItemModel::rowCount.
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

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
};

} // namespace ege
