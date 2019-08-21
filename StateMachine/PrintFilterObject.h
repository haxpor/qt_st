#ifndef PRINTFILTEROBJECT_H
#define PRINTFILTEROBJECT_H

#include <QObject>

class QDialog;

class PrintFilterObject : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief PrintFilterObject prints simple event as happened on input target onto debugging console.
     * After this constructor, it will register event filter onto input target, and do its works.
     *
     * @param target An QDialog to be monitored for its events
     * @param parent Parent object that owns this object
     */
    explicit PrintFilterObject(QDialog *target, QObject *parent = nullptr);

    virtual bool eventFilter(QObject *watched, QEvent *event) override;

private:
    QDialog *targetDialog;
};

#endif // PRINTFILTEROBJECT_H
