#Human Imitator (humimit) [![Build Status](https://travis-ci.org/ugeneunipro/humimit.svg?branch=master)]	(https://travis-ci.org/ugeneunipro/humimit)

## Introduction
`HumImit` is a GUI testing library for Qt desktop applications.

## Writing Tests
You need create declarations for tests like follow:
```cpp
#include <core/GUITest.h>
#define GUI_TEST_SUITE "My_base_tests"
    TEST_CLASS_DECLARATION(Test1)
    TEST_CLASS_DECLARATION(Test2)
#undef GUI_TEST_SUITE
```
Also need create definitions of tests:
```cpp
TEST_CLASS_DEFINITION(Test1){
    //body of test
}

TEST_CLASS_DEFINITION(Test2){
    //body of test
}
```
After this you need implement `GUITestsLauncher`:
```cpp
#include <core/GUITestsLauncher.h>
class MyGUITestsLauncher: public GUITestsLauncher
{
public:
    MyGUITestsLauncher();
};
```
```cpp
MyGUITestsLauncher::MyGUITestsLauncher(): GUITestsLauncher()
{
    guiTestBase.registerTest(new Test1());
    guiTestBase.registerTest(new Test2());
}
```
In main function of your application you need add something like this:
```cpp
    QString runGuiTest = qgetenv("HI_GUI_TEST");
    if (!runGuiTest.isEmpty()) {
        MyGUITestsLauncher* tests = new MyGUITestsLauncher();
        tests->connect(&myMainWindow,SIGNAL(si_applicationStarted()),tests,SLOT(sl_runTest()));
    }
```

## Running Tests
A single test can be run just using environment variable 'HI_GUI_TEST'.
For Unix systems:
```bash
export HI_GUI_TEST=<suite_name>:<test_name>
```
or for Windows systems:
```bat
set HI_GUI_TEST=<suite_name>:<test_name>
```
And then execute you application.

## Requirements

Qt5

## License

This project available under GNU GPL V2.
