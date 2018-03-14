#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QWidget>

namespace Ui {
class Rectangle;
}

class Rectangle : public QWidget
{
    Q_OBJECT

public:
    explicit Rectangle(QWidget *parent = 0);
    ~Rectangle();

private:
    Ui::Rectangle *ui;
};

#endif // RECTANGLE_H
