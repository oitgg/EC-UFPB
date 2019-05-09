#include "rectangle.h"
#include "ui_rectangle.h"

Rectangle::Rectangle(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Rectangle)
{
    ui->setupUi(this);
}

Rectangle::~Rectangle()
{
    delete ui;
}
