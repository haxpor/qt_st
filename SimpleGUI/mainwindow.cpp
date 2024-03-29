#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->mySlider, SIGNAL(valueChanged(int)), ui->myProgressbar, SLOT(setValue(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
