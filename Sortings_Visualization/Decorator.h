#pragma once

#include <Sorting.h>
#include <visualizer.h>

#include <QElapsedTimer>

class SortingAndTiming  {
public:
    SortingAndTiming(Visualizer* visualizer);

    void SetSorting(Sortings::SortingName name, bool isVisualization);

    QString ComplexityCheck(Sortings::SortingName name);
    float Run(std::vector<uint32_t>& m_Numbers, std::function<bool (uint32_t,uint32_t)> cmp);

private:
    QElapsedTimer time;
    Visualizer* m_Visualizer;
    Sortings::DefaultVisualizer<std::vector<uint32_t>>m_DefaultVisualizer;
    Sortings::Sorting<std::vector<uint32_t>>*m_Sorting;
    Sortings::SortingName m_CurrentSortingName;
};
