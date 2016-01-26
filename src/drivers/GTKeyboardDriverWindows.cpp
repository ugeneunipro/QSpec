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
#include <QtGui/QClipboard>

#ifdef _WIN32
    #include <windows.h>
    #define VIRTUAL_TO_SCAN_CODE 0
#endif

namespace HI {

#ifdef _WIN32

#define GT_CLASS_NAME "GTKeyboardDriver Windows"

void GTKeyboardDriver::keyPress(GUITestOpStatus &os, char key, int modifiers)
{
    if (isalpha(key)) {
        key = toupper(key);
    }

    switch (key) {
        case '-':
            if (modifiers != 0) {
                keyPress(os, modifiers);
            }
            keyPress(os, VK_OEM_MINUS);
            break;

        case '_':
            if (modifiers != 0) {
                keyPress(os, modifiers);
            }
            keyPress(os, VK_OEM_MINUS, GTKeyboardDriver::key["shift"]);
            break;

        case '=':
            if (modifiers != 0) {
                keyPress(os, modifiers);
            }
            keyPress(os, VK_OEM_PLUS, modifiers);
            break;

        case '.':
            keyPress(os, VK_DECIMAL, modifiers);
            break;

        case ',':
            keyPress(os, VK_OEM_COMMA, modifiers);
            break;

        case ']':
            keyPress(os, VK_OEM_6, modifiers);
            break;

        case '\\':
            keyPress(os, VK_OEM_5, modifiers);
            break;

        case '[':
            keyPress(os, VK_OEM_4, modifiers);
            break;

        case '/':
            keyPress(os, VK_DIVIDE, modifiers);
            break;

        case '\n':
            keyPress(os, GTKeyboardDriver::key["enter"], modifiers);
            break;

        case ':':
            if (modifiers != 0) {
                keyPress(os, modifiers);
            }
            keyPress(os, VK_OEM_1, GTKeyboardDriver::key["shift"]);
            break;
        case ';':
            if (modifiers != 0) {
                keyPress(os, modifiers);
            }
            keyPress(os, VK_OEM_1);
            break;
        case '<':
             if (modifiers != 0) {
                keyPress(os, modifiers);
            }
            keyPress(os, VK_OEM_COMMA, GTKeyboardDriver::key["shift"]);
            break;
        case '>':
             if (modifiers != 0) {
                keyPress(os, modifiers);
            }
            keyPress(os, VK_OEM_PERIOD, GTKeyboardDriver::key["shift"]);
            break;
        case '(':
             if (modifiers != 0) {
                keyPress(os, modifiers);
            }
            keyPress(os, '9', GTKeyboardDriver::key["shift"]);
            break;
        case ')':
             if (modifiers != 0) {
                keyPress(os, modifiers);
            }
            keyPress(os, '0', GTKeyboardDriver::key["shift"]);
            break;
        case '"':
            if (modifiers != 0) {
                keyPress(os, modifiers);
            }
            keyPress(os, VK_OEM_7, GTKeyboardDriver::key["shift"]);
            break;
        case '!':
            if (modifiers != 0) {
                keyPress(os, modifiers);
            }
            keyPress(os, '1', GTKeyboardDriver::key["shift"]);
            break;
        case '@':
            if (modifiers != 0) {
                keyPress(os, modifiers);
            }
            keyPress(os, '2', GTKeyboardDriver::key["shift"]);
            break;
        case '#':
            if (modifiers != 0) {
                keyPress(os, modifiers);
            }
            keyPress(os, '3', GTKeyboardDriver::key["shift"]);
            break;
        case '$':
            if (modifiers != 0) {
                keyPress(os, modifiers);
            }
            keyPress(os, '4', GTKeyboardDriver::key["shift"]);
            break;
        case '%':
            if (modifiers != 0) {
                keyPress(os, modifiers);
            }
            keyPress(os, '5', GTKeyboardDriver::key["shift"]);
            break;
        case '^':
            if (modifiers != 0) {
                keyPress(os, modifiers);
            }
            keyPress(os, '6', GTKeyboardDriver::key["shift"]);
            break;
        case '&':
            if (modifiers != 0) {
                keyPress(os, modifiers);
            }
            keyPress(os, '7', GTKeyboardDriver::key["shift"]);
            break;
        case '*':
            if (modifiers != 0) {
                keyPress(os, modifiers);
            }
            keyPress(os, '8', GTKeyboardDriver::key["shift"]);
            break;
        case '+':
            if (modifiers != 0) {
                keyPress(os, modifiers);
            }
            keyPress(os, VK_OEM_PLUS, GTKeyboardDriver::key["shift"]);
            break;
        case '?':
            if (modifiers != 0) {
                keyPress(os, modifiers);
            }
            keyPress(os, VK_OEM_2, GTKeyboardDriver::key["shift"]);
            break;
        default:
            keyPress(os, (int)key, modifiers);
            break;
    }
}

void GTKeyboardDriver::keyRelease(GUITestOpStatus &os, char key, int modifiers)
{
    if (isalpha(key)) {
        key = toupper(key);
    }

    switch (key) {
        case '_':
            keyRelease(os, VK_OEM_MINUS, GTKeyboardDriver::key["shift"]);
            if (modifiers != 0) {
                keyRelease(os, modifiers);
            }
            break;

        case '=':
            keyRelease(os, VK_OEM_PLUS);
            if (modifiers != 0) {
                keyRelease(os, modifiers);
            }
            break;

        case '.':
            keyRelease(os, VK_DECIMAL, modifiers);
            break;

        case ',':
            keyRelease(os, VK_OEM_COMMA, modifiers);
            break;

        case ']':
            keyRelease(os, VK_OEM_6, modifiers);
            break;

        case '\\':
            keyRelease(os, VK_OEM_5, modifiers);
            break;

        case '[':
            keyRelease(os, VK_OEM_4, modifiers);
            break;

        case '/':
            keyRelease(os, VK_DIVIDE, modifiers);
            break;

        case '\n':
            keyRelease(os, GTKeyboardDriver::key["enter"], modifiers);
            break;

        case ':':
            keyRelease(os, VK_OEM_1, GTKeyboardDriver::key["shift"]);
            if (modifiers != 0) {
                keyRelease(os, modifiers);
            }
            break;
        case ';':
            keyRelease(os, VK_OEM_1);
            if (modifiers != 0) {
                keyRelease(os, modifiers);
            }
            break;
        case '<':
            keyRelease(os, VK_OEM_COMMA, GTKeyboardDriver::key["shift"]);
            if (modifiers != 0) {
                keyRelease(os, modifiers);
            }
            break;
        case '>':
            keyRelease(os, VK_OEM_PERIOD, GTKeyboardDriver::key["shift"]);
            if (modifiers != 0) {
                keyRelease(os, modifiers);
            }
            break;
        case '(':
            keyRelease(os, '9', GTKeyboardDriver::key["shift"]);
            if (modifiers != 0) {
                keyRelease(os, modifiers);
            }
            break;
        case ')':
            keyRelease(os, '0', GTKeyboardDriver::key["shift"]);
            if (modifiers != 0) {
                keyRelease(os, modifiers);
            }
            break;
        case '"':
            keyRelease(os, VK_OEM_7, GTKeyboardDriver::key["shift"]);
            if (modifiers != 0) {
                keyRelease(os, modifiers);
            }
            break;
        case '!':
            keyRelease(os, '1', GTKeyboardDriver::key["shift"]);
            if (modifiers != 0) {
                keyRelease(os, modifiers);
            }
            break;
        case '@':
            keyRelease(os, '2', GTKeyboardDriver::key["shift"]);
            if (modifiers != 0) {
                keyRelease(os, modifiers);
            }
            break;
        case '#':
            keyRelease(os, '3', GTKeyboardDriver::key["shift"]);
            if (modifiers != 0) {
                keyRelease(os, modifiers);
            }
            break;
        case '$':
            keyRelease(os, '4', GTKeyboardDriver::key["shift"]);
            if (modifiers != 0) {
                keyRelease(os, modifiers);
            }
            break;
        case '%':
            keyRelease(os, '5', GTKeyboardDriver::key["shift"]);
            if (modifiers != 0) {
                keyRelease(os, modifiers);
            }
            break;
        case '^':
            keyRelease(os, '6', GTKeyboardDriver::key["shift"]);
            if (modifiers != 0) {
                keyRelease(os, modifiers);
            }
            break;
        case '&':
            keyRelease(os, '7', GTKeyboardDriver::key["shift"]);
            if (modifiers != 0) {
                keyRelease(os, modifiers);
            }
            break;
        case '*':
            keyRelease(os, '8', GTKeyboardDriver::key["shift"]);
            if (modifiers != 0) {
                keyRelease(os, modifiers);
            }
            break;
        case '+':
            keyRelease(os, VK_OEM_PLUS, GTKeyboardDriver::key["shift"]);
            if (modifiers != 0) {
                keyRelease(os, modifiers);
            }
            break;
        case '?':
            keyRelease(os, VK_OEM_2, GTKeyboardDriver::key["shift"]);
            if (modifiers != 0) {
                keyRelease(os, modifiers);
            }
            break;
        default:
            keyRelease(os, (int)key, modifiers);
            break;
    }
}

#define GT_METHOD_NAME "keyClick"
void GTKeyboardDriver::keyClick(GUITestOpStatus &os, char key, int modifiers)
{
    GT_CHECK(key != 0, "key = 0");

    keyPress(os, key, modifiers);
    keyRelease(os, key, modifiers);
    GTGlobals::sleep(10);
}
#undef GT_METHOD_NAME

void GTKeyboardDriver::keyClick(GUITestOpStatus &os, char key, QList<int> modifiers){
    switch (modifiers.size()) {
    case 0:
        keyClick(os, key);
        break;
    case 1:
        keyClick(os, key, modifiers.first());
        break;
    default:
        int modifier = modifiers.takeLast();
        foreach (int mod, modifiers) {
            keyPress(os, mod);
        }
        keyClick(os, key, modifier);
        foreach (int mod, modifiers) {
            keyRelease(os, mod);
        }
        break;
    }
}

INPUT GTKeyboardDriver::getKeyEvent(int key, bool keyUp) {

    INPUT event;
    event.type = INPUT_KEYBOARD;
    event.ki.wVk = key;
    event.ki.wScan = MapVirtualKey(key, VIRTUAL_TO_SCAN_CODE);
    event.ki.dwFlags = keyUp ? KEYEVENTF_KEYUP : 0;
    event.ki.time = 0;
    event.ki.dwExtraInfo = 0;
    event.ki.dwFlags |= KEYEVENTF_EXTENDEDKEY;

    return event;
}

#define GT_METHOD_NAME "keyPress"
void GTKeyboardDriver::keyPress(GUITestOpStatus &os, int key, int modifiers) {

    GT_CHECK(key != 0, " Error: key = 0 in GTKeyboardDriver::keyPress()");

    if (modifiers) {
        INPUT input = getKeyEvent(modifiers);
        SendInput(1, &input, sizeof(input));
    }

    INPUT input = getKeyEvent(key);
    SendInput(1, &input, sizeof(input));
}
#undef GT_METHOD_NAME

#define GT_METHOD_NAME "keyRelease"
void GTKeyboardDriver::keyRelease(GUITestOpStatus &os, int key, int modifiers)
{
    GT_CHECK(key != 0, " Error: key = 0 in GTKeyboardDriver::keyRelease()");

    if (modifiers) {
        INPUT input = getKeyEvent(modifiers, true);
        SendInput(1, &input, sizeof(input));
    }

    INPUT input = getKeyEvent(key, true);
    SendInput(1, &input, sizeof(input));
}
#undef GT_METHOD_NAME

GTKeyboardDriver::keys::keys()
{
    ADD_KEY("context_menu", VK_APPS);
    ADD_KEY("back", VK_BACK);
    ADD_KEY("tab", VK_TAB);
    ADD_KEY("clear", VK_CLEAR);
    ADD_KEY("enter", VK_RETURN);
    ADD_KEY("shift", VK_SHIFT);
    ADD_KEY("rshift", VK_RSHIFT);
    ADD_KEY("lshift", VK_LSHIFT);
    ADD_KEY("ctrl", VK_CONTROL);
    ADD_KEY("rctrl", VK_RCONTROL);
    ADD_KEY("lctrl", VK_LCONTROL);
    ADD_KEY("alt", VK_MENU);
    ADD_KEY("pause", VK_PAUSE);
    ADD_KEY("esc", VK_ESCAPE);
    ADD_KEY("space", VK_SPACE);
    ADD_KEY("left", VK_LEFT);
    ADD_KEY("up", VK_UP);
    ADD_KEY("right", VK_RIGHT);
    ADD_KEY("down", VK_DOWN);
    ADD_KEY("insert", VK_INSERT);
    ADD_KEY("delete", VK_DELETE);
    ADD_KEY("pageup", VK_PRIOR);
    ADD_KEY("pagedown", VK_NEXT);
    ADD_KEY("help", VK_HELP);
    ADD_KEY("f1", VK_F1);
    ADD_KEY("f2", VK_F2);
    ADD_KEY("f3", VK_F3);
    ADD_KEY("f4", VK_F4);
    ADD_KEY("f5", VK_F5);
    ADD_KEY("f6", VK_F6);
    ADD_KEY("f7", VK_F7);
    ADD_KEY("f8", VK_F8);
    ADD_KEY("f9", VK_F9);
    ADD_KEY("f10", VK_F10);
    ADD_KEY("f12", VK_F12);
    ADD_KEY("home", VK_HOME);
    ADD_KEY("end", VK_END);

// feel free to add other keys
// macro VK_* defined in WinUser.h
}

#undef GT_CLASS_NAME

#endif

} //namespace
