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

#if defined __linux__
    #define XK_LATIN1      // for latin symbol
    #define XK_MISCELLANY  // for action keys
    #include <X11/keysymdef.h>
    #include <X11/extensions/XTest.h>
#endif

namespace HI {

#if defined __linux__

#define GT_CLASS_NAME "GTKeyboardDriverLinux"

#define GT_METHOD_NAME "keyPress"
void GTKeyboardDriver::keyPress(GUITestOpStatus &os, int key, int modifiers)
{
    GT_CHECK_NO_MESSAGE(key != 0, "key = 0");

    QByteArray display_name = qgetenv("DISPLAY");
    GT_CHECK_NO_MESSAGE(!display_name.isEmpty(), "Environment variable \"DISPLAY\" not found");

    Display *display = XOpenDisplay(display_name.constData());
    GT_CHECK_NO_MESSAGE(display != 0, "display is NULL");

    if (modifiers) {
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, modifiers), 1, 0);
    }

    switch(key) {
    case '\n':
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key["enter"]), 1, 0);
        break;
    case '_':
        key = '-';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key["shift"]), 1, 0);
        break;
    case '<':
        key = ',';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key["shift"]), 1, 0);
        break;
    case '>':
        key = '.';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key["shift"]), 1, 0);
        break;
    case '(':
        key = '9';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key["shift"]), 1, 0);
        break;
    case '$':
        key = '4';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key["shift"]), 1, 0);
        break;
    case '#':
        key = '3';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key["shift"]), 1, 0);
        break;
    case ')':
        key = '0';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key["shift"]), 1, 0);
        break;
    case ':':
        key = ';';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key["shift"]), 1, 0);
        break;
    case '*':
        key = '8';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key["shift"]), 1, 0);
        break;
    case '\"':
        key = '\'';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key["shift"]), 1, 0);
        break;
    case '@':
        key = '2';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key["shift"]), 1, 0);
        break;
    case '%':
        key = '5';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key["shift"]), 1, 0);
        break;
    case '^':
        key = '6';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key["shift"]), 1, 0);
        break;
    case '&':
        key = '7';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key["shift"]), 1, 0);
        break;
    case '+':
        key = '=';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key["shift"]), 1, 0);
        break;
    case '{':
        key = '[';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key["shift"]), 1, 0);
        break;
    case '}':
        key = ']';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key["shift"]), 1, 0);
        break;
    case '|':
        key = '\\';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key["shift"]), 1, 0);
        break;
    case '!':
        key = '1';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key["shift"]), 1, 0);
        break;
    }

    XTestFakeKeyEvent(display, XKeysymToKeycode(display, key), 1, 0);
    XFlush(display);

    XCloseDisplay(display);
}
#undef GT_METHOD_NAME

