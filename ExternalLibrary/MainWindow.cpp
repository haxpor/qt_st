#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "SimpleLib.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    SimpleLib::Calc calc;
    qDebug() << "SimpleLib::Calc.Add(10, 5.5)=" << calc.Add(10, 5.5);
}

MainWindow::~MainWindow()
{
    delete ui;
}
