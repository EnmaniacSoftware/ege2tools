#pragma once

#include <QObject>
#include <QQmlEngine>

namespace ege
{
//! @brief
//! Application's main window.
class MainWindow : public QObject
{
  Q_OBJECT
  QML_ELEMENT

public:
  MainWindow(QObject* parent = nullptr);

signals:
  //! Signal emitted with new main window title.
  //! @param  title New window title to set.
  void setWindowTitle(const QString& title);

private slots:
  //! Slot called when new object has been added into the pool.
  void onObjectAdded(QObject* object);
  //! Slot called when object is about to be removed from pool.
  void onObjectRemoved(QObject* object);
  //! Slot called when title of the main window should be updated.
  void onUpdateTitle();
};
}
