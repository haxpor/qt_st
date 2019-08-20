#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    QStringList languages = {"C++", "Python", "C#", "Java", "Ruby", "PHP"};
    for (const auto &l : languages)
    {
        ui->listWidget->addItem(l);
    }
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_3_clicked()
{
    QListWidgetItem *item = ui->listWidget->currentItem();
    item->setForeground(QBrush(Qt::red));
}

void Dialog::on_pushButton_2_clicked()
{

}
