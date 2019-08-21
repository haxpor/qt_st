#include "QtGuiApplication1.h"
#include <QDebug>

QtGuiApplication1::QtGuiApplication1(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton, &QPushButton::clicked, this, [=] {
		qDebug() << "Clicked on pushButton_1";
	});
	connect(ui.pushButton_2, &QPushButton::clicked, this, [=] {
		qDebug() << "Clicked on pushButton_2";
		fictionalFunction();
	});
}

void QtGuiApplication1::fictionalFunction()
{
	qDebug() << "Called from fictional Function";
}