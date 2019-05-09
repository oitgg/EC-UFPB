#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QString>
#include <QVector>
#include <thread>
#include <chrono>
#include <QTime>

typedef struct Poligono{
    QString Nome;
    QVector<int> list;

    Poligono(QString nome): Nome(nome){}
    Poligono(){}
} Poligono;

#include <QMainWindow>
#include <QGraphicsScene>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int getSizeScene();
    std::thread savethread;
    friend void autoSave(MainWindow* window);
    bool cancel;

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void clearCanvas();

    void on_pushButton_9_clicked();

    void sobre();

    void ajuda();

    void refresh();
    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QVector<Poligono> list;

};

#endif // MAINWINDOW_H
