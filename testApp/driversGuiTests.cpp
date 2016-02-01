#include "driversGuiTests.h"

#include <primitives/GTWidget.h>
#include <drivers/GTKeyboardDriver.h>

#include <QLineEdit>
#include <primitives/GTLineEdit.h>

using namespace HI;
driversGuiTestsLauncher::driversGuiTestsLauncher(): GUITestsLauncher()
{
    guiTestBase.registerTest(new Test1());
    guiTestBase.registerTest(new Test2());
}

TEST_CLASS_DEFINITION(Test1){
    QLineEdit* line = GTWidget::findExactWidget<QLineEdit*>(os, "testLine");
    GTWidget::click(os, line);
    GTGlobals::sleep();
    GTKeyboardDriver::keySequence(os, "abcdefghigklmnopqrstuvwxyz");
    CHECK_SET_ERR(line->text() == "abcdefghigklmnopqrstuvwxyz", "expected: abcdefghigklmnopqrstuvwxyz, actual: " + line->text())
}

TEST_CLASS_DEFINITION(Test2){
    QLineEdit* line = GTWidget::findExactWidget<QLineEdit*>(os, "testLine");
    GTWidget::click(os, line);
    //GTGlobals::sleep();
    GTKeyboardDriver::keySequence(os, "0123456789,<.>!@#$%^&*()-_=+[{]};:\'\"/\\|");
    CHECK_SET_ERR(line->text() == "0123456789,<.>!@#$%^&*()-_=+[{]};:\'\"/\\|", "expected: 0123456789,<.>!@#$%^&*()-_=+[{]};:\'\"/\\|, actual: " + line->text())
}