#define GT_METHOD_NAME "keyRelease"
void GTKeyboardDriver::keyRelease(GUITestOpStatus &os, int key, int modifiers)
{
    GT_CHECK_NO_MESSAGE(key != 0, "key = ");

    QByteArray display_name = qgetenv("DISPLAY");
    GT_CHECK_NO_MESSAGE(!display_name.isEmpty(), "Environment variable \"DISPLAY\" not found");

    Display *display = XOpenDisplay(display_name.constData());
    GT_CHECK_NO_MESSAGE(display != 0, "display is NULL");

    switch(key) {
    case '\n':
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key["enter"]), 0, 0);
        break;
    case '_':
        key = '-';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, key), 0, 0);
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key["shift"]), 0, 0);
        break;

    case '<':
        key = ',';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, key), 0, 0);
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key["shift"]), 0, 0);
        break;

    case '>':
        key = '.';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, key), 0, 0);
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key["shift"]), 0, 0);
        break;

    case '(':
        key = '9';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, key), 0, 0);
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key["shift"]), 0, 0);
        break;

    case '$':
        key = '4';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, key), 0, 0);
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key["shift"]), 0, 0);
        break;

    case '#':
        key = '3';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, key), 0, 0);
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key["shift"]), 0, 0);
        break;

    case ')':
        key = '0';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, key), 0, 0);
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key["shift"]), 0, 0);
        break;

    case ':':
        key = ';';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, key), 0, 0);
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key["shift"]), 0, 0);
        break;

    case '*':
        key = '8';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, key), 0, 0);
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key["shift"]), 0, 0);
        break;

    case '\"':
        key = '\'';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, key), 0, 0);
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key["shift"]), 0, 0);
        break;
    case '@':
        key = '2';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, key), 0, 0);
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key["shift"]), 0, 0);
        break;
    case '%':
        key = '5';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, key), 0, 0);
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key["shift"]), 0, 0);
        break;
    case '^':
        key = '6';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, key), 0, 0);
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key["shift"]), 0, 0);
        break;
    case '&':
        key = '7';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, key), 0, 0);
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key["shift"]), 0, 0);
        break;
    case '+':
        key = '=';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, key), 0, 0);
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key["shift"]), 0, 0);
        break;
    case '{':
        key = '[';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, key), 0, 0);
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key["shift"]), 0, 0);
        break;
    case '}':
        key = ']';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, key), 0, 0);
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key["shift"]), 0, 0);
        break;
    case '|':
        key = '\\';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, key), 0, 0);
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key["shift"]), 0, 0);
        break;
    case '!':
        key = '1';
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, key), 0, 0);
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, GTKeyboardDriver::key["shift"]), 0, 0);
        break;

    default:
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, key), 0, 0);
    }

    if (modifiers) {
        XTestFakeKeyEvent(display, XKeysymToKeycode(display, modifiers), 0, 0);
    }
    XFlush(display);

    XCloseDisplay(display);
}
#undef GT_METHOD_NAME

GTKeyboardDriver::keys::keys()
{
    ADD_KEY("context_menu", XK_Menu);
    ADD_KEY("back", XK_BackSpace);
    ADD_KEY("tab", XK_Tab);
    ADD_KEY("clear", XK_Clear);
    ADD_KEY("enter", XK_Return);
    ADD_KEY("shift", XK_Shift_L);
    ADD_KEY("rshift", XK_Shift_R);
    ADD_KEY("lshift", XK_Shift_L);
    ADD_KEY("ctrl", XK_Control_L);
    ADD_KEY("rctrl", XK_Control_R);
    ADD_KEY("lctrl", XK_Control_L);
    ADD_KEY("alt", XK_Alt_L);
    ADD_KEY("pause", XK_Pause);
    ADD_KEY("esc", XK_Escape);
    ADD_KEY("space", XK_space);
    ADD_KEY("left", XK_Left);
    ADD_KEY("up", XK_Up);
    ADD_KEY("right", XK_Right);
    ADD_KEY("down", XK_Down);
    ADD_KEY("insert", XK_Insert);
    ADD_KEY("delete", XK_Delete);
    ADD_KEY("help", XK_Help);
    ADD_KEY("f1", XK_F1);
    ADD_KEY("f2", XK_F2);
    ADD_KEY("f3", XK_F3);
    ADD_KEY("f4", XK_F4);
    ADD_KEY("f5", XK_F5);
    ADD_KEY("f6", XK_F6);
    ADD_KEY("f7", XK_F7);
    ADD_KEY("f8", XK_F8);
    ADD_KEY("f9", XK_F9);
    ADD_KEY("f10", XK_F10);
    ADD_KEY("f12", XK_F12);
    ADD_KEY("home", XK_Home);
    ADD_KEY("end", XK_End);
    ADD_KEY("pageup", XK_Page_Up);
    ADD_KEY("pagedown", XK_Page_Down);

// feel free to add other keys
// macro XK_* defined in X11/keysymdef.h
}

#undef GT_CLASS_NAME

#endif

} //namespace
