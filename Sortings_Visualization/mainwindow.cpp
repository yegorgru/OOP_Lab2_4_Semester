#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include <QDesktopWidget>
#include <QElapsedTimer>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      m_Visualizer(m_Numbers),
      m_Sorting(new Sortings::BubbleSort<std::vector<int>,Visualizer>(&m_Visualizer)),
      mersenne(rd())
{

    ui->setupUi(this);

    ui->graphicsView->scale(1, -1);
    ui->graphicsView->setScene(m_Visualizer.GetScene());
    ui->SortButton->setEnabled(false);

    keyCtrl_D = new QShortcut(this);
    keyCtrl_D->setKey(Qt::CTRL + Qt::Key_D);
    connect(keyCtrl_D, SIGNAL(activated()), this, SLOT(on_SortButton_clicked()));

    m_SortingAndTiming.SetSorting(m_Sorting);

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
        if(m_Sorting){
            delete m_Sorting;
        }
        switch(name){
        case Sortings::SortingName::BUBBLESORT:{
            m_Sorting = new Sortings::BubbleSort<std::vector<int>,Visualizer>(&m_Visualizer);
            break;
        }
        case Sortings::SortingName::INSERTIONSORT:{
            m_Sorting = new Sortings::InsertionSort<std::vector<int>,Visualizer>(&m_Visualizer);
            break;
        }
        case Sortings::SortingName::SELECTIONSORT:{
            m_Sorting = new Sortings::SelectionSort<std::vector<int>,Visualizer>(&m_Visualizer);
            break;
        }
        case Sortings::SortingName::CYCLESORT:{
            m_Sorting = new Sortings::CycleSort<std::vector<int>,Visualizer>(&m_Visualizer);
            break;
        }
        case Sortings::SortingName::SHAKERSORT:{
            m_Sorting = new Sortings::ShakerSort<std::vector<int>,Visualizer>(&m_Visualizer);
            break;
        }
        case Sortings::SortingName::COMBSORT:{
            m_Sorting = new Sortings::CombSort<std::vector<int>,Visualizer>(&m_Visualizer);
            break;
        }
        case Sortings::SortingName::GNOMESORT:{
            m_Sorting = new Sortings::GnomeSort<std::vector<int>,Visualizer>(&m_Visualizer);
            break;
        }
        case Sortings::SortingName::ODDEVENSORT:{
            m_Sorting = new Sortings::OddEvenSort<std::vector<int>,Visualizer>(&m_Visualizer);
            break;
        }
        case Sortings::SortingName::QUICKSORT:{
            m_Sorting = new Sortings::QuickSort<std::vector<int>,Visualizer>(&m_Visualizer);
            break;
        }
        case Sortings::SortingName::MERGESORT:{
            m_Sorting = new Sortings::MergeSort<std::vector<int>,Visualizer>(&m_Visualizer);
            break;
        }
        case Sortings::SortingName::MERGESORTINPLACE:{
            m_Sorting = new Sortings::MergeSortInPlace<std::vector<int>,Visualizer>(&m_Visualizer);
            break;
        }
        case Sortings::SortingName::HEAPSORT:{
            m_Sorting = new Sortings::HeapSort<std::vector<int>,Visualizer>(&m_Visualizer);
            break;
        }
        case Sortings::SortingName::TIMSORT:{
            m_Sorting = new Sortings::TimSort<std::vector<int>,Visualizer>(&m_Visualizer);
            break;
        }
        case Sortings::SortingName::INTROSORT:{
            m_Sorting = new Sortings::IntroSort<std::vector<int>,Visualizer>(&m_Visualizer);
            break;
        }
        case Sortings::SortingName::SHELLSORT:{
            m_Sorting = new Sortings::ShellSort<std::vector<int>,Visualizer>(&m_Visualizer);
            break;
        }
        case Sortings::SortingName::PIGEONHOLESORT:{
            m_Sorting = new Sortings::PigeonholeSort<std::vector<int>,Visualizer>(&m_Visualizer);
            break;
        }
        case Sortings::SortingName::BUCKETSORT:{
            m_Sorting = new Sortings::BucketSort<std::vector<int>,Visualizer>(&m_Visualizer);
            break;
        }
        case Sortings::SortingName::COUNTINGSORT:{
            Sortings::CountingSort<std::vector<int>,Visualizer>::RANGE = ui->verticalSlider->value();
            m_Sorting = new Sortings::CountingSort<std::vector<int>,Visualizer>(&m_Visualizer);
            break;
        }
        case Sortings::SortingName::RADIXSORT:{
            m_Sorting = new Sortings::RadixSort<std::vector<int>,Visualizer>(&m_Visualizer);
            break;
        }
        }
        m_CurrentSortingName = name;
    }

    m_Visualizer.ClearQueue();

    m_SortingAndTiming.SetSorting(m_Sorting);
    qDebug() << Qt::endl << "Time of sorting: " <<  m_SortingAndTiming.Run(m_Numbers) << "milliseconds" << Qt::endl;

    ui->groupBox->setEnabled(false);
    m_Visualizer.Play(ui->Slider->value());
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
