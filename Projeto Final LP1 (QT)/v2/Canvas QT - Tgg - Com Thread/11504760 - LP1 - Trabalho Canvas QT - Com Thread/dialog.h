#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QAbstractButton>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    int x,y;
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    bool cancel;

private slots:
    void on_pushButton_clicked();
    void on_Dialog_finished(int result);

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
