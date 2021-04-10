#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_Scene=new QGraphicsScene;

    auto size = ui->graphicsView->size();
    m_Scene->setSceneRect ( 0,0,size.width()*0.95, size.height()*0.95);

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

    ui->graphicsView->setScene(m_Scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    //MainWindow::resizeEvent(event);

    auto size = ui->graphicsView->size();
    m_Scene->setSceneRect ( 0,0,size.width()*0.95, size.height()*0.95);
}

void MainWindow::on_SortButton_clicked()
{
    m_Sorting->Sort(m_Numbers.begin(), m_Numbers.end(), [](int x, int y) { return x < y; },
    [this](Sortings::Operation operation, size_t pos){this->VisualizeChanges(operation, pos);});
}
