#include "Dialog.h"
#include "ui_Dialog.h"
#include <QFlags>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent, Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint), // nicely disable expand cursor icon when hover on the edge of the dialog window
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}
