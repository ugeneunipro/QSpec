#ifndef EVENTFILTER_H
#define EVENTFILTER_H

#include <QObject>
#include <QKeyEvent>

class KeyEvent
{
public:
    KeyEvent();
    KeyEvent(QKeyEvent*);

    Qt::Key getKey();
    QEvent::Type getType();
private:
    Qt::Key key;
    QEvent::Type type;
};

class EventFilter : public QObject
{
    Q_OBJECT
public:
    EventFilter(QObject *parent = 0);
    QList<KeyEvent> keyEvents;
protected:
    bool eventFilter(QObject *, QEvent *);
};

#endif // EVENTFILTER_H
