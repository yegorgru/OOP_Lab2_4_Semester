#include "Decorator.h"

void SortingAndTiming::SetSorting(Sortings::Sorting<std::vector<int>,Visualizer>* sorting){
    m_Sorting = sorting;
}

qint64 SortingAndTiming::Run(std::vector<int>& m_Numbers){
    time.start();
    m_Sorting->Sort(m_Numbers.begin(), m_Numbers.end(), [](int x, int y) { return x < y; });
    return time.nsecsElapsed();
}
