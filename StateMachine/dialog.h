#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

// forward declaration, we only store pointers here
class QState;
class QStateMachine;

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    // slot notified when state has been changed, kindly use sender() to check
    // which particular state it should be
    void stateChanged();

private:
    Ui::Dialog *ui;

    /** relevant of statemachine variables
     * possible routes of state changing is as follows
     * 1. A->B
     * 2. B->C
     * 3. C->A
     * 4. A->C
     */
    QState *stateA;
    QState *stateB;
    QState *stateC;
    QStateMachine *stateMachine;
};

#endif // DIALOG_H
