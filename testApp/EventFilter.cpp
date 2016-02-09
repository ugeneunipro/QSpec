#include "EventFilter.h"

KeyEvent::KeyEvent(){
    key = Qt::Key_unknown;
    type = QEvent::None;
}

KeyEvent::KeyEvent(QKeyEvent *e){
    key = (Qt::Key)e->key();
    type = e->type();
}

Qt::Key KeyEvent::getKey(){return key;}
QEvent::Type KeyEvent::getType(){return type;}

EventFilter::EventFilter(QObject *parent) :
    QObject(parent)
{
}

bool EventFilter::eventFilter(QObject *o, QEvent *e){
    QKeyEvent* keyEvent = dynamic_cast<QKeyEvent*>(e);
    if(keyEvent != NULL && (keyEvent->type() == QEvent::KeyPress || keyEvent->type() == QEvent::KeyRelease)){
        keyEvents.append(KeyEvent(keyEvent));
    }
    return QObject::eventFilter(o,e);
}
