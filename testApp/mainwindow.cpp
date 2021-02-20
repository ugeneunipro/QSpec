#include "mainwindow.h"

#include <QEvent>
#include <QGridLayout>
#include <QKeyEvent>
#include <QLineEdit>

#include "EventFilter.h"
#include "EventRecorderWidget.h"

MainWindow *MainWindow::instance;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    QGridLayout *l = new QGridLayout(this);
    setLayout(l);

    testLine = new QLineEdit(this);
    testLine->setObjectName("testLine");
    l->addWidget(testLine, 0, 0, 5, 5);

    eventFilter = new EventFilter(this);

    eventRecorderWidget = new EventRecorderWidget(this);
    eventRecorderWidget->setObjectName("eventRecorder");
    eventRecorderWidget->installEventFilter(eventFilter);
    l->addWidget(eventRecorderWidget, 1, 0, 5, 5);
}

MainWindow::~MainWindow() {
}

MainWindow *MainWindow::getInstance() {
    if (instance == NULL) {
        instance = new MainWindow();
    }
    return instance;
}
