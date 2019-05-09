
#include "dialogwindow.h"

#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLayout>

DialogWindow::DialogWindow(QWidget *parent): QDialog(parent){
    QLabel *text1 = new QLabel(this);
    text1->setText("Digite o valor de X: ");
    QLineEdit *x = new QLineEdit(this);

    QLabel *text2 = new QLabel(this);
    text2->setText("Digite o valor de Y: ");
    QLineEdit *y = new QLineEdit(this);    

    QPushButton *button1 = new QPushButton();
    button1->setText("OK");
    button1->setDefault(false);
    QObject::connect(button1, SIGNAL(clicked()), this, SLOT(close()));
    QPushButton *button2 = new QPushButton();
    button2->setText("Cancelar");
    button2->setDefault(true);

    QObject::connect(button2, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(button2, SIGNAL(clicked()), this, SLOT(setCancel()));

    QHBoxLayout *layout1 = new QHBoxLayout();
    QHBoxLayout *layout2 = new QHBoxLayout();
    QHBoxLayout *layout3 = new QHBoxLayout();
    layout3->addWidget(button1);
    layout3->addWidget(button2);
    layout2->addWidget(text2);
    layout2->addWidget(y);
    layout1->addWidget(text1);
    layout1->addWidget(x);

    QVBoxLayout *final = new QVBoxLayout();
    final->addLayout(layout1);
    final->addLayout(layout2);
    final->addLayout(layout3);

    setLayout(final);
    setWindowTitle("Canvas");
    this->exec();
    setCanvas(x->text().toInt(), y->text().toInt());
}

QSize DialogWindow::minimumSizeHint() const
{
    return QSize(100, 100);
}


QSize DialogWindow::sizeHint() const
{
    return QSize(400, 200);
}

void DialogWindow::setCancel(bool a){
    cancel = a;
}

void DialogWindow::setCanvas(int a,int b){
    this->x = a;
    this->y = b;
}


