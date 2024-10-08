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

    typedef std::function<Project* (QObject*, const QString&, const QString&)> CreateFunction;
    typedef std::function<QString ()> ProjectTypeNameFunction;

  public:

    explicit ProjectFactory(QObject* parent = nullptr);
   ~ProjectFactory() override;

  public:

    //! Registeres custom project type.
    bool registerProject(ProjectTypeNameFunction typeNameFunc, CreateFunction createFunc);
    //! Creates instance of project of the type given by name.
    Project* createProject(const QString& typeName, const QString& name, const QString& path, QObject* parent) const;
    //! Returns TRUE if given project type is registered.
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
      CreateFunction          createFunc;
    };

    typedef QList<ProjectData> ProjectRegisterList;

  private:

    //! List of registered projects.
    ProjectRegisterList m_registeredProjects;
};

} // namespace ege
