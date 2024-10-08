#pragma once

#include <QColor>
#include <QQuickPaintedItem>
#include <QString>
#include <QTimer>

namespace ege
{
namespace qml
{

class StatusBar : public QQuickPaintedItem
{
  Q_OBJECT
  QML_ELEMENT
  Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)

signals:
  void colorChanged();

public:
  explicit StatusBar(QQuickItem* parent = nullptr);

  Q_INVOKABLE void showMessage(const QString& message, int timeout = 0);

  void paint(QPainter* painter) override;

  //! Sets text color.
  Q_INVOKABLE void setColor(const QColor& color);
  //! Returns text color.
  const QColor& color() const;

private slots:
  void clearMessage();

private:
  const QString& text() const;

private:
  QString m_text;
  QColor m_textColor;
  QColor m_backgroundColor;
  QTimer m_timer;
};

} // namespace qml
} // namespace ege
