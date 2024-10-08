// #include "ObjectPool.h"
// #include "LoadSave/ReadStream.h"
// #include "LoadSave/WriteStream.h"
#include "Project/Project.hpp"

namespace ege
{

// static const QString KProjectTag = "Project";

Project::Project(QObject* parent, const QString& typeName, const QString& name, const QString& path)
: QObject(parent)
, m_typeName(typeName)
, m_name(name)
, m_path(path)
, m_dirty(false)
{
}

Project::~Project()
{
}

QString Project::FileExtension()
{
  return "egeproj";
}

QString Project::FileFilter()
{
  return tr("Projects") + QString(" (*." + FileExtension() + ")");
}

void Project::setDirty(bool set)
{
  if (m_dirty != set)
  {
    m_dirty = set;

    emit dirtyFlagChanged();
  }
}

bool Project::isDirty() const
{
  return m_dirty;
}

void Project::onProjectDataChanged()
{
  setDirty(true);
}

const QString& Project::typeName() const
{
  return m_typeName;
}

const QString& Project::name() const
{
  return m_name;
}

const QString& Project::path() const
{
  return m_path;
}

// bool Project::save(WriteStream& stream)
// {
//   stream.startElement(KProjectTag);

//   stream.addAttribute("name", name());

//   return ! stream.hasError();
// }

// bool Project::load(ReadStream& stream)
// {
//   m_name = stream.attribute("name");

//   return ! m_name.isEmpty() && ! stream.hasError();
// }

// QString Project::tag() const
// {
//   return KProjectTag;
// }

} // namespace ege
