#pragma once

#include "CorePlugin_global.h"

// #include "Serializable.h"
// #include "LoadSave/LoadSaveClient.h"
#include <QObject>
#include <QString>

class QStyledItemDelegate;

namespace ege
{

class ReadStream;
class WriteStream;

//! @brief
//! Project base class.
class COREPLUGIN_API Project : public QObject
// protected Serializable
//, protected LoadSaveClient
{
  Q_OBJECT
  // Q_INTERFACES(CorePlugin::LoadSaveClient
  //              CorePlugin::Serializable)

public:
  ~Project() override;

public:
  //! Returns project's file extension.
  static QString FileExtension();
  //! Returns string representing a project file filter.
  static QString FileFilter();

signals:

  //! Signal emitted when project dirty flag changes.
  void dirtyFlagChanged();

public:
  //! Returns type name.
  const QString& typeName() const;

  //! Returns name.
  const QString& name() const;

  //! Returns full path to project file.
  const QString& path() const;

  //! Marks/unmarks project content as dirty.
  void setDirty(bool set);
  //! Returns dirty flag.
  bool isDirty() const;

  //! Returns resource library item delegate.
  virtual QStyledItemDelegate* resourceLibraryItemDelegate() const = 0;

public slots:

  //! Slot called when project data has changed.
  void onProjectDataChanged();

protected:
  //! Constructor.
  Project(QObject* parent, const QString& typeName, const QString& name, const QString& path);

  //! @see LoadSaveClient::save.
  // bool save(WriteStream& stream) override;
  // //! @see LoadSaveClient::load.
  // bool load(ReadStream& stream) override;
  // //! @see LoadSaveClient::tag.
  // QString tag() const override;

private:
  //! Type name.
  QString m_typeName;
  //! Name.
  QString m_name;
  //! Path to project file.
  QString m_path;
  //! Dirty flag.
  bool m_dirty;
};

} // namespace ege
