#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "retangulo.h"
#include "circulo.h"
#include "hexagono.h"
#include "triangulo.h"
#include "deleteitem.h"
#include "QRect"
#include <QPen>
#include <QBrush>
#include <QPolygonF>
#include <QtMath>
#include <QMessageBox>
#include <QGraphicsItem>
#include <fstream>
#include <QFileDialog>
#include <thread>
#include <chrono>
#include <QTime>
#include <QStandardPaths>

int miliToSecond(int x){
    return x/1000;
}

void autoSave(MainWindow* window){
    QTime time;
    time.start();
    while(1){
    std::this_thread::sleep_for(std::chrono::seconds(1));
    if(miliToSecond(time.elapsed())>5){
        QString filename = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) += QString("/autosave.tgg");
        QFile f(filename);
        f.open(QIODevice::WriteOnly);
        QDataStream file(&f);
        file << window->ui->graphicsView->width() << window->ui->graphicsView->height();
        for(int i=0; i < window->list.size(); ++i){
            file << QString(window->list[i].Nome);
            for(int j =0; j < window->list[i].list.size();++j) file << window->list[i].list[j];
        }
        time.restart();
    }
    if(window->finish)
         break;
    }
    return;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    finish(false),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(QString("CanvasEdit"));
    Dialog askCanvas(this);
    askCanvas.setWindowTitle(QString("CanvasEdit"));
    askCanvas.exec();
    cancel = false;
    if(!askCanvas.cancel) cancel = true;
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->resize(askCanvas.x+5, askCanvas.y+5);
    scene->addRect(0,0,askCanvas.x, askCanvas.y,QPen(Qt::white),QBrush(Qt::white));
    QObject::connect(ui->actionNovo,SIGNAL(triggered()),this,SLOT(clearCanvas()));
    QObject::connect(ui->actionSalvar,SIGNAL(triggered()),ui->pushButton_7,SLOT(click()));
    QObject::connect(ui->actionAbrir,SIGNAL(triggered()),ui->pushButton_8,SLOT(click()));
    QObject::connect(ui->actionSair,SIGNAL(triggered()),this,SLOT(close()));
    QObject::connect(ui->actionSobre,SIGNAL(triggered()),this,SLOT(sobre()));
    QObject::connect(ui->actionAjuda,SIGNAL(triggered()),this,SLOT(ajuda()));
    QObject::connect(ui->actionAtualizar,SIGNAL(triggered()),this,SLOT(refresh()));
    savethread = std::thread(autoSave, this);
    }

MainWindow::~MainWindow()
{
    delete ui;
    finish = true;
    savethread.join();
}

void MainWindow::on_pushButton_4_clicked()
{
    retangulo re;
    re.exec();
    if(!re.cancel) return;
    QPen pen(Qt::red);
    QBrush brush(Qt::red);
    switch(re.getCor()){
    case 0:
        pen.setColor(Qt::red);
        brush.setColor(Qt::red);
        break;
    case 1:
        pen.setColor(Qt::blue);
        brush.setColor(Qt::blue);
        break;
    case 2:
        pen.setColor(Qt::green);
        brush.setColor(Qt::green);
        break;
    default:
        pen.setColor(Qt::red);
        brush.setColor(Qt::red);
        break;
    }
    int alt = re.getAltura(), base = re.getBase();
    // if(re.getAltura() >= (ui->graphicsView->size().height()-5)) alt = re.getAltura() -(re.getAltura() - ui->graphicsView->size().height()) - re.getY() -5;
    // if(re.getBase() >= (ui->graphicsView->size().width() - 5)) base = re.getBase() -(re.getBase() - ui->graphicsView->size().width()) - re.getX() -5 ;
    scene->addRect(re.getX(),re.getY(),base,alt,pen,brush);
    Poligono a("R");
    a.list.push_back(re.getX());
    a.list.push_back(re.getY());
    a.list.push_back(base);
    a.list.push_back(alt);
    a.list.push_back(re.getCor());
    list.push_back(a);
    update();
}

