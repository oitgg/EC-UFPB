#ifndef HEXAGONO_H
#define HEXAGONO_H

#include <QDialog>

namespace Ui {
class hexagono;
}

class hexagono : public QDialog
{
    Q_OBJECT

public:
    explicit hexagono(QWidget *parent = 0);
    ~hexagono();
    int getLado();
    void setLado(QString);
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
    Ui::hexagono *ui;
};

#endif // HEXAGONO_H
