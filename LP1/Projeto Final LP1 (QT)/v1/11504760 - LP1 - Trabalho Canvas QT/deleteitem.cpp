#include "deleteitem.h"
#include "ui_deleteitem.h"

deleteItem::deleteItem(int size, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deleteItem)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(close()));
    QObject::connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(close()));
    ui->spinBox->setMinimum(1);
    ui->spinBox->setMaximum(size-1);
    cancel = false;
}

deleteItem::~deleteItem()
{
    delete ui;
}

int deleteItem::getIndex(){
    return ui->spinBox->value();
}

void deleteItem::on_pushButton_clicked()
{
    cancel = true;
}

void deleteItem::setTitle(QString nome){
    ui->label->setText(nome);
}
