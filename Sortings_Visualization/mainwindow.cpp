#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include <QDesktopWidget>
#include <QElapsedTimer>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      m_Visualizer(m_Numbers),
      m_SortingAndTiming(new Sortings::BubbleSort<std::vector<int>,Visualizer>(&m_Visualizer)),
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
    Sortings::SortingName name =
            static_cast<Sortings::SortingName>(ui->SortingNameComboBox->currentIndex());
    if(m_CurrentSortingName != name){
        m_SortingAndTiming.SetSorting(name, m_Visualizer);
        m_CurrentSortingName = name;
    }

    m_Visualizer.ClearQueue();

    qDebug() << Qt::endl << "Time of sorting: " <<  m_SortingAndTiming.Run(m_Numbers) << "milliseconds" << Qt::endl;

    ui->groupBox->setEnabled(false);
    m_Visualizer.Play(ui->Slider->value());
    connect(&m_Visualizer, &Visualizer::Sorted, this, [this] { this->ui->groupBox->setEnabled(true); });
}

void MainWindow::RandomizeNumbers(int size){
    m_Numbers.clear();
    for(int i=0;i<size;i++){
        m_Numbers.push_back(mersenne()%m_MaxValue);
    }
}

void MainWindow::on_InitiateButton_clicked()
{
    m_MaxValue = ui->verticalSlider->value();
    m_Visualizer.SetMaxValue( ui->verticalSlider->value());

    RandomizeNumbers(ui->spinBox->value());

    auto size = ui->graphicsView->size();
    m_Visualizer.FormScene(size);

    ui->SortButton->setEnabled(true);

    m_IsInitiated = true;
}