void MainWindow::on_pushButton_5_clicked()
{
    circulo re;
    re.exec();
    if(!re.cancel) return;
    QPen pen(Qt::red);
    QBrush brush(Qt::red);
    switch(re.getCor()){
    case 0:
        pen.setColor(Qt::red);
        brush.setColor(Qt::red);
        break;
    case 1:
        pen.setColor(Qt::blue);
        brush.setColor(Qt::blue);
        break;
    case 2:
        pen.setColor(Qt::green);
        brush.setColor(Qt::green);
        break;
    default:
        pen.setColor(Qt::red);
        brush.setColor(Qt::red);
        break;
    }
    // if(re.getAltura() >= (ui->graphicsView->size().height()-5)) alt = re.getAltura() -(re.getAltura() - ui->graphicsView->size().height()) - re.getY() -5;
    // if(re.getBase() >= (ui->graphicsView->size().width() - 5)) base = re.getBase() -(re.getBase() - ui->graphicsView->size().width()) - re.getX() -5 ;
    scene->addEllipse(re.getX(),re.getY(),re.getRaio(),re.getRaio(),pen,brush);

    Poligono a("C");
    a.list.push_back(re.getX());
    a.list.push_back(re.getY());
    a.list.push_back(re.getRaio());
    a.list.push_back(re.getCor());
    list.push_back(a);
    update();
}


