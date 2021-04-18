#pragma once

#include <Sorting.h>
#include <visualizer.h>
#include <QElapsedTimer>

class SortingAndTiming  {
public:
    SortingAndTiming() = default;

    void SetSorting(Sortings::Sorting<std::vector<int>,Visualizer>* sorting);

    qint64 Run(std::vector<int>& m_Numbers);

private:
    QElapsedTimer time;
    Sortings::Sorting<std::vector<int>,Visualizer>* m_Sorting;
};
