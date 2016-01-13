/**
* UGENE - Integrated Bioinformatics Tools.
* Copyright (C) 2008-2016 UniPro <ugene@unipro.ru>
* http://ugene.unipro.ru
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
* MA 02110-1301, USA.
*/


#include <core/MainThreadRunnable.h>

#include <drivers/GTMouseDriver.h>
#include "primitives/GTWebView.h"

#include <QWebFrame>

namespace HI {
namespace {
bool compare(QString s1, QString s2, bool exactMatch){
    if(exactMatch){
        return s1==s2;
    }else{
        return s1.contains(s2);
    }
}
}

#define GT_CLASS_NAME "GTWebView"

#define GT_METHOD_NAME "findElement"
QWebElement GTWebView::findElement(GUITestOpStatus &os, QWebView *view, const QString &text, const QString &tag, bool exactMatch) {
    class Scenario : public CustomScenario {
    public:
        Scenario(QWebView *view, const QString &text, const QString &tag, bool exactMatch, QWebElement &webElement) :
            view(view),
            text(text),
            tag(tag),
            exactMatch(exactMatch),
            webElement(webElement) {}

        void run(GUITestOpStatus &os) {
            Q_UNUSED(os);
            QWebFrame* frame = view->page()->mainFrame();
            foreach (QWebElement el, frame->findAllElements(tag)) {
                QString s = el.toPlainText();
                int width = el.geometry().width();

                if (compare(s, text, exactMatch) && width != 0) {
                    webElement = el;
                    return;
                }
            }
            GT_CHECK(false, QString("element with text '%1' and tag '%2' not found").arg(text).arg(tag));
        }

    private:
        QWebView *view;
        const QString text;
        const QString tag;
        bool exactMatch;
        QWebElement &webElement;
    };

    QWebElement webElement;
    MainThreadRunnable mainThreadRunnable(os, new Scenario(view, text, tag, exactMatch, webElement));
    mainThreadRunnable.doRequest();
    return webElement;
}
#undef GT_METHOD_NAME

#define GT_METHOD_NAME "checkElement"
void GTWebView::checkElement(GUITestOpStatus &os, QWebView *view, QString text, QString tag, bool exists, bool exactMatch){
    const bool found = doesElementExist(os, view, text, tag, exactMatch);
    if (exists) {
        GT_CHECK(found, "element with text " + text + " and tag " + tag + " not found");
    } else {
        GT_CHECK(!found, "element with text " + text + " and tag " + tag + " unexpectedly found");
    }
}
#undef GT_METHOD_NAME

#define GT_METHOD_NAME "doesElementExist"
bool GTWebView::doesElementExist(GUITestOpStatus &os, QWebView *view, const QString &text, const QString &tag, bool exactMatch) {
    Q_UNUSED(os)
    QWebFrame* frame = view->page()->mainFrame();

    foreach (QWebElement el, frame->findAllElements(tag)) {
        QString s = el.toPlainText();
        int width = el.geometry().width();

        if (compare(s, text, exactMatch) && width != 0) {
            return true;
        }
    }
    return false;
}
#undef GT_METHOD_NAME

QWebElement GTWebView::findTreeElement(GUITestOpStatus &os, QWebView *view, QString text){
    return findElement(os, view, text, "SPAN");
}

QWebElement GTWebView::findContextMenuElement(GUITestOpStatus &os, QWebView *view, QString text){
    return findElement(os, view, text, "LI");
}

void GTWebView::click(GUITestOpStatus &os, QWebView *view, QWebElement el, Qt::MouseButton button){
    GTMouseDriver::moveTo(os, view->mapToGlobal(el.geometry().center()));
    GTMouseDriver::click(os, button);
}

void GTWebView::selectElementText(GUITestOpStatus &os, QWebView *view, QWebElement el){
    GTMouseDriver::moveTo(os, view->mapToGlobal(el.geometry().topLeft()) + QPoint(5,5));
    GTMouseDriver::press(os);
    GTMouseDriver::moveTo(os, view->mapToGlobal(el.geometry().bottomRight()) - QPoint(5,5));
    GTMouseDriver::release(os);
}

void GTWebView::traceAllWebElements(GUITestOpStatus &os, QWebView *view){
    Q_UNUSED(os)
    QWebFrame* frame = view->page()->mainFrame();
    QWebElement result;
    foreach (QWebElement el, frame->findAllElements("*")) {
        QString s = el.toPlainText();
        QString tagName = el.tagName();
        QString localName = el.localName();

        if(el.geometry().width() != 0){
            qDebug("GT_DEBUG_MESSAGE tag: %s name: %s text: %s width: %d", tagName.toLocal8Bit().constData(), localName.toLocal8Bit().constData(), s.toLocal8Bit().constData(), el.geometry().width());
        }
        if (s == "Input"){
            result = el;
        }
    }

}

#undef GT_CLASS_NAME

}