void MainWindow::on_pushButton_clicked()
{
    Dialog askCanvas(this);
    askCanvas.exec();
    if(!askCanvas.cancel) return;
    ui->graphicsView->resize(askCanvas.x+5, askCanvas.y+5);
    if(scene->items().size() == 1){
        scene->removeItem(scene->items().at(0));
        scene->addRect(0,0,askCanvas.x, askCanvas.y,QPen(Qt::white),QBrush(Qt::white));
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    hexagono re;
    re.exec();
    if(!re.cancel) return;
    QPen pen(Qt::red);
    QBrush brush(Qt::red);
    switch(re.getCor()){
    case 0:
        pen.setColor(Qt::red);
        brush.setColor(Qt::red);
        break;

    case 1:
        pen.setColor(Qt::blue);
        brush.setColor(Qt::blue);
        break;
    case 2:
        pen.setColor(Qt::green);
        brush.setColor(Qt::green);
        break;
    default:
        pen.setColor(Qt::red);
        brush.setColor(Qt::red);
        break;
    }
    int lado = re.getLado(),x = re.getX(), y = re.getY();
    QPolygonF hex;

    hex.append(QPointF(0 +x ,(sqrt(3)*lado/2) + y));//p1
    hex.append(QPointF((lado/2) + x,(sqrt(3)*lado)+y));//p2
    hex.append(QPointF((3*lado/2)+ x,(sqrt(3)*lado)+y));//p3
    hex.append(QPointF(2*lado +x,(sqrt(3)*lado/2) + y));//p4
    hex.append(QPointF((3*lado/2)+ x,0+y));//p5
    hex.append(QPointF(lado/2 +x,0+y));  //p6
    hex.append(QPointF(0 +x ,(sqrt(3)*lado/2) + y));//p1

    scene->addPolygon(hex,pen,brush);

    Poligono a("H");
    a.list.push_back(re.getX());
    a.list.push_back(re.getY());
    a.list.push_back(lado);
    a.list.push_back(re.getCor());
    list.push_back(a);
    update();
}

void MainWindow::on_pushButton_2_clicked()
{
    triangulo re;
    re.exec();
    if(!re.cancel) return;
    QPen pen(Qt::red);
    QBrush brush(Qt::red);
    switch(re.getCor()){
    case 0:
        pen.setColor(Qt::red);
        brush.setColor(Qt::red);
        break;

    case 1:
        pen.setColor(Qt::blue);
        brush.setColor(Qt::blue);
        break;
    case 2:
        pen.setColor(Qt::green);
        brush.setColor(Qt::green);
        break;
    default:
        pen.setColor(Qt::red);
        brush.setColor(Qt::red);
        break;
    }
    int base = re.getBase(),alt = re.getAltura(),x = re.getX(), y = re.getY();
    QPolygonF tri;

    tri.append(QPointF((base/2)+x,y));
    tri.append(QPointF(base+x,alt + y));
    tri.append(QPointF(x , alt + y));
    tri.append(QPointF((base/2)+x,y));
    scene->addPolygon(tri,pen,brush);

    Poligono a("T");
    a.list.push_back(re.getX());
    a.list.push_back(re.getY());
    a.list.push_back(base);
    a.list.push_back(alt);
    a.list.push_back(re.getCor());
    list.push_back(a);
    update();
}

void MainWindow::on_pushButton_6_clicked()
{
    int b = scene->items().size();
    if(b==1){
        QMessageBox msgBox;
        msgBox.setText("Nenhum polígono adicionado.");
        msgBox.setWindowTitle("Aviso");
        msgBox.exec();
    }else{
        deleteItem re(b);
        re.exec();
        if(!re.cancel) return;
        int a = b - re.getIndex() -1;
        scene->removeItem(scene->items().at(a));
        QVector<Poligono>::iterator ite = list.begin();
        for(int i=0; i<re.getIndex()-1; ++i) ++ite;
        list.erase(ite);
    }
}

int MainWindow::getSizeScene(){
    return scene->items().size();
}

void MainWindow::on_pushButton_7_clicked()
{
    QString filename = QFileDialog::getSaveFileName( this,"Salvar Arquivo","","CanvasEdit File (*.tgg)");
    if(filename == NULL) return;
    QFile f(filename);
    f.open(QIODevice::WriteOnly);
    QDataStream file(&f);
    file << ui->graphicsView->width() << ui->graphicsView->height();
    for(int i=0; i < list.size(); ++i){
        file << QString(list[i].Nome);
        for(int j =0; j < list[i].list.size();++j) file << list[i].list[j];
    }
}

void MainWindow::on_pushButton_8_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,"Abrir Arquivo","","CanvasEdit File (*.tgg)" );
    if(filename == NULL) return;
    QFile f(filename);
    f.open( QIODevice::ReadOnly );
    QDataStream file(&f);
    int cBase, cAlt;
    file >> cBase >> cAlt;
    scene->clear();
    ui->graphicsView->resize(cBase,cAlt);
    scene->addRect(0,0,cBase-5,cAlt-5,QPen(Qt::white),QBrush(Qt::white));
    list.clear();
    QString nome;
    // store data in f
    while(!file.atEnd()){
        file >> nome;
        if(nome == "R"){
            int x,y,base,alt,cor;
            file >> x >> y >> base >> alt >> cor;
            QPen pen(Qt::red);
            QBrush brush(Qt::red);
            switch(cor){
            case 0:
                pen.setColor(Qt::red);
                brush.setColor(Qt::red);
                break;

            case 1:
                pen.setColor(Qt::blue);
                brush.setColor(Qt::blue);
                break;
            case 2:
                pen.setColor(Qt::green);
                brush.setColor(Qt::green);
                break;
            default:
                pen.setColor(Qt::red);
                brush.setColor(Qt::red);
                break;
            }
            Poligono a("R");
            scene->addRect(x,y,base,alt,pen,brush);
            a.list.push_back(x);
            a.list.push_back(y);
            a.list.push_back(base);
            a.list.push_back(alt);
            a.list.push_back(cor);
            list.push_back(a);
        }
        if(nome == "C"){
            int x,y,raio,cor;
            file >> x >> y >> raio >> cor;
            QPen pen(Qt::red);
            QBrush brush(Qt::red);
            switch(cor){
            case 0:
                pen.setColor(Qt::red);
                brush.setColor(Qt::red);
                break;

            case 1:
                pen.setColor(Qt::blue);
                brush.setColor(Qt::blue);
                break;
            case 2:
                pen.setColor(Qt::green);
                brush.setColor(Qt::green);
                break;
            default:
                pen.setColor(Qt::red);
                brush.setColor(Qt::red);
                break;
            }
            scene->addEllipse(x,y,raio,raio,pen,brush);
            Poligono a("C");
            a.list.push_back(x);
            a.list.push_back(y);
            a.list.push_back(raio);
            a.list.push_back(cor);
            list.push_back(a);
        }
        if(nome == "H"){
            int x,y,lado,cor;
            file >> x >> y >> lado >> cor;
            QPen pen(Qt::red);
            QBrush brush(Qt::red);
            switch(cor){
            case 0:
                pen.setColor(Qt::red);
                brush.setColor(Qt::red);
                break;

            case 1:
                pen.setColor(Qt::blue);
                brush.setColor(Qt::blue);
                break;
            case 2:
                pen.setColor(Qt::green);
                brush.setColor(Qt::green);
                break;
            default:
                pen.setColor(Qt::red);
                brush.setColor(Qt::red);
                break;
            }
            QPolygonF hex;

            hex.append(QPointF(0 +x ,(sqrt(3)*lado/2) + y));//p1
            hex.append(QPointF((lado/2) + x,(sqrt(3)*lado)+y));//p2
            hex.append(QPointF((3*lado/2)+ x,(sqrt(3)*lado)+y));//p3
            hex.append(QPointF(2*lado +x,(sqrt(3)*lado/2) + y));//p4
            hex.append(QPointF((3*lado/2)+ x,0+y));//p5
            hex.append(QPointF(lado/2 +x,0+y));  //p6
            hex.append(QPointF(0 +x ,(sqrt(3)*lado/2) + y));//p1

            scene->addPolygon(hex,pen,brush);
            Poligono a("H");
            a.list.push_back(x);
            a.list.push_back(y);
            a.list.push_back(lado);
            a.list.push_back(cor);
            list.push_back(a);
        }
        if(nome == "T"){
            int x,y,base,alt,cor;
            file >> x >> y >> base >> alt >> cor;
            QPen pen(Qt::red);
            QBrush brush(Qt::red);
            switch(cor){
            case 0:
                pen.setColor(Qt::red);
                brush.setColor(Qt::red);
                break;

            case 1:
                pen.setColor(Qt::blue);
                brush.setColor(Qt::blue);
                break;
            case 2:
                pen.setColor(Qt::green);
                brush.setColor(Qt::green);
                break;
            default:
                pen.setColor(Qt::red);
                brush.setColor(Qt::red);
                break;
            }
            QPolygonF tri;

            tri.append(QPointF((base/2)+x,y));
            tri.append(QPointF(base+x,alt + y));
            tri.append(QPointF(x , alt + y));
            tri.append(QPointF((base/2)+x,y));
            scene->addPolygon(tri,pen,brush);

            Poligono a("T");
            a.list.push_back(x);
            a.list.push_back(y);
            a.list.push_back(base);
            a.list.push_back(alt);
            a.list.push_back(cor);
            list.push_back(a);
        }
    }
    f.close();
}

