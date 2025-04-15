#pragma once

#include "CorePlugin_global.h"

#include <QObject>

#include <mutex>
#include <vector>

namespace ege
{

class COREPLUGIN_API ObjectPool : public QObject
{
  Q_OBJECT

signals:

  //! Signal emitted when object has been added into the pool.
  void objectAdded(QObject* object);
  //! Signal emitted when object is to about to be removed from pool.
  void aboutToRemoveObject(QObject* object);
  //! Signal emitted when object is removed from pool.
  void objectRemoved(QObject* object);

public:
  //! Returns pool instance.
  static ObjectPool* Instance();

public:
  //! Adds given object into pool.
  bool addObject(QObject* object);
  //! Removes given object from pool.
  void removeObject(QObject* object);
  //! Returns all objects.
  std::vector<QObject*> allObjects() const;

  //! Returns list of objects of a given type.
  template <typename T>
  std::vector<T*> getObjects() const;

  //! Returns first object of a given type.
  template <typename T>
  T* getObject() const;

private:
  mutable std::mutex m_mutex;      //<! Shared data mutex.
  std::vector<QObject*> m_objects; //<! List of objects.
};

template <typename T>
std::vector<T*> ObjectPool::getObjects() const
{
  std::lock_guard<std::mutex> lock(m_mutex);

  std::vector<T*> result;
  for (QObject* object : m_objects)
  {
    if (T* casted = qobject_cast<T*>(object))
    {
      result.push_back(casted);
    }
  }

  return result;
}

template <typename T>
T* ObjectPool::getObject() const
{
  std::lock_guard<std::mutex> lock(m_mutex);

  for (QObject* object : m_objects)
  {
    if (T* casted = qobject_cast<T*>(object))
    {
      return casted;
    }
  }

  return nullptr;
}
}
