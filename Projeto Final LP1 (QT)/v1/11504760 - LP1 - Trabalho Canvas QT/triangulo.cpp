#include "triangulo.h"
#include "ui_triangulo.h"

triangulo::triangulo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::triangulo)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(close()));
    QObject::connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(close()));
    ui->altura->setValidator(new QIntValidator(0, 999999));
    ui->base->setValidator(new QIntValidator(0, 999999));
    ui->x->setValidator(new QIntValidator(0, 999999));
    ui->y->setValidator(new QIntValidator(0, 999999));
    cancel = false;

}

triangulo::~triangulo()
{
    delete ui;
}

int triangulo::getAltura(){
    return ui->altura->text().toInt();
}

int triangulo::getBase(){
    return ui->base->text().toInt();
}

int triangulo::getCor(){
    return ui->comboBox->currentIndex();
}

int triangulo::getX(){
    return ui->x->text().toInt();
}

int triangulo::getY(){
    return ui->y->text().toInt();
}



void triangulo::on_pushButton_clicked()
{
    cancel = true;
}

void triangulo::setAltura(QString alt){
    ui->altura->setText(alt);
}

void triangulo::setBase(QString base){
    ui->base->setText(base);
}

void triangulo::setCor(int index){
    ui->comboBox->setCurrentIndex(index);
}

void triangulo::setX(QString x){
    ui->x->setText(x);
}

void triangulo::setY(QString y){
    ui->y->setText(y);
}
