#ifndef CIRCULO_H
#define CIRCULO_H

#include <QDialog>

namespace Ui {
class circulo;
}

class circulo : public QDialog
{
    Q_OBJECT

public:
    explicit circulo(QWidget *parent = 0);
    ~circulo();
    int getRaio();
    void setRaio(QString);
    int getCor();
    void setCor(int);
    int getX();
    void setX(QString);
    int getY();
    void setY(QString);
    bool cancel;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::circulo *ui;
};

#endif // CIRCULO_H
