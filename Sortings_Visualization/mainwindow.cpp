#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include <iostream>
//#include <QDesktopWidget>
#include "parsingwindow.h"
#include <QElapsedTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      m_Visualizer(m_Numbers),
      m_SortingAndTiming(&m_Visualizer),
      mersenne(rd())
{

    ui->setupUi(this);

    ui->graphicsView->scale(1, -1);
    ui->graphicsView->setScene(m_Visualizer.GetScene());
    ui->SortButton->setEnabled(false);

    keyCtrl_D = new QShortcut(this);
    keyCtrl_D->setKey(Qt::CTRL + Qt::Key_D);
    connect(keyCtrl_D, SIGNAL(activated()), this, SLOT(on_SortButton_clicked()));

    m_IsInitiated = false;

    ui->changes->setReadOnly(true);
    ui->accesses->setReadOnly(true);
    ui->comparisons->setReadOnly(true);

    m_Visualizer.SetChangesItem(ui->changes);
    m_Visualizer.SetAccessesItem(ui->accesses);
    m_Visualizer.SetComparisonsItem(ui->comparisons);

    ui->VisualizationControl->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    if(m_IsInitiated){
        m_Visualizer.UpdateScene(double(event->size().width())/event->oldSize().width(),
                                 double(event->size().height())/event->oldSize().height());
    }
}

void MainWindow::on_SortButton_clicked() {
    ui->comparisons->setText("0");
    ui->changes->setText("0");
    ui->accesses->setText("0");

    m_SortingAndTiming.SetSorting(static_cast<Sortings::SortingName>(ui->SortingNameComboBox->currentIndex()),m_Numbers.size() <= 500);

    m_Visualizer.ClearQueue();

    if(ui->SortingOrder->currentText() == "Direct Order"){
        ui->SortingTime->setText("Time of sorting: " +  QString::number(m_SortingAndTiming.Run(m_Numbers, [](uint32_t x, uint32_t y) { return x < y; })) + " milliseconds");
    }
    else if(ui->SortingOrder->currentText() == "Reverse Order"){
        ui->SortingTime->setText("Time of sorting: " +  QString::number(m_SortingAndTiming.Run(m_Numbers, [](uint32_t x, uint32_t y) { return x > y; })) + " milliseconds");
    }
    ui->TheorComplexity->setText("Average computational complexity: " + m_SortingAndTiming.ComplexityCheck(static_cast<Sortings::SortingName>(ui->SortingNameComboBox->currentIndex())));

    if (m_Numbers.size() <= 500) {
        ui->groupBox->setEnabled(false);
        m_Visualizer.Play(ui->delay->value());
        ui->VisualizationControl->setVisible(true);
    }
    connect(&m_Visualizer, &Visualizer::Sorted, this, [this] { this->ui->groupBox->setEnabled(true);
                                                                this->ui->VisualizationControl->setVisible(false);});
}

void MainWindow::FormNumbers(){
    m_Numbers.clear();
    for(uint32_t i=0;i<ui->numberOfItems->value();i++){
        m_Numbers.push_back(mersenne()%ui->numberOfItems->value());
    }
    if(ui->InitiateOrder->currentText() == "Almost Sorted"){
        std::sort(m_Numbers.begin(), m_Numbers.end());
        for(size_t i=0;i<m_Numbers.size()/50;i++){
            std::swap(m_Numbers[mersenne()%m_Numbers.size()], m_Numbers[mersenne()%m_Numbers.size()]);
        }
    }
    else if(ui->InitiateOrder->currentText() == "Almost Sorted in Reverse Order"){
        std::sort(m_Numbers.rbegin(), m_Numbers.rend());
        for(size_t i=0;i<m_Numbers.size()/50;i++){
            std::swap(m_Numbers[mersenne()%m_Numbers.size()], m_Numbers[mersenne()%m_Numbers.size()]);
        }
    }
}

void MainWindow::on_InitiateButton_clicked()
{
    FormNumbers();

    if(m_Numbers.size() <= 500){
        m_Visualizer.SetMaxValue(ui->numberOfItems->value());
        auto size = ui->graphicsView->size();
        m_Visualizer.FormScene(size);
    }
    else{
        m_Visualizer.Clear();
    }

    ui->SortButton->setEnabled(true);

    m_IsInitiated = true;
}

void MainWindow::on_pushButton_clicked()
{
    //hide();
    window = new ParsingWindow(this);
    window->show();

}

void MainWindow::on_delay_sliderMoved(int position)
{
    if(m_Visualizer.GetTimer()){
        m_Visualizer.GetTimer()->setInterval(position);
    }
}

void MainWindow::on_StopButton_clicked()
{
    m_Visualizer.PauseOrContinue();
}

void MainWindow::on_ClearButton_clicked()
{
    m_Visualizer.Clear();
    m_Numbers.clear();
    ui->VisualizationControl->setVisible(false);
    this->ui->groupBox->setEnabled(true);
    ui->SortButton->setEnabled(false);
}
