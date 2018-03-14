#ifndef DELETEITEM_H
#define DELETEITEM_H

#include <QDialog>

namespace Ui {
class deleteItem;
}

class deleteItem : public QDialog
{
    Q_OBJECT

public:
    explicit deleteItem(int size, QWidget *parent = 0);
    ~deleteItem();
    int getIndex();
    bool cancel;
    void setTitle(QString);
private slots:
    void on_pushButton_clicked();

private:
    Ui::deleteItem *ui;
};

#endif // DELETEITEM_H
