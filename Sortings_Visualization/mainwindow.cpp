#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include <QDesktopWidget>

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

    keyCtrl_D = new QShortcut(this);
    keyCtrl_D->setKey(Qt::CTRL + Qt::Key_D);
    connect(keyCtrl_D, SIGNAL(activated()), this, SLOT(on_SortButton_clicked()));
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
    RandomizeNumbers(10);

    auto size = ui->graphicsView->size();
    m_Visualizer.FormScene(size);

    ui->graphicsView->setScene(m_Visualizer.GetScene());
}

void MainWindow::on_SortButton_clicked()
{
    QString str = ui->comboBox->currentText();
    if (str == "BubbleSort") {
         m_Sorting = new Sortings::BubbleSort<std::vector<int>,Visualizer>(&m_Visualizer);
    }
    else if (str == "InsertionSort") {
        m_Sorting = new Sortings::InsertionSort<std::vector<int>,Visualizer>(&m_Visualizer);
    }

    m_Sorting->Sort(m_Numbers.begin(), m_Numbers.end(), [](int x, int y) { return x < y; });
    m_Visualizer.Play();
}

void MainWindow::RandomizeNumbers(int size){
    m_Numbers.clear();
    for(int i=0;i<size;i++){
        m_Numbers.push_back(mersenne()%m_MaxValue);
    }
}
