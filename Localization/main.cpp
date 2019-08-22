#include "Dialog.h"
#include <QApplication>
#include <QTranslator>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;

    // only way to show translated text on UI is to put all those .qm files into resource file
    // then load it like this :/myfile.qm, or :/dir1/dir2/myfile.qm
    // the process of putting translation into qt project is as follows
    // 0. add `TRANSLATION = res/trans_la.ts` inside .pro file
    // 1. add resource file (.qrc), inside add res/trans_la.ts
    // 2. execute `lupdate -verbose <project-file.pro>` to generate .ts files as mentioned in .pro file
    // 3. add relevant code to create QTranslator and load translator file like you see in this file; at main.cpp.
    // 4. use qt linguist to edit translations. Run it via `linguist <ts-file>` or just open it with `linguist` then use GUI to open a desire file
    // 5. execute `lrelease-pro <profile-file>` to generate corresponding .qm files
    bool result = translator.load(":/res/hellotr_la.qm");
    if (result)
    {
        qDebug() << "Loaded .ts ok";
        a.installTranslator(&translator);
    }

    Dialog w;
    w.show();

    return a.exec();
}
