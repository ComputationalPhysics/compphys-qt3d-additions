#ifndef MOUSEMOVER_H
#define MOUSEMOVER_H

#include <QQuickView>

class MouseMover : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool showCursor READ showCursor WRITE setShowCursor NOTIFY showCursorChanged)
public:
    explicit MouseMover(QQuickView *parent = 0);
    virtual ~MouseMover();

    bool showCursor() const;

signals:

    void showCursorChanged(bool arg);

public slots:
    void move(int x, int y);

    void setShowCursor(bool arg);

private:
    QQuickView* m_view;
    bool m_showCursor;
};

#endif // MOUSEMOVER_H
