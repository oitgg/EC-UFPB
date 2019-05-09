#include "hexagono.h"
#include "ui_hexagono.h"

hexagono::hexagono(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::hexagono)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(close()));
    QObject::connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(close()));
    ui->lado->setValidator(new QIntValidator(0, 999999));
    ui->x->setValidator(new QIntValidator(0, 999999));
    ui->y->setValidator(new QIntValidator(0, 999999));
    cancel = false;
}

hexagono::~hexagono()
{
    delete ui;
}

int hexagono::getLado(){
    return ui->lado->text().toInt();
}

int hexagono::getCor(){
    return ui->comboBox->currentIndex();
}

int hexagono::getX(){
    return ui->x->text().toInt();
}

int hexagono::getY(){
    return ui->y->text().toInt();
}


void hexagono::on_pushButton_clicked()
{
    cancel = true;
}

void hexagono::setLado(QString lado){
    ui->lado->setText(lado);
}

void hexagono::setCor(int index){
    ui->comboBox->setCurrentIndex(index);
}

void hexagono::setX(QString x){
    ui->x->setText(x);
}

void hexagono::setY(QString y){
    ui->y->setText(y);
}
