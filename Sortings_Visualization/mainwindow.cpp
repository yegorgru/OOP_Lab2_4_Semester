#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      mersenne(rd()),
      m_Scene(new QGraphicsScene),
      m_Visualizer(*m_Scene)
{
    ui->setupUi(this);

    ui->graphicsView->scale(1, -1);

    m_MaxValue = 1000;
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

    double width = double(m_Scene->width())/m_Visualizer.GetRects().size();
    for(size_t i=0;i<m_Visualizer.GetRects().size();i++){
        double height = double(m_Numbers[i])/m_MaxValue*m_Scene->height()*0.9;
        m_Visualizer.GetRects()[i]->setRect(i*width,m_Scene->height()*0.05, width, height);
    }
    m_Scene->update();
}

void MainWindow::showEvent(QShowEvent *event){
    auto size = ui->graphicsView->size();
    m_Scene->setSceneRect( 0,0,size.width()*0.95, size.height()*0.95);

    FormRandomScene(100);

    ui->graphicsView->setScene(m_Scene);
}

void MainWindow::on_SortButton_clicked()
{
    m_Sorting->Sort(m_Numbers.begin(), m_Numbers.end(), [](int x, int y) { return x < y; },
    [this](Sortings::Operation operation, size_t pos){this->VisualizeChanges(operation, pos);});
}

void MainWindow::VisualizeChanges(Sortings::Operation operation, size_t pos){
    if(operation == Sortings::Operation::ACCESS){

    }
    else if(operation == Sortings::Operation::COMPARISON){

    }
    else if(operation == Sortings::Operation::CHANGE){

    }
}

void MainWindow::FormRandomScene(int numberOfRectangles){
    for(auto i:m_Visualizer.GetRects()){
        delete i;
    }
    double width = double(m_Scene->width())/numberOfRectangles;
    m_Visualizer.GetRects().clear();
    m_Numbers.clear();
    for(int i=0;i<numberOfRectangles;i++){
        m_Numbers.push_back(mersenne()%m_MaxValue);
        double height = double(m_Numbers.back())/m_MaxValue*m_Scene->height()*0.9;
        QGraphicsRectItem* cur =
                new QGraphicsRectItem(m_Visualizer.GetRects().size()*width,m_Scene->height()*0.95,
                                      width, height);
        cur->setBrush(QBrush(Qt::red));
        m_Visualizer.GetRects().push_back(cur);
        m_Scene->addItem(m_Visualizer.GetRects().back());
    }
    m_Scene->update();
}
