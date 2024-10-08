#include "QmlStatusBar.hpp"

#include <QColor>
#include <QPainter>

#include <QGuiApplication>
#include <QtLogging>

namespace ege
{
namespace qml
{

StatusBar::StatusBar(QQuickItem* parent)
  : QQuickPaintedItem(parent),
    m_textColor(Qt::black)
{
  setHeight(20);
  setFillColor(Qt::red);

  m_timer.setSingleShot(true);
  connect(&m_timer, &QTimer::timeout, this, &StatusBar::clearMessage);
}

void StatusBar::showMessage(const QString& message, int timeout)
{
  m_text = message;
  if (timeout > 0)
  {
    m_timer.start(timeout);
  }

  update();
}

void StatusBar::paint(QPainter* painter)
{
  qCritical() << "PAINTING" << boundingRect() << m_text << QGuiApplication::font();

  painter->setPen({ fillColor() });
  painter->setBrush({ fillColor() });
  painter->drawRect(boundingRect());

  painter->setPen({ color() });
  painter->drawText(boundingRect(), Qt::AlignLeft | Qt::AlignVCenter, text());
}

void StatusBar::setColor(const QColor& color)
{
  m_textColor = color;
}

const QColor& StatusBar::color() const
{
  return m_textColor;
}

void StatusBar::clearMessage()
{
  showMessage("", 0);
}

const QString& StatusBar::text() const
{
  return m_text;
}

} // namespace qml
} // namespace ege
