#pragma once

#include <QMainWindow>
#include <QGraphicsScene>
#include <QShortcut>

#include <vector>
#include <random>

#include "Sorting.h"
#include "visualizer.h"

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
    void showEvent(QShowEvent* event);

private slots:
    void on_SortButton_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

private:
    void RandomizeNumbers(int numberOfRectangles);

    Ui::MainWindow *ui;
    QShortcut  *keyCtrl_D;

    std::vector<int>m_Numbers;

    Visualizer m_Visualizer;

    Sortings::Sorting<std::vector<int>,Visualizer>* m_Sorting;
    int m_MaxValue;

    std::random_device rd;
    std::mt19937 mersenne;
};
