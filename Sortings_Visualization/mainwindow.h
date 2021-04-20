#pragma once

#include <QMainWindow>
#include <QGraphicsScene>
#include <QShortcut>
#include <QResizeEvent>

#include <vector>
#include <random>

#include "Sorting.h"
#include "visualizer.h"
#include "Decorator.h"
#include "parsingwindow.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent* event);

private slots:
    void on_SortButton_clicked();

    void on_InitiateButton_clicked();

    void on_pushButton_clicked();

    void on_delay_sliderMoved(int position);

private:
    void FormNumbers();

    Ui::MainWindow *ui;
    ParsingWindow * window;
    QShortcut  *keyCtrl_D;

    std::vector<int>m_Numbers;

    Visualizer m_Visualizer;

    SortingAndTiming m_SortingAndTiming;

    bool m_IsInitiated;

    std::random_device rd;
    std::mt19937 mersenne;
};
