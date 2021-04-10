#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopWidget>
#include <QGraphicsRectItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene=new QGraphicsScene;

    auto size = ui->graphicsView->size();
    scene->setSceneRect ( 0,0,size.width()*0.95, size.height()*0.95);

    /*QGraphicsRectItem* item1 = new QGraphicsRectItem(0,0,100,100);
    QGraphicsRectItem* item2 = new QGraphicsRectItem(0,100,100,100);
    QGraphicsRectItem* item3 = new QGraphicsRectItem(100,0,100,100);
    QGraphicsRectItem* item4 = new QGraphicsRectItem(100,100,100,100);

    item1->setBrush(QBrush(Qt::red));
    item2->setBrush(QBrush(Qt::green));
    item3->setBrush(QBrush(Qt::blue));
    item4->setBrush(QBrush(Qt::yellow));

    scene->addItem(item1);
    scene->addItem(item2);
    scene->addItem(item3);
    scene->addItem(item4);*/

    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    //MainWindow::resizeEvent(event);

    auto size = ui->graphicsView->size();
    scene->setSceneRect ( 0,0,size.width()*0.95, size.height()*0.95);
}