void MainWindow::clearCanvas(){
    Dialog askCanvas(this);
    askCanvas.exec();
    if(!askCanvas.cancel) return;
    scene->clear();
    ui->graphicsView->resize(askCanvas.x+5,askCanvas.y+5);
    scene->addRect(0,0,askCanvas.x,askCanvas.y,QPen(Qt::white),QBrush(Qt::white));
}

void MainWindow::on_pushButton_9_clicked()
{
    if(scene->items().size()==1){
        QMessageBox msgBox;
        msgBox.setText("Nenhum polígono adicionado.");
        msgBox.setWindowTitle("Aviso");
        msgBox.exec();
        return;
    }
    deleteItem del(scene->items().size());
    del.setTitle("Índice do item");
    del.exec();
    if(!del.cancel) return;
    int i = del.getIndex()-1;
    if(list[i].Nome == "R"){
        retangulo re;
        re.setX(QString::number(list[i].list[0]));
        re.setY(QString::number(list[i].list[1]));
        re.setBase(QString::number(list[i].list[2]));
        re.setAltura(QString::number(list[i].list[3]));
        re.setCor(list[i].list[4]);
        re.exec();
        if(!re.cancel) return;
        list[i].list.clear();
        list[i].list.push_back(re.getX());
        list[i].list.push_back(re.getY());
        list[i].list.push_back(re.getBase());
        list[i].list.push_back(re.getAltura());
        list[i].list.push_back(re.getCor());
    }
    if(list[i].Nome == "C"){
        circulo re;
        re.setX(QString::number(list[i].list[0]));
        re.setY(QString::number(list[i].list[1]));
        re.setRaio(QString::number(list[i].list[2]));
        re.setCor(list[i].list[3]);
        re.exec();
        if(!re.cancel) return;
        list[i].list.clear();
        list[i].list.push_back(re.getX());
        list[i].list.push_back(re.getY());
        list[i].list.push_back(re.getRaio());
        list[i].list.push_back(re.getCor());
    }
    if(list[i].Nome == "H"){
        hexagono re;
        re.setX(QString::number(list[i].list[0]));
        re.setY(QString::number(list[i].list[1]));
        re.setLado(QString::number(list[i].list[2]));
        re.setCor(list[i].list[3]);
        re.exec();
        if(!re.cancel) return;
        list[i].list.clear();
        list[i].list.push_back(re.getX());
        list[i].list.push_back(re.getY());
        list[i].list.push_back(re.getLado());
        list[i].list.push_back(re.getCor());
    }
    if(list[i].Nome == "T"){
        triangulo re;
        re.setX(QString::number(list[i].list[0]));
        re.setY(QString::number(list[i].list[1]));
        re.setBase(QString::number(list[i].list[2]));
        re.setAltura(QString::number(list[i].list[3]));
        re.setCor(list[i].list[4]);
        re.exec();
        if(!re.cancel) return;
        list[i].list.clear();
        list[i].list.push_back(re.getX());
        list[i].list.push_back(re.getY());
        list[i].list.push_back(re.getBase());
        list[i].list.push_back(re.getAltura());
        list[i].list.push_back(re.getCor());
    }
    refresh();
}

