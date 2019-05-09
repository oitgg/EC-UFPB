
#include "mainwindow.h"
#include "dialogwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    if(w.cancel) return 0;
    w.show();

    return a.exec();
}
