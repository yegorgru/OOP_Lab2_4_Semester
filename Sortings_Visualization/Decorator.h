#pragma once

#include "SortingProxy.h"

#include <QElapsedTimer>

#include <string>


namespace Sortings{
    template<
        typename Container,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class SortingAndTiming{
    public:
        SortingAndTiming(SortingProxy<std::vector<uint32_t>>*sorting):
            m_Sorting(sorting) {}

        float Sort(SortingName name, typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
             [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }){
            time.start();
            m_Sorting->Sort(name, begin, end, cmp);
            return (float)time.nsecsElapsed()/1000000;
        }

        std::string ComplexityCheck(Sortings::SortingName name){
            if ((name == Sortings::SortingName::BUBBLESORT ) || (name == Sortings::SortingName::INSERTIONSORT) ||
                    (name == Sortings::SortingName::SELECTIONSORT) || (name == Sortings::SortingName::SHAKERSORT) || (name == Sortings::SortingName::GNOMESORT)
                    || (name == Sortings::SortingName::ODDEVENSORT) || (name == Sortings::SortingName::PANCAKESORT) || (name == Sortings::SortingName::STOOGESORT))
            {
                return "O(n²)";
            }
            else if ((name == Sortings::SortingName::COMBSORT) || (name == Sortings::SortingName::QUICKSORTPIVOTFIRST) || (name == Sortings::SortingName::MERGESORT)
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

    private:
        QElapsedTimer time;
        SortingProxy<std::vector<uint32_t>>*m_Sorting;
    };
}
