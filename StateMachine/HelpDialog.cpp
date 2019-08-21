#include "HelpDialog.h"
#include "ui_HelpDialog.h"
#include <QDebug>

HelpDialog::HelpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpDialog)
{
    ui->setupUi(this);

    // support to show image that keeps aspect ratio inside QLabel
    // note: intention here is to allow users to set image although the aspect ratio as shown
    // on designer UI isn't correct yet, but it will be in runtime every time the widget containing
    // a target QLabel (which has our image) changes its size
    //
    // This approach requires QLabel to have fixed size set Size constraints, then we just need the following section of code
    // to be here, and no need to be at every time its size has changed
    const int imageContainerWidth = ui->image->width();
    const int imageContainerHeight = ui->image->height();
    qDebug() << "width: " << imageContainerWidth << "\nheight: " << imageContainerHeight;
    const QPixmap *p = ui->image->pixmap();
    ui->image->setPixmap(p->scaled(imageContainerWidth, imageContainerHeight, Qt::AspectRatioMode::KeepAspectRatio));
}

HelpDialog::~HelpDialog()
{
    delete ui;
}
