#include "circulo.h"
#include "ui_circulo.h"

circulo::circulo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::circulo)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(close()));
    ui->raio->setValidator(new QIntValidator(0, 999999));
    ui->x->setValidator(new QIntValidator(0, 999999));
    ui->y->setValidator(new QIntValidator(0, 999999));
    cancel = false;
}

circulo::~circulo()
{
    delete ui;
}

int circulo::getRaio(){
    return ui->raio->text().toInt();
}

int circulo::getCor(){
    return ui->comboBox->currentIndex();
}


int circulo::getX(){
    return ui->x->text().toInt();
}


int circulo::getY(){
    return ui->y->text().toInt();
}



void circulo::on_pushButton_2_clicked()
{
    ui->raio->setText("");
    ui->x->setText("");
    ui->y->setText("");

}

void circulo::on_pushButton_clicked()
{
    cancel = true;
}

void circulo::setRaio(QString raio){
    ui->raio->setText(raio);
}

void circulo::setCor(int index){
    ui->comboBox->setCurrentIndex(index);
}

void circulo::setX(QString x){
    ui->x->setText(x);
}

void circulo::setY(QString y){
    ui->y->setText(y);
}



