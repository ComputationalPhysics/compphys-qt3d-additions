#include "mousemover.h"

#include <QCursor>
#include <QApplication>

MouseMover::MouseMover(QQuickView *parent) :
    QObject(parent),
    m_view(parent)
{
}

MouseMover::~MouseMover()
{
}

bool MouseMover::showCursor() const
{
    return m_showCursor;
}

void MouseMover::move(int x, int y)
{
    QPoint globalPoint = m_view->mapToGlobal(QPoint(x,y));
    QCursor::setPos(globalPoint);
}

void MouseMover::setShowCursor(bool arg)
{
    if (m_showCursor != arg) {
        m_showCursor = arg;
        if(m_showCursor) {
            QApplication::setOverrideCursor(QCursor());
            QApplication::changeOverrideCursor(QCursor());
        } else {
            QApplication::setOverrideCursor(QCursor(Qt::BlankCursor));
            QApplication::changeOverrideCursor(QCursor(Qt::BlankCursor));
        }
        emit showCursorChanged(arg);
    }
}
