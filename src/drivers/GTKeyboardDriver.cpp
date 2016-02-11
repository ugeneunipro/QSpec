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

#include <cctype>
#include "GTKeyboardDriver.h"
#include <utils/GTThread.h>

namespace HI {

#define GT_CLASS_NAME "GTKeyboardDriver"

#define GT_METHOD_NAME "keyClick"

QList<Qt::Key> GTKeyboardDriver::modifiersToKeys(Qt::KeyboardModifiers mod){
    QList<Qt::Key> result;
    if(mod.testFlag(Qt::ShiftModifier)){result.append(Qt::Key_Shift);}
    if(mod.testFlag(Qt::AltModifier)){result.append(Qt::Key_Alt);}
    if(mod.testFlag(Qt::ControlModifier)){result.append(Qt::Key_Control);}
    if(mod.testFlag(Qt::MetaModifier)){result.append(Qt::Key_Meta);}
    return result;
}

void GTKeyboardDriver::keyClick(GUITestOpStatus &os, char key, Qt::KeyboardModifiers modifiers)
{
    GT_CHECK(key != 0, "key = 0");
    keyPress(os, key, modifiers);
    keyRelease(os, key, modifiers);
}

void GTKeyboardDriver::keyClick(GUITestOpStatus &os, Qt::Key key, Qt::KeyboardModifiers modifiers)
{
    GT_CHECK(key != 0, "key = 0");
    keyPress(os, key, modifiers);
    keyRelease(os, key, modifiers);
}
#undef GT_METHOD_NAME

void GTKeyboardDriver::keySequence(GUITestOpStatus &os, const QString &str, Qt::KeyboardModifiers modifiers)
{
    QList<Qt::Key> modifierKeys = modifiersToKeys(modifiers);
    foreach (Qt::Key mod, modifierKeys) {
        keyPress(os, mod);
    }

    foreach(QChar ch, str) {
        char asciiChar = ch.toLatin1();
        if(isalpha(asciiChar) && !islower(asciiChar)) {
            keyClick(os, asciiChar, Qt::ShiftModifier);
        } else {
            keyClick(os, asciiChar);
        }
#ifdef  Q_OS_MAC
        GTGlobals::sleep(10); // need for MacOS
        GTThread::waitForMainThread(os);
#endif
    }

    foreach (Qt::Key mod, modifierKeys) {
        keyRelease(os, mod);
    }
    GTThread::waitForMainThread(os);
}

/******************************************************************************/
int GTKeyboardDriver::keys::operator [] (const Qt::Key &key) const
{
    return value(key);
}

GTKeyboardDriver::keys GTKeyboardDriver::key;

#undef GT_CLASS_NAME

} //namespace
