#include "mousemover.h"

#include <QCursor>
#include <QApplication>
#include <QQuickItem>
#include <QQuickWindow>

MouseMover::MouseMover(QObject *parent) :
    QObject(parent),
    m_rootWindow(0),
    m_hasWarnedAboutRootWindow(false)
{
    setShowCursor(true);
}

MouseMover::~MouseMover()
{
}

void MouseMover::setupRootWindow() {
    QObject *rootObject = parent();
    QObject *parentObject = parent();
    for(int i = 0; i < 1000; i++) {
        if(!parentObject) {
            break;
        }
        rootObject = parentObject;
        parentObject = parentObject->parent();
    }
    if(!rootObject) {
        qDebug() << "The MouseMover object has no parent at all.";
        return;
    }

    QQuickItem *rootItem = qobject_cast<QQuickItem*>(rootObject);
    if(!rootItem) {
        qDebug() << "Root object is not a QQuickItem.";
        return;
    }
    QWindow *rootWindow = qobject_cast<QWindow*>(rootItem->window());
    if(!rootWindow) {
        qDebug() << "Root item has no window.";
        return;
    }
    m_rootWindow = rootWindow;
}

bool MouseMover::showCursor() const
{
    return m_showCursor;
}

void MouseMover::move(int x, int y)
{
    if(!m_rootWindow) {
        setupRootWindow();
        if(!m_rootWindow && !m_hasWarnedAboutRootWindow) {
            qWarning() << "Warning: Could not find root window of MouseMover object. "
                          "Perhaps you are not using a QQuickView, QQuickWindow or QWindow as your main view?";
            m_hasWarnedAboutRootWindow = true;
        }
    }
    if(m_rootWindow) {
        QPoint globalPoint = m_rootWindow->mapToGlobal(QPoint(x,y));
        QCursor::setPos(globalPoint);
    }
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
