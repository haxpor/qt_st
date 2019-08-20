#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->comboBox->addItem(QStringLiteral("Item 1"));
    ui->comboBox->addItem(QStringLiteral("Item 2"));
    ui->comboBox->addItem(QStringLiteral("Item 3"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->label->setText(ui->comboBox->currentText());
}
