#pragma once

#include <Sorting.h>
#include <visualizer.h>

#include <QElapsedTimer>

class SortingAndTiming  {
public:
    SortingAndTiming(Visualizer* visualizer);

    void SetSorting(Sortings::SortingName name, bool isVisualization);

    QString ComplexityCheck(Sortings::SortingName name);
    float Run(std::vector<int>& m_Numbers, std::function<bool (int,int)> cmp);

private:
    QElapsedTimer time;
    Visualizer* m_Visualizer;
    Sortings::DefaultVisualizer<std::vector<int>>m_DefaultVisualizer;
    Sortings::Sorting<std::vector<int>>*m_Sorting;
    Sortings::SortingName m_CurrentSortingName;
};
