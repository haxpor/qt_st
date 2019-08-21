#include "dialog.h"
#include <QApplication>
#include "PrintFilterObject.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Dialog w;
    PrintFilterObject filterObj(&w);
    w.show();

    return a.exec();
}
