#pragma once

#include <Sorting.h>
#include <visualizer.h>

#include <QElapsedTimer>

class SortingAndTiming  {
public:
    SortingAndTiming(Visualizer* visualizer);

    void SetSorting(Sortings::SortingName name);

    float Run(std::vector<int>& m_Numbers);

private:
    QElapsedTimer time;
    Visualizer* m_Visualizer;
    Sortings::Sorting<std::vector<int>,Visualizer>* m_Sorting;
    Sortings::SortingName m_CurrentSortingName;
};
