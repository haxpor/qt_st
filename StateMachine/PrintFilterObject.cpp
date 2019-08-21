#include "PrintFilterObject.h"

#include "dialog.h"
#include <QEvent>
#include <QResizeEvent>
#include <QDebug>

PrintFilterObject::PrintFilterObject(QDialog *target, QObject *parent) : QObject(parent),
    targetDialog(target)
{
    targetDialog->installEventFilter(this);
}

bool PrintFilterObject::eventFilter(QObject *target, QEvent *event)
{
    if (target == targetDialog) {
        if (event->type() == QEvent::Resize)
        {
            QResizeEvent *resizeEvent = static_cast<QResizeEvent*>(event);
            qDebug() << "Resized monitored dialog to (width: " << std::to_string(resizeEvent->size().width()).c_str() <<
                        "," << std::to_string(resizeEvent->size().height()).c_str() << ")\n";
            // we just want to detect this event but not consume it, so this won't return true immediately
            return false;
        }
    }
    // according to https://doc.qt.io/qt-5/qobject.html#eventFilter
    // pass through the logic and let its base class operates further
    return QObject::eventFilter(target, event);
}
