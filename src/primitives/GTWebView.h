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

#ifndef GTWEBVIEW_H
#define GTWEBVIEW_H

#include "GTGlobals.h"

#include <QWebView>
#include <QWebElement>

namespace HI {

class HI_EXPORT HIWebElement{
public:
    HIWebElement();
    HIWebElement(const QWebElement& el);
    QRect geometry();
    QString toInnerXml();
    QString toPlainText();
private:
    QRect rect;
    QString text;
    QString xml;
};

class HI_EXPORT GTWebView{
public:
    static HIWebElement findElement(GUITestOpStatus &os, QWebView *view, const QString &text, const QString &tag = "*", bool exactMatch = false);
    static void checkElement(GUITestOpStatus &os, QWebView *view, QString text, QString tag = "*", bool exists = true, bool exactMatch = false);
    static bool doesElementExist(GUITestOpStatus &os, QWebView *view, const QString &text, const QString &tag = "*", bool exactMatch = false);

    static void click(GUITestOpStatus &os, QWebView *view, HIWebElement el, Qt::MouseButton button = Qt::LeftButton);
    static void selectElementText(GUITestOpStatus &os, QWebView *view, HIWebElement el);
    static HIWebElement findTreeElement(GUITestOpStatus &os, QWebView *view, QString text);
    static HIWebElement findContextMenuElement(GUITestOpStatus &os, QWebView *view, QString text);

    static void traceAllWebElements(GUITestOpStatus &os, QWebView *view);

};

}

#endif // GTWEBVIEW_H
