#include "Decorator.h"
#include "Factory.h"

SortingAndTiming::SortingAndTiming(Visualizer* visualizer):
    m_Visualizer(visualizer),
    m_Sorting(new Sortings::BubbleSort<std::vector<uint32_t>,Sortings::DefaultVisualizer<std::vector<uint32_t>>>(m_Visualizer)),
    m_CurrentSortingName(Sortings::SortingName::BUBBLESORT) {}

void SortingAndTiming::SetSorting(Sortings::SortingName name, bool isVisualization){
    if(m_CurrentSortingName != name){
        if(m_Sorting){
            delete m_Sorting;
        }
        m_Sorting = Factory<std::vector<uint32_t>>::CreateSorting(name);
        m_CurrentSortingName = name;
    }
    if(isVisualization){
        m_Sorting->SetVisualizer(m_Visualizer);
    }
    else{
        m_Sorting->SetVisualizer(&m_DefaultVisualizer);
    }
}

float SortingAndTiming::Run(std::vector<uint32_t>& m_Numbers, std::function<bool (uint32_t,uint32_t)> cmp){
    time.start();
    m_Sorting->Sort(m_Numbers.begin(), m_Numbers.end(), cmp);
    return (float)time.nsecsElapsed()/1000000;
}

QString SortingAndTiming::ComplexityCheck(Sortings::SortingName name)
{
    if ((name == Sortings::SortingName::BUBBLESORT ) || (name == Sortings::SortingName::INSERTIONSORT) ||
            (name == Sortings::SortingName::SELECTIONSORT) || (name == Sortings::SortingName::SHAKERSORT) || (name == Sortings::SortingName::GNOMESORT)
            || (name == Sortings::SortingName::ODDEVENSORT) || (name == Sortings::SortingName::PANCAKESORT) || (name == Sortings::SortingName::STOOGESORT))
    {
        return "O(n²)";
    }
    else if ((name == Sortings::SortingName::COMBSORT) || (name == Sortings::SortingName::QUICKSORT) || (name == Sortings::SortingName::MERGESORT)
               || (name == Sortings::SortingName::MERGESORTINPLACE) || (name == Sortings::SortingName::HEAPSORT) || (name == Sortings::SortingName::TIMSORT)
               || (name == Sortings::SortingName::INTROSORT) || (name == Sortings::SortingName::SHELLSORT) || (name == Sortings::SortingName::BUCKETSORT))
    {
        return "O(n log(n))";
    }
    else if((name == Sortings::SortingName::PIGEONHOLESORT) || (name == Sortings::SortingName::COUNTINGSORT) || (name == Sortings::SortingName::RADIXSORT)
              )
    {
        return "O(n + Range)";
    }
    else if(name == Sortings::SortingName::FLASHSORT)
    {
        return "O(n)";
    }
    else if(name == Sortings::SortingName::BOGOSORT)
    {
        return "O((n+1)!)";
    }
    else if(name == Sortings::SortingName::BOGOSORT)
    {
        return "O(>n²)";
    }
    return "Unrecognised";
}
