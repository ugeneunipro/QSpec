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

#include <QApplication>
#include <QTimer>
#include <utils/GTThread.h>

#include "GTMouseDriver.h"

namespace HI {

void GTMouseDriver::click(GUITestOpStatus &os, Qt::MouseButton button)
{
    press(os, button);
    release(os, button);

    GTGlobals::sleep(500);
}

namespace {

bool isFarEnoughToStartDnd(const QPoint &start, const QPoint &end) {
    return (end - start).manhattanLength() > 2 * QApplication::startDragDistance();
}

}

void GTMouseDriver::dragAndDrop(GUITestOpStatus &os, const QPoint& start, const QPoint& end) {
    moveTo(os, start);
    GTDragger d(os, end);
    Q_UNUSED(d);

    press(os);

    const QPoint farPoint = (isFarEnoughToStartDnd(start, (end + start) / 2) ?
                                 (end + start) / 2 :
                                 QPoint(0, 0));
    GTMouseDriver::moveTo(os, farPoint);

    GTThread::waitForMainThread(os);
}

#ifndef Q_OS_MAC
void GTMouseDriver::doubleClick(GUITestOpStatus &os)
{
    press(os, Qt::LeftButton);
    release(os, Qt::LeftButton);
    GTGlobals::sleep(100);

    press(os, Qt::LeftButton);
    release(os, Qt::LeftButton);
    GTGlobals::sleep(250);
}
#endif

GTDragger::GTDragger(GUITestOpStatus &_os, const QPoint& _to) :
    QObject(),
    os(_os),
    to(_to),
    done(false)
{
    QTimer::singleShot(2000, this, SLOT(sl_execDrag()));
    GTGlobals::sleep(500);
}

GTDragger::~GTDragger() {
    if (!done) {
        sl_execDrag();
    }
}

void GTDragger::sl_execDrag(){
    GTMouseDriver::moveTo(os, to);
#ifndef Q_OS_LINUX
    GTMouseDriver::release(os);
    GTThread::waitForMainThread(os);
#else
    GTMouseDriver::click(os);
    GTGlobals::sleep();
#endif
    done = true;
}

} //namespace
