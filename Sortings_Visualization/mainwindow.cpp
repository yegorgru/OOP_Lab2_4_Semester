#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include <QDesktopWidget>
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

    m_SortingAndTiming.SetSorting(static_cast<Sortings::SortingName>(ui->SortingNameComboBox->currentIndex()));

    m_Visualizer.ClearQueue();

    ui->SortingTime->setText("Time of sorting: " +  QString::number(m_SortingAndTiming.Run(m_Numbers)) + " milliseconds");

    if (ui->ShowVisualizationCheckBox->isChecked()) {
        ui->groupBox->setEnabled(false);
        m_Visualizer.Play(ui->Slider->value());
    }
    connect(&m_Visualizer, &Visualizer::Sorted, this, [this] { this->ui->groupBox->setEnabled(true); });
}

void MainWindow::RandomizeNumbers(int size){
    m_Numbers.clear();
    for(int i=0;i<size;i++){
        m_Numbers.push_back(mersenne()%ui->verticalSlider->value());
    }
}

void MainWindow::on_InitiateButton_clicked()
{
    m_Visualizer.SetMaxValue( ui->verticalSlider->value());

    RandomizeNumbers(ui->spinBox->value());

    auto size = ui->graphicsView->size();
    m_Visualizer.FormScene(size);

    ui->SortButton->setEnabled(true);

    m_IsInitiated = true;
}
