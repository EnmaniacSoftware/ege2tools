#include "ObjectPool.hpp"

#include <cassert>

namespace ege
{

ObjectPool* ObjectPool::Instance()
{
  static ObjectPool objectPool;
  return &objectPool;
}

bool ObjectPool::addObject(QObject* object)
{
  if (object == nullptr)
  {
    return false;
  }

  auto shouldObjectBeAdded{ false };

  {
    const std::lock_guard<std::mutex> lock(m_mutex);
    shouldObjectBeAdded = std::find(m_objects.begin(), m_objects.end(), object) == m_objects.end();
    if (shouldObjectBeAdded)
    {
      m_objects.push_back(object);
    }
  }

  if (shouldObjectBeAdded)
  {
    emit objectAdded(object);
  }

  return shouldObjectBeAdded;
}

void ObjectPool::removeObject(QObject *object)
{
  if (object == nullptr)
  {
    return;
  }

  auto count{ 0 };

  {
    const std::lock_guard<std::mutex> lock(m_mutex);
    count = std::erase(m_objects, object);
    assert(count <= 1);
  }

  if (count > 0)
  {
    emit objectRemoved(object);
  }
}

std::vector<QObject*> ObjectPool::allObjects() const
{
  return m_objects;
}
}
