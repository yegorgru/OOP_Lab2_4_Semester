#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      m_Visualizer(m_Numbers),
      m_Sorting(new Sortings::BubbleSort<std::vector<int>,Visualizer>(&m_Visualizer)),
      mersenne(rd())
{
    ui->setupUi(this);

    ui->graphicsView->scale(1, -1);

    m_MaxValue = 1000;
    m_Visualizer.SetMaxValue(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    //MainWindow::resizeEvent(event);

    auto size = ui->graphicsView->size();
    m_Visualizer.UpdateScene(size);
}

void MainWindow::showEvent(QShowEvent *event){
    RandomizeNumbers(100);

    auto size = ui->graphicsView->size();
    m_Visualizer.FormScene(size);

    ui->graphicsView->setScene(m_Visualizer.GetScene());
}

void MainWindow::on_SortButton_clicked()
{
    m_Sorting->Sort(m_Numbers.begin(), m_Numbers.end(), [](int x, int y) { return x < y; });
}

void MainWindow::RandomizeNumbers(int size){
    m_Numbers.clear();
    for(int i=0;i<size;i++){
        m_Numbers.push_back(mersenne()%m_MaxValue);
    }
}
