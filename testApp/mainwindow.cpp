#include "mainwindow.h"

#include <QLineEdit>
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    testLine = new QLineEdit(this);
    testLine->setObjectName("testLine");
    this->layout()->addWidget(testLine);
}

MainWindow::~MainWindow()
{

}
