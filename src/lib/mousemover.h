#ifndef MOUSEMOVER_H
#define MOUSEMOVER_H

#include <QWindow>

class MouseMover : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool showCursor READ showCursor WRITE setShowCursor NOTIFY showCursorChanged)
public:
    explicit MouseMover(QObject *parent = 0);
    virtual ~MouseMover();

    bool showCursor() const;

signals:

    void showCursorChanged(bool arg);

public slots:
    void move(int x, int y);

    void setShowCursor(bool arg);

private:
    QWindow* m_rootWindow;
    bool m_showCursor;
    bool m_hasWarnedAboutRootWindow;
    void setupRootWindow();
};

#endif // MOUSEMOVER_H
