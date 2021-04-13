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
    ui->graphicsView->setScene(m_Visualizer.GetScene());

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
    auto size = ui->graphicsView->size();
    m_Visualizer.UpdateScene(size);
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
        }
        m_CurrentSortingName = name;
    }

    m_Visualizer.ClearQueue();
    m_Sorting->Sort(m_Numbers.begin(), m_Numbers.end(), [](int x, int y) { return x < y; });

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
}
