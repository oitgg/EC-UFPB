#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(close()));
    QObject::connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(on_pushButton_clicked()));
    QObject::connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(close()));
    ui->lineEdit->setValidator(new QIntValidator(0, 1000));
    ui->lineEdit_2->setValidator(new QIntValidator(0, 1000));

    cancel = false;
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    if(!(ui->lineEdit->isModified()) || !(ui->lineEdit_2->isModified())){
        this->x=100; this->y=100;
    } else{
    this->x = ui->lineEdit->text().toInt();
    this->y = ui->lineEdit_2->text().toInt();
    }
    cancel = true;
}


void Dialog::on_Dialog_finished(int result)
{

}
