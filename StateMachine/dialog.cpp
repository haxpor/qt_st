#include "dialog.h"
#include "ui_dialog.h"
#include <QState>
#include <QStateMachine>
#include <QEventTransition>
#include <QPropertyAnimation>
#include <QDebug>

#include "HelpDialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    // animation sets for each state transitioning
    QPropertyAnimation *anim = new QPropertyAnimation(ui->myObject, "geometry");
    anim->setEasingCurve(QEasingCurve::InOutExpo);

    QPropertyAnimation *anim_bypass = new QPropertyAnimation(ui->myObject, "geometry");
    anim->setEasingCurve(QEasingCurve::OutBounce);

    // set up state machine
    // object (myObject) will have 3 states
    stateA = new QState();
    stateA->assignProperty(ui->myObject, "geometry", QRect(30, 30, 70, 31));
    connect(stateA, SIGNAL(entered()), this, SLOT(stateChanged()));

    stateB = new QState();
    stateB->assignProperty(ui->myObject, "geometry", QRect(50, 50, 30, 30));
    connect(stateB, SIGNAL(entered()), this, SLOT(stateChanged()));

    stateC = new QState();
    stateC->assignProperty(ui->myObject, "geometry", QRect(100, 100, 70, 45));
    connect(stateC, SIGNAL(entered()), this, SLOT(stateChanged()));

    // setup state transitions
    QEventTransition *tAB = new QEventTransition(ui->stateChangeNormalButton, QEvent::Type::MouseButtonPress);
    tAB->setTargetState(stateB);
    tAB->addAnimation(anim);
    stateA->addTransition(tAB);

    QEventTransition *tBC = new QEventTransition(ui->stateChangeNormalButton, QEvent::Type::MouseButtonPress);
    tBC->setTargetState(stateC);
    tBC->addAnimation(anim);
    stateB->addTransition(tBC);

    QEventTransition *tCA = new QEventTransition(ui->stateChangeNormalButton, QEvent::Type::MouseButtonPress);
    tCA->setTargetState(stateA);
    tCA->addAnimation(anim);
    stateC->addTransition(tCA);

    QEventTransition *tAC = new QEventTransition(ui->stateChangeSpecialButton, QEvent::Type::MouseButtonPress);
    tAC->setTargetState(stateC);
    tAC->addAnimation(anim_bypass);
    stateA->addTransition(tAC);

    stateMachine = new QStateMachine();
    stateMachine->addState(stateA);
    stateMachine->addState(stateB);
    stateMachine->addState(stateC);
    // add all states first before calling this otherwise it won't work
    stateMachine->setInitialState(stateA);
    stateMachine->start();
}

Dialog::~Dialog()
{
    delete ui;
    delete stateA;
    delete stateB;
    delete stateC;
    delete stateMachine;
}

void Dialog::stateChanged()
{
    // get the sender object to check
    // check this article https://doc.qt.io/archives/qq/qq10-signalmapper.html
    // for sender() approach used to map multiple signals to one
    QState *state = static_cast<QState*>(sender());

    std::string stateStr;
    if (state == this->stateA)
        stateStr = "A";
    else if (state == this->stateB)
        stateStr = "B";
    else if (state == this->stateC)
        stateStr = "C";

    // show on debugging console as well
    qDebug() << "state changed from origin state " << stateStr.c_str();
    // update to status label
    ui->stateStatus->setText(stateStr.c_str());
}

void Dialog::on_pushButton_clicked()
{
    // if no HelpDialog is previously created yet, thus it's not shown yet
    // we will need to show then
    if (!helpDialog)
    {
        // show dialog from HelpDialog.ui
        helpDialog = new HelpDialog(this);

        // connect signal of HelpDialog to this class's slot
        // in order to disconnect any existing signal/slot previously created, then destroy such pointer
        connect(helpDialog, SIGNAL(finished(int)), this, SLOT(onHelpDialogFinished(int)));

        helpDialog->exec();
    }
}

void Dialog::onHelpDialogFinished(int result)
{
    // ignore the input values because even with Rejected result code, it can be happened due to user call finished() with Rejected result code
    // double check if HelpDialog is still existing
    if (helpDialog)
    {
        // disconnect signal/slot
        disconnect(sender(), SIGNAL(finished(int)), this, SLOT(onHelpDialogFinished(int)));

        // properly clean the memory usage
        delete helpDialog;
        helpDialog = nullptr;

        qDebug() << "Cleanly destroyed previous HelpDialog\n";
    }
}
