#pragma once

#include <QQuickItem>

namespace ege::qml
{

class NewProject : public QQuickItem
{
  Q_OBJECT
  QML_ELEMENT

public:
  explicit NewProject(QQuickItem* parent = nullptr);
};

} // namespace ege::qml
