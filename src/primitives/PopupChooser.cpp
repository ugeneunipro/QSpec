/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2017 UniPro <ugene@unipro.ru>
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

#include "primitives/PopupChooser.h"
#include "drivers/GTKeyboardDriver.h"
#include "primitives/GTMenu.h"
#include "drivers/GTMouseDriver.h"

#include <QApplication>
#include <QMenu>

namespace HI {
#define GT_CLASS_NAME "PopupChooser"

#define GT_METHOD_NAME "run"
void PopupChooser::commonScenario() {
    GTGlobals::sleep(1000);
    GTMouseDriver::release();
    QMenu* activePopupMenu = qobject_cast<QMenu*>(QApplication::activePopupWidget());
    GT_CHECK(NULL != activePopupMenu, "Active popup menu is NULL");

    if (!namePath.isEmpty()) {
        GTMenu::clickMenuItemByName(os, activePopupMenu, namePath, useMethod);
    } else {
        clickEsc(os);
    }

    if (os.hasError()) {
        clickEsc(os);
    }
}
#undef GT_METHOD_NAME

#define GT_METHOD_NAME "clickEsc"
void PopupChooser::clickEsc(GUITestOpStatus &) {
    GTKeyboardDriver::keyClick(Qt::Key_Escape);
}
#undef GT_METHOD_NAME

#undef GT_CLASS_NAME

void PopupChooserByText::commonScenario()
{
    GTGlobals::sleep(1000);
    GTMouseDriver::release();
    QMenu* activePopupMenu = qobject_cast<QMenu*>(QApplication::activePopupWidget());
    GTMenu::clickMenuItemByText(os, activePopupMenu, namePath, useMethod, matchFlag);
}


#define GT_CLASS_NAME "PopupChecker"

#define GT_METHOD_NAME "run"
PopupChecker::PopupChecker(GUITestOpStatus &os, CustomScenario *scenario) :
    Filler(os, GUIDialogWaiter::WaitSettings(QString(), GUIDialogWaiter::Popup), scenario)
{
}

void PopupChecker::commonScenario() {
    GTGlobals::sleep(1000);
    GTMouseDriver::release();
    QMenu* activePopupMenu = qobject_cast<QMenu*>(QApplication::activePopupWidget());
    GT_CHECK(NULL != activePopupMenu, "Active popup menu is NULL");

    QAction* act;
    if (!namePath.isEmpty()) {
        QString actName;
        int escCount = namePath.size();
        if(namePath.size()>1){
            actName = namePath.takeLast();
            GTMenu::clickMenuItemByName(os, activePopupMenu, namePath, useMethod);
            QMenu* activePopupMenuToCheck = qobject_cast<QMenu*>(QApplication::activePopupWidget());
            act = GTMenu::getMenuItem(os, activePopupMenuToCheck, actName);
        }else{
            QMenu* activePopupMenuToCheck = qobject_cast<QMenu*>(QApplication::activePopupWidget());
            actName = namePath.last();
            act = GTMenu::getMenuItem(os, activePopupMenuToCheck, actName);
        }

        if(options.testFlag(Exists)){
            GT_CHECK(act != NULL, "action '" + actName + "' not found");
            qDebug("GT_DEBUG_MESSAGE options.testFlag(Exists)");
        }else{
            GT_CHECK(act == NULL, "action '" + actName + "' unexpectidly found");
        }
        if(options.testFlag(IsEnabled)){
            GT_CHECK(act->isEnabled(), "action '" + act->objectName() + "' is not enabled");
            qDebug("GT_DEBUG_MESSAGE options.testFlag(IsEnabled)");
        }
        if(options.testFlag(IsDisabled)){
            GT_CHECK(!act->isEnabled(), "action '" + act->objectName() + "' is enabled");
            qDebug("GT_DEBUG_MESSAGE options.testFlag(IsDisabled");
        }
        if(options.testFlag(IsChecable)){
            GT_CHECK(act->isCheckable(), "action '" + act->objectName() + "' is not checkable");
            qDebug("GT_DEBUG_MESSAGE options.testFlag(IsChecable)");
        }
        if(options.testFlag(IsChecked)){
            GT_CHECK(act->isChecked(), "action '" + act->objectName() + "' is not checked");
            qDebug("GT_DEBUG_MESSAGE options.testFlag(IsChecked)");
        }
        if (options.testFlag(PopupChecker::IsUnchecked)){
            GT_CHECK(!act->isChecked(), "action '" + act->objectName() + "' is checked");
            qDebug("GT_DEBUG_MESSAGE options.testFlag(IsUnchecked)");
        }
        for(int i = 0; i<escCount; i++){
            PopupChooser::clickEsc(os);
            GTGlobals::sleep(300);
        }
    } else {
        PopupChooser::clickEsc(os);
    }

    if (os.hasError()) {
        PopupChooser::clickEsc(os);
    }
}
#undef GT_METHOD_NAME

#undef GT_CLASS_NAME

#define GT_CLASS_NAME "PopupCheckerByText"

#define GT_METHOD_NAME "run"
PopupCheckerByText::PopupCheckerByText(GUITestOpStatus &os, CustomScenario *scenario) :
    Filler(os, GUIDialogWaiter::WaitSettings(QString(), GUIDialogWaiter::Popup), scenario)
{
}

PopupCheckerByText::PopupCheckerByText(GUITestOpStatus &os,
                                       const QStringList &namePath,
                                       PopupChecker::CheckOptions options,
                                       GTGlobals::UseMethod useMethod) :
    Filler(os, GUIDialogWaiter::WaitSettings(QString(), GUIDialogWaiter::Popup)),
    textPaths(QList<QStringList>() << namePath),
    options(options),
    useMethod(useMethod)
{

}

PopupCheckerByText::PopupCheckerByText(GUITestOpStatus &os,
                                       const QList<QStringList> &namePaths,
                                       PopupChecker::CheckOptions options,
                                       GTGlobals::UseMethod useMethod) :
    Filler(os, GUIDialogWaiter::WaitSettings(QString(), GUIDialogWaiter::Popup)),
    textPaths(namePaths),
    options(options),
    useMethod(useMethod)
{

}

void PopupCheckerByText::commonScenario() {
    GTGlobals::sleep(1000);
    GTMouseDriver::release();
    QMenu* activePopupMenu = qobject_cast<QMenu*>(QApplication::activePopupWidget());
    GT_CHECK(NULL != activePopupMenu, "Active popup menu is NULL");

    QAction* act;

    if (textPaths.isEmpty() || textPaths.first().isEmpty()) {
        PopupChooser::clickEsc(os);
        return;
    }

    foreach (QStringList textPath, textPaths) {
        QString actName;
        int escCount = textPath.size();
        if(textPath.size()>1){
            actName = textPath.takeLast();
            GTMenu::clickMenuItemByText(os, activePopupMenu, textPath, useMethod);
            QMenu* activePopupMenuToCheck = qobject_cast<QMenu*>(QApplication::activePopupWidget());
            act = GTMenu::getMenuItem(os, activePopupMenuToCheck, actName, true);
        }else{
            QMenu* activePopupMenuToCheck = qobject_cast<QMenu*>(QApplication::activePopupWidget());
            actName = textPath.last();
            act = GTMenu::getMenuItem(os, activePopupMenuToCheck, actName, true);
        }

        if(options.testFlag(PopupChecker::Exists)){
            GT_CHECK(act != NULL, "action '" + actName + "' not found");
            qDebug("GT_DEBUG_MESSAGE options.testFlag(Exists)");
        }else{
            GT_CHECK(act == NULL, "action '" + actName + "' unexpectidly found");
        }
        if(options.testFlag(PopupChecker::IsEnabled)){
            GT_CHECK(act->isEnabled(), "action '" + act->objectName() + "' is not enabled");
            qDebug("GT_DEBUG_MESSAGE options.testFlag(IsEnabled)");
        }
        if(options.testFlag(PopupChecker::IsDisabled)){
            GT_CHECK(!act->isEnabled(), "action '" + act->objectName() + "' is enabled");
            qDebug("GT_DEBUG_MESSAGE options.testFlag(IsDisabled");
        }
        if(options.testFlag(PopupChecker::IsChecable)){
            GT_CHECK(act->isCheckable(), "action '" + act->objectName() + "' is not checkable");
            qDebug("GT_DEBUG_MESSAGE options.testFlag(IsChecable)");
        }
        if(options.testFlag(PopupChecker::IsChecked)){
            GT_CHECK(act->isCheckable(), "action '" + act->objectName() + "' is not checked");
            qDebug("GT_DEBUG_MESSAGE options.testFlag(IsChecked)");
        }
        if (options.testFlag(PopupChecker::IsChecked)){
            GT_CHECK(act->isChecked(), "action '" + act->objectName() + "' is not checked");
            qDebug("GT_DEBUG_MESSAGE options.testFlag(IsChecked)");
        } 
        if (options.testFlag(PopupChecker::IsUnchecked)){
            GT_CHECK(!act->isChecked(), "action '" + act->objectName() + "' is checked");
            qDebug("GT_DEBUG_MESSAGE options.testFlag(IsUnchecked)");
        }
        for (int i = 0; i < escCount - 1; i++) {
            PopupChooser::clickEsc(os);
            GTGlobals::sleep(300);
        }
    }

    PopupChooser::clickEsc(os);
}
#undef GT_METHOD_NAME

#undef GT_CLASS_NAME
}

