#include "retangulo.h"
#include "ui_retangulo.h"

retangulo::retangulo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::retangulo)
{
    ui->setupUi(this);
    ui->comboBox->addItem("Vermelho");
    ui->comboBox->addItem("Azul");
    ui->comboBox->addItem("Verde");
    QObject::connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(close()));
    QObject::connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(close()));
    ui->altura->setValidator(new QIntValidator(0, 999999));
    ui->base->setValidator(new QIntValidator(0, 999999));
    ui->x->setValidator(new QIntValidator(0, 999999));
    ui->y->setValidator(new QIntValidator(0, 999999));
    cancel = false;
}

retangulo::~retangulo()
{
    delete ui;
}

int retangulo::getAltura(){
    return ui->altura->text().toInt();
}

int retangulo::getBase(){
    return ui->base->text().toInt();
}

int retangulo::getCor(){
    return ui->comboBox->currentIndex();
}

int retangulo::getX(){
    return ui->x->text().toInt();
}

int retangulo::getY(){
    return ui->y->text().toInt();
}

void retangulo::on_pushButton_2_clicked()
{
    ui->altura->setText("");
    ui->base->setText("");
    ui->x->setText("");
    ui->y->setText("");

}

void retangulo::on_pushButton_clicked()
{
    cancel = true;
}

void retangulo::setAltura(QString alt){
    ui->altura->setText(alt);
}

void retangulo::setBase(QString base){
    ui->base->setText(base);
}

void retangulo::setCor(int index){
    ui->comboBox->setCurrentIndex(index);
}

void retangulo::setX(QString x){
    ui->x->setText(x);
}

void retangulo::setY(QString y){
    ui->y->setText(y);
}





