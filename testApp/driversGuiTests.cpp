#include "driversGuiTests.h"
#include "mainwindow.h"
#include "EventFilter.h"

#include <primitives/GTWidget.h>
#include <drivers/GTKeyboardDriver.h>

#include <QApplication>
#include <QLineEdit>
#include <primitives/GTLineEdit.h>

using namespace HI;
driversGuiTestsLauncher::driversGuiTestsLauncher(): GUITestsLauncher()
{
    guiTestBase.registerTest(new Test1());
    guiTestBase.registerTest(new Test2());
    guiTestBase.registerTest(new Test3());
    guiTestBase.registerTest(new Test4());
}

TEST_CLASS_DEFINITION(Test1){
    QLineEdit* line = GTWidget::findExactWidget<QLineEdit*>(os, "testLine");
    GTWidget::click(os, line);
    GTGlobals::sleep();
    GTKeyboardDriver::keySequence(os, "abcdefghigklmnopqrstuvwxy z");
	CHECK_SET_ERR(line->text() == "abcdefghigklmnopqrstuvwxy z", "expected: abcdefghigklmnopqrstuvwxy z, actual: " + line->text())
	GTGlobals::sleep(500);
}

TEST_CLASS_DEFINITION(Test2){
    QLineEdit* line = GTWidget::findExactWidget<QLineEdit*>(os, "testLine");
    GTWidget::click(os, line);
    //GTGlobals::sleep();
    GTKeyboardDriver::keySequence(os, "0123456789,<.>!@#$%^&*()-_=+[{]};:\'\"/\\|");
    CHECK_SET_ERR(line->text() == "0123456789,<.>!@#$%^&*()-_=+[{]};:\'\"/\\|", "expected: 0123456789,<.>!@#$%^&*()-_=+[{]};:\'\"/\\|, actual: " + line->text())
	GTGlobals::sleep(500);
}

TEST_CLASS_DEFINITION(Test3){
    QWidget* recorder = GTWidget::findWidget(os, "eventRecorder");
    GTWidget::click(os, recorder);
    GTKeyboardDriver::keyClick(os, Qt::Key_Up);
    GTGlobals::sleep(500);

    QList<KeyEvent> list = MainWindow::getInstance()->eventFilter->keyEvents;
    int i = list.size();
    CHECK_SET_ERR(i == 2, QString("unexpected number of key events: %1").arg(i));
    CHECK_SET_ERR(list.first().getKey() == Qt::Key_Up, QString("unexpected first key: %1").arg(list.first().getKey()));
    CHECK_SET_ERR(list.first().getType() == QEvent::KeyPress, QString("unexpected first type: %1").arg(list.first().getType()));
    CHECK_SET_ERR(list.last().getKey() == Qt::Key_Up, QString("unexpected second key: %1").arg(list.last().getKey()));
    CHECK_SET_ERR(list.last().getType() == QEvent::KeyRelease, QString("unexpected second type: %1").arg(list.last().getType()));
}

TEST_CLASS_DEFINITION(Test4){
    QWidget* recorder = GTWidget::findWidget(os, "eventRecorder");
    GTWidget::click(os, recorder);
    GTKeyboardDriver::keyClick(os, Qt::Key_Enter, Qt::ControlModifier);
    GTGlobals::sleep(500);

    QList<KeyEvent> list = MainWindow::getInstance()->eventFilter->keyEvents;
    int i = list.size();

    CHECK_SET_ERR(i == 4, QString("unexpected number of key events: %1").arg(i));

    CHECK_SET_ERR(list[0].getKey() == Qt::Key_Control, QString("unexpected 1 key: %1").arg(list[0].getKey()));
    CHECK_SET_ERR(list[0].getType() == QEvent::KeyPress, QString("unexpected 1 type: %1").arg(list[0].getType()));

    CHECK_SET_ERR(list[1].getKey() == Qt::Key_Return, QString("unexpected 2 key: %1").arg(list[1].getKey()));
    CHECK_SET_ERR(list[1].getType() == QEvent::KeyPress, QString("unexpected 2 key: %1").arg(list[1].getType()));

    CHECK_SET_ERR(list[2].getKey() == Qt::Key_Return, QString("unexpected 3 key: %1").arg(list[2].getKey()));
    CHECK_SET_ERR(list[2].getType() == QEvent::KeyRelease, QString("unexpected 3 type: %1").arg(list[2].getType()));

    CHECK_SET_ERR(list[3].getKey() == Qt::Key_Control, QString("unexpected 4 key: %1").arg(list[3].getKey()));
    CHECK_SET_ERR(list[3].getType() == QEvent::KeyRelease, QString("unexpected 4 type: %1").arg(list[3].getType()));
}
