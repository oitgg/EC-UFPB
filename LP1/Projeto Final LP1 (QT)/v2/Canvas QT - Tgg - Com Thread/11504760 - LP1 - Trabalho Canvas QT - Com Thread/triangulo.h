#ifndef TRIANGULO_H
#define TRIANGULO_H

#include <QDialog>

namespace Ui {
class triangulo;
}

class triangulo : public QDialog
{
    Q_OBJECT

public:
    explicit triangulo(QWidget *parent = 0);
    ~triangulo();
    int getAltura();
    void setAltura(QString);
    int getBase();
    void setBase(QString);
    int getCor();
    void setCor(int);
    int getX();
    void setX(QString);
    int getY();
    void setY(QString);
    bool cancel;

private slots:
    void on_pushButton_clicked();

private:
    Ui::triangulo *ui;
};

#endif // TRIANGULO_H