void MainWindow::sobre(){
    QMessageBox msgBox;
    msgBox.setText("\tPrograma 'Canvas Edit'\n \nVersão: Tgg Beta Alfa 1.9 RC\n \nLiguagem de Programação I - CI - UFPB\nProfessor: Carlos Eduardo Batista\n"
                   "\nAluno: Thiago Gonzaga Gomes\nMatricula: 11504760"
                   "\n");
    msgBox.setWindowTitle("Sobre");
    msgBox.exec();

}

void MainWindow::ajuda(){
    QMessageBox msgBox;
    msgBox.setWindowTitle("Ajuda");
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText("<a href='http://pt.stackoverflow.com/questions/tagged/qt'>Clique aqui para toda e qualquer ajuda</a>");
    msgBox.exec();
}

void MainWindow::refresh(){
    scene->clear();
    scene->addRect(0,0,ui->graphicsView->width()-5,ui->graphicsView->height()-5,QPen(Qt::white),QBrush(Qt::white));
    for(int i=0; i<list.size(); ++i){
        if(list[i].Nome == "R"){
            QPen pen(Qt::red);
            QBrush brush(Qt::red);
            switch(list[i].list[4]){
            case 0:
                pen.setColor(Qt::red);
                brush.setColor(Qt::red);
                break;

            case 1:
                pen.setColor(Qt::blue);
                brush.setColor(Qt::blue);
                break;
            case 2:
                pen.setColor(Qt::green);
                brush.setColor(Qt::green);
                break;
            default:
                pen.setColor(Qt::red);
                brush.setColor(Qt::red);
                break;
            }
            scene->addRect(list[i].list[0],list[i].list[1],list[i].list[2],list[i].list[3],pen,brush);
        }
        if(list[i].Nome == "C"){
            QPen pen(Qt::red);
            QBrush brush(Qt::red);
            switch(list[i].list[3]){
            case 0:
                pen.setColor(Qt::red);
                brush.setColor(Qt::red);
                break;

            case 1:
                pen.setColor(Qt::blue);
                brush.setColor(Qt::blue);
                break;
            case 2:
                pen.setColor(Qt::green);
                brush.setColor(Qt::green);
                break;
            default:
                pen.setColor(Qt::red);
                brush.setColor(Qt::red);
                break;
            }
            scene->addEllipse(list[i].list[0],list[i].list[1],list[i].list[2],list[i].list[2],pen,brush);
        }
        if(list[i].Nome == "H"){
            int x=list[i].list[0], y=list[i].list[1], lado=list[i].list[2], cor=list[i].list[3];
            QPen pen(Qt::red);
            QBrush brush(Qt::red);
            switch(cor){
            case 0:
                pen.setColor(Qt::red);
                brush.setColor(Qt::red);
                break;

            case 1:
                pen.setColor(Qt::blue);
                brush.setColor(Qt::blue);
                break;
            case 2:
                pen.setColor(Qt::green);
                brush.setColor(Qt::green);
                break;
            default:
                pen.setColor(Qt::red);
                brush.setColor(Qt::red);
                break;
            }
            QPolygonF hex;

            hex.append(QPointF(0 +x ,(sqrt(3)*lado/2) + y));//p1
            hex.append(QPointF((lado/2) + x,(sqrt(3)*lado)+y));//p2
            hex.append(QPointF((3*lado/2)+ x,(sqrt(3)*lado)+y));//p3
            hex.append(QPointF(2*lado +x,(sqrt(3)*lado/2) + y));//p4
            hex.append(QPointF((3*lado/2)+ x,0+y));//p5
            hex.append(QPointF(lado/2 +x,0+y));  //p6
            hex.append(QPointF(0 +x ,(sqrt(3)*lado/2) + y));//p1

            scene->addPolygon(hex,pen,brush);
        }
        if(list[i].Nome == "T"){
            int x = list[i].list[0],y = list[i].list[1],base =list[i].list[2],alt = list[i].list[3],cor =list[i].list[4];
            QPen pen(Qt::red);
            QBrush brush(Qt::red);
            switch(cor){
            case 0:
                pen.setColor(Qt::red);
                brush.setColor(Qt::red);
                break;

            case 1:
                pen.setColor(Qt::blue);
                brush.setColor(Qt::blue);
                break;
            case 2:
                pen.setColor(Qt::green);
                brush.setColor(Qt::green);
                break;
            default:
                pen.setColor(Qt::red);
                brush.setColor(Qt::red);
                break;
            }
            QPolygonF tri;

            tri.append(QPointF((base/2)+x,y));
            tri.append(QPointF(base+x,alt + y));
            tri.append(QPointF(x , alt + y));
            tri.append(QPointF((base/2)+x,y));
            scene->addPolygon(tri,pen,brush);

        }
    }
}


void MainWindow::on_pushButton_10_clicked()
{
    scene->clear();
    list.clear();
}

void MainWindow::on_pushButton_11_clicked()
{
        Dialog askCanvas(this);
        askCanvas.exec();
        if(!askCanvas.cancel) return;
        scene->clear();
        ui->graphicsView->resize(askCanvas.x+5,askCanvas.y+5);
        scene->addRect(0,0,askCanvas.x,askCanvas.y,QPen(Qt::white),QBrush(Qt::white));

}

void MainWindow::on_pushButton_12_clicked()
{
    close();
}
