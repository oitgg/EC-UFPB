#ifndef RETANGULO_H
#define RETANGULO_H

#include <QDialog>

namespace Ui {
class retangulo;
}

class retangulo : public QDialog
{
    Q_OBJECT

public:
    explicit retangulo(QWidget *parent = 0);
    ~retangulo();
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
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::retangulo *ui;
};

#endif // RETANGULO_H
