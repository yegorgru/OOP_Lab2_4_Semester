#pragma once

#include <type_traits>
#include <iterator>
#include <algorithm>
#include <functional>
#include <optional>
#include <vector>
#include <array>

template<typename Container>
using IteratorCategoryOf =
    typename std::iterator_traits<typename Container::iterator>::iterator_category;

template<typename Container>
using HaveRandomAccessIterator =
    std::is_base_of<std::random_access_iterator_tag, IteratorCategoryOf<Container>>;

namespace Sortings{

    enum class Operation{
        COMPARISON = 0,
        ACCESS,
        CHANGE,
        END
    };

    enum class SortingName{
        BUBBLESORT,
        INSERTIONSORT,
        SELECTIONSORT,
        CYCLESORT,
        SHAKERSORT,
        COMBSORT,
        GNOMESORT,
        ODDEVENSORT,
        QUICKSORT,
        MERGESORT,
        MERGESORTINPLACE,
        HEAPSORT,
        TIMSORT,
        INTROSORT,
        SHELLSORT,
        PIGEONHOLESORT,
        BUCKETSORT
    };

    template <typename T>
    class DefaultVisualizer{
    public:
        bool Visualize(Operation operation, typename T::iterator first, std::optional<typename T::iterator> second = std::nullopt){
            return true;
        }
    };

    template<
        typename Container,
        typename Visualizer = DefaultVisualizer<Container>,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class Sorting{
    public:
        Sorting(Visualizer* visualizer = nullptr):
            visualizer(visualizer){}

        virtual void Sort(typename Container::iterator begin, typename Container::iterator end,
                     std::function<bool (
                     typename std::iterator_traits<typename Container::iterator>::value_type,
                     typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) = 0;
    protected:
        Visualizer* visualizer;
    };

    template<
        typename Container,
        typename Visualizer = DefaultVisualizer<Container>,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class BubbleSort : public Sorting<Container, Visualizer>{
    public:
        BubbleSort(Visualizer* visualizer = nullptr):
            Sorting<Container, Visualizer>(visualizer){}

        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) override {
            using Iterator = typename Container::iterator;
            for (Iterator i = begin; i < end-1; i++){
                for (Iterator j = begin; j < end-i+begin-1; j++){
                    if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, j, j+1);
                    if (cmp(*(j + 1), *j)){
                        std::swap(*j, *(j + 1));
                        if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, j, j+1);
                    }
                }
            }
        }
    };

    template<
        typename Container,
        typename Visualizer = DefaultVisualizer<Container>,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class InsertionSort : public Sorting<Container, Visualizer>{
    public:
        InsertionSort(Visualizer* visualizer = nullptr):
            Sorting<Container, Visualizer>(visualizer){}

        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) override {
            using Iterator = typename Container::iterator;
            using ValueType = typename std::iterator_traits<typename Container::iterator>::value_type;
            for ( Iterator i = begin+1; i < end; i++) {
                Iterator j= i;
                this->visualizer->Visualize(Operation::ACCESS, i);
                ValueType key = *i;
                while (j > begin && (this->visualizer != nullptr ?
                       this->visualizer->Visualize(Operation::COMPARISON, j-1) :true) &&
                       cmp(key,*(j-1))) {
                    *j = *(j-1);
                    if(this->visualizer) {
                        this->visualizer->Visualize(Operation::CHANGE, j);
                        this->visualizer->Visualize(Operation::ACCESS, j-1);
                    }
                    j--;
                }
                *j = key;
                if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, j);
            }
        }
    };

    template<
        typename Container,
        typename Visualizer = DefaultVisualizer<Container>,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class SelectionSort : public Sorting<Container, Visualizer>{
    public:
        SelectionSort(Visualizer* visualizer = nullptr):
            Sorting<Container, Visualizer>(visualizer){}

        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) override {
            using Iterator = typename Container::iterator;
            for (Iterator i = begin; i < end-1; i++) {
                Iterator min = i;
                for (Iterator j = i + 1; j < end; j++)
                {
                    if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, j, min);
                    if (cmp(*j, *min))
                    {
                        min = j;
                        if(this->visualizer){
                            this->visualizer->Visualize(Operation::ACCESS, j);
                            this->visualizer->Visualize(Operation::CHANGE, min);
                        }
                    }
                }
                if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, i, min);
                if (min != i)
                {
                    std::swap(*i, *min);
                    if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, i, min);
                }
            }
        }
    };

    template<
        typename Container,
        typename Visualizer = DefaultVisualizer<Container>,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class CycleSort : public Sorting<Container, Visualizer>{
    public:
        CycleSort(Visualizer* visualizer = nullptr):
            Sorting<Container, Visualizer>(visualizer){}

        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) override {
            using Iterator = typename Container::iterator;
            using ValueType = typename std::iterator_traits<typename Container::iterator>::value_type;
            for( Iterator i = begin; i < end - 1; i++ )
            {
                if(this->visualizer) this->visualizer->Visualize(Operation::ACCESS, i);
                ValueType cur = *i;
                size_t pos = i-begin;
                for( Iterator j = i + 1; j < end; j++ ){
                    if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, j);
                    if( cmp(*j,cur)){
                        pos++;
                    }
                }
                if( i-begin == pos ){
                    continue;
                }
                while((this->visualizer ? this->visualizer->Visualize(Operation::COMPARISON, begin+pos) : true) && *(begin+pos) == cur){
                    pos++;
                }
                std::swap( cur, *(begin+pos));
                if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, begin+pos);
                while( i-begin != pos ){
                    pos = i-begin;
                    for( Iterator j = i + 1; j < end; j++ ){
                        if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, j);
                        if( cmp(*j, cur)) {
                            pos++;
                        }
                    }
                    while((this->visualizer ? this->visualizer->Visualize(Operation::COMPARISON, begin+pos) : true) && *(begin+pos) == cur){
                        pos++;
                    }
                    std::swap( cur, *(begin+pos) );
                    if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, begin+pos);
                }
            }
        }
    };

    template<
        typename Container,
        typename Visualizer = DefaultVisualizer<Container>,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class ShakerSort : public Sorting<Container, Visualizer>{
    public:
        ShakerSort(Visualizer* visualizer = nullptr):
            Sorting<Container, Visualizer>(visualizer){}

        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) override {
            using Iterator = typename Container::iterator;
            size_t border=end-begin;
            Iterator left = begin;
            Iterator right = end - 1;
            do {
                for (Iterator i = left; i < right; i++) {
                    if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, i+1, i);
                    if (cmp(*(i+1), *i)) {
                        std::swap(*i, *(i+1));
                        if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, i+1, i);
                        border=i-begin;
                    }
                }
                right=begin+border;
                for (Iterator i = right; i > left; i--) {
                    if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, i-1, i);
                    if (cmp(*i, *(i-1))) {
                        std::swap(*i, *(i-1));
                        if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, i-1, i);
                        border=i-begin;
                    }
                }
                left=begin+border;
            } while (left < right);
        }
    };

    template<
        typename Container,
        typename Visualizer = DefaultVisualizer<Container>,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class CombSort : public Sorting<Container, Visualizer>{
    public:
        CombSort(Visualizer* visualizer = nullptr):
            Sorting<Container, Visualizer>(visualizer){}

        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) override {
            using Iterator = typename Container::iterator;
            const double factor = 1.2473309;
            size_t step = end-begin;
            bool swapped = true;
            while (step > 1 || swapped) {
                if (step > 1){
                    step /= factor;
                }
                swapped = false;
                for (Iterator i = begin; i + step < end; i++) {
                    if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, i+step, i);
                    if (cmp(*(i+step),*i)) {
                        std::swap(*i, *(i + step));
                        if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, i, i+step);
                        swapped = true;
                    }
                }
            }
        }
    };

    template<
        typename Container,
        typename Visualizer = DefaultVisualizer<Container>,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class GnomeSort : public Sorting<Container, Visualizer>{
    public:
        GnomeSort(Visualizer* visualizer = nullptr):
            Sorting<Container, Visualizer>(visualizer){}

        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) override {
            using Iterator = typename Container::iterator;
            Iterator i = begin+1;
            Iterator j = begin+2;
            while(i < end){
                if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, i-1, i);
                if(cmp(*(i-1), *i)){
                    i = j;
                    j = j < end ? j+1 : j;
                }
                else{
                    std::swap(*(i-1), *i);
                    if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, i-1, i);
                    i--;
                    if(i==begin){
                        i = j;
                        j = j < end ? j+1 : j;
                    }
                }
            }
        }
    };

    template<
        typename Container,
        typename Visualizer = DefaultVisualizer<Container>,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class OddEvenSort : public Sorting<Container, Visualizer>{
    public:
        OddEvenSort(Visualizer* visualizer = nullptr):
            Sorting<Container, Visualizer>(visualizer){}

        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) override {
            for (size_t i = 0; i < end-begin; i++) {
                for (size_t j = (i % 2) ? 0 : 1; j + 1 < end-begin; j += 2) {
                    if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, begin+j+1, begin+j);
                    if (cmp(*(begin+j+1), *(begin+j))) {
                        std::swap(*(begin+j+1), *(begin+j));
                        if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, begin+j+1, begin+j);
                    }
                }
            }
        }
    };

    template<
        typename Container,
        typename Visualizer = DefaultVisualizer<Container>,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class QuickSort : public Sorting<Container, Visualizer>{
    public:
        QuickSort(Visualizer* visualizer = nullptr):
            Sorting<Container, Visualizer>(visualizer){}

        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) override {
            using Iterator = typename Container::iterator;
            if (begin != end){
                Iterator left  = begin;
                Iterator right = end;
                if(this->visualizer) this->visualizer->Visualize(Operation::ACCESS, left);
                Iterator pivot = left++;
                while( left != right ) {
                  if( (this->visualizer ? this->visualizer->Visualize(Operation::COMPARISON, left) : true) && cmp( *left, *pivot ) ) {
                     ++left;
                  } else {
                     while( left != --right &&
                            (this->visualizer ?
                             this->visualizer->Visualize(Operation::COMPARISON, right)
                             : true) && cmp( *pivot, *right ) );
                     std::swap( *left, *right );
                     if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, left, right);
                  }
                }
                --left;
                std::swap( *begin, *left );
                if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, left, begin);
                Sort( begin, left, cmp );
                Sort( right, end, cmp );
            }
        }
    };

    template<
        typename Container,
        typename Visualizer = DefaultVisualizer<Container>,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class MergeSort : public Sorting<Container, Visualizer>{
    public:
        MergeSort(Visualizer* visualizer = nullptr):
            Sorting<Container, Visualizer>(visualizer){}

        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) override {
            using Iterator = typename Container::iterator;
            if (begin < end-1) {
                Iterator middle = begin + (end - begin) / 2;
                Sort(begin , middle, cmp);
                Sort(middle, end, cmp);
                Merge(begin, middle, end, cmp);
            }
        }

        void Merge(typename Container::iterator begin, typename Container::iterator middle,
                   typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp) {
            using Iterator = typename Container::iterator;
            Container left(middle - begin);
            Container right(end - middle);
            for(Iterator i = begin, k=left.begin(); i<middle; i++, k++){
                if(this->visualizer) this->visualizer->Visualize(Operation::ACCESS, i);
                *k = *i;
            }
            for(Iterator i = middle, k=right.begin(); i<end; i++, k++){
                if(this->visualizer) this->visualizer->Visualize(Operation::ACCESS, i);
                *k = *i;
            }
            Iterator i = left.begin();
            Iterator j = right.begin();
            Iterator current = begin;
            while (i < left.end() && j < right.end()) {
                if (cmp(*i, *j)) {
                    *current = *i;
                    i++;
                } else {
                    *current = *j;
                    j++;
                }
                if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, current);
                current++;
            }
            for(; i<left.end(); i++, current++){
                *current = *i;
                if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, current);
            }
            for(; j<right.end(); j++, current++){
                *current = *j;
                if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, current);
            }
        }
    };

    template<
        typename Container,
        typename Visualizer = DefaultVisualizer<Container>,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class MergeSortInPlace : public Sorting<Container, Visualizer>{
    public:
        MergeSortInPlace(Visualizer* visualizer = nullptr):
            Sorting<Container, Visualizer>(visualizer){}

        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) override {
            using Iterator = typename Container::iterator;
            if (begin < end-1) {
                Iterator middle = begin + (end - begin) / 2;
                Sort(begin , middle, cmp);
                Sort(middle, end, cmp);
                Merge(begin, middle, end, cmp);
            }
        }

        void Merge(typename Container::iterator begin, typename Container::iterator middle,
                   typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp) {
            using Iterator = typename Container::iterator;
            using ValueType = typename std::iterator_traits<typename Container::iterator>::value_type;
            Iterator begin2 = middle;
            while (begin < middle && begin2 < end) {
                if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, begin2, begin);
                if (cmp(*begin2, *begin)) {
                    if(this->visualizer) this->visualizer->Visualize(Operation::ACCESS, begin2);
                    ValueType value = *begin2;
                    Iterator cur = begin2;
                    while (cur != begin) {
                        if(this->visualizer) this->visualizer->Visualize(Operation::ACCESS, cur-1);
                        *cur = *(cur - 1);
                        if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, cur);
                        cur--;
                    }
                    *begin = value;
                    if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, begin);
                    middle++;
                    begin2++;
                }
                begin++;
            }
        }
    };

    template<
        typename Container,
        typename Visualizer = DefaultVisualizer<Container>,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class HeapSort : public Sorting<Container, Visualizer>{
    public:
        HeapSort(Visualizer* visualizer = nullptr):
            Sorting<Container, Visualizer>(visualizer){}

        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) override {
            using Iterator = typename Container::iterator;
            for (Iterator i = begin + (end-begin) / 2 - 1; i >= begin; i--){
                Heapify(begin, end, i, cmp);
            }
            for (Iterator i=end-1; i>=begin; i--)
            {
                std::swap(*begin, *i);
                if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, i, begin);
                Heapify(begin, i, begin, cmp);
            }
        }

    private:
        void Heapify(typename Container::iterator begin, typename Container::iterator end,
                     typename Container::iterator cur,
                     std::function<bool (
                     typename std::iterator_traits<typename Container::iterator>::value_type,
                     typename std::iterator_traits<typename Container::iterator>::value_type)> cmp)
        {
            using Iterator = typename Container::iterator;
            Iterator largest = cur;
            Iterator left = begin+2*(cur-begin) + 1;
            Iterator right = begin+2*(cur-begin) + 2;
            if (left < end &&
                (this->visualizer ?
                 this->visualizer->Visualize(Operation::COMPARISON, left, largest) : true)
                    && !cmp(*left, *largest)){
                largest = left;
            }
            if (right < end &&
               (this->visualizer ?
                this->visualizer->Visualize(Operation::COMPARISON, right, largest) : true)
                && !cmp(*right, *largest)){
                largest = right;
            }
            if (largest != cur)
            {
                std::swap(*cur, *largest);
                if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, cur, largest);
                Heapify(begin, end, largest, cmp);
            }
        }
    };

    //Combine
    template<
        typename Container,
        typename Visualizer = DefaultVisualizer<Container>,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class TimSort : public Sorting<Container, Visualizer>{
    public:
        TimSort(Visualizer* visualizer = nullptr):
            Sorting<Container, Visualizer>(visualizer){}

        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) override {
            using Iterator = typename Container::iterator;
            const int RUN = 32;
            InsertionSort<Container, Visualizer> insertionSort(this->visualizer);
            MergeSort<Container, Visualizer> mergeSort(this->visualizer);
            for (Iterator i = begin; i < end; i+=RUN){
                insertionSort.Sort(i, std::min(i+RUN, end), cmp);
            }
            for (int size = RUN; size < end-begin; size *= 2) {
                for (Iterator left = begin; left < end; left += 2*size) {
                    Iterator middle = left + size;
                    Iterator right = std::min(left + 2*size, end);
                    if(middle < right){
                        mergeSort.Merge(left, middle, right, cmp);
                    }
                }
            }
        }
    };

    //Combine
    template<
        typename Container,
        typename Visualizer = DefaultVisualizer<Container>,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class IntroSort : public Sorting<Container, Visualizer>{
    public:
        IntroSort(Visualizer* visualizer = nullptr):
            Sorting<Container, Visualizer>(visualizer),
            m_HeapSort(visualizer) {}

        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) override {
            using Iterator = typename Container::iterator;
            if(end - begin > 32){
                Iterator left  = begin;
                Iterator right = end;
                if(this->visualizer) this->visualizer->Visualize(Operation::ACCESS, left);
                Iterator pivot = left++;
                while( left != right ) {
                  if( (this->visualizer ? this->visualizer->Visualize(Operation::COMPARISON, left) : true) && cmp( *left, *pivot ) ) {
                     ++left;
                  } else {
                     while( left != --right &&
                            (this->visualizer ?
                             this->visualizer->Visualize(Operation::COMPARISON, right)
                             : true) && cmp( *pivot, *right ) );
                     std::swap( *left, *right );
                     if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, left, right);
                  }
                }
                --left;
                std::swap( *begin, *left );
                if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, left, begin);
                Sort( begin, left, cmp );
                Sort( right, end, cmp );
            }
            else{
                m_HeapSort.Sort(begin, end, cmp);
            }
        }

    private:
        HeapSort<Container, Visualizer> m_HeapSort;
    };

    template<
        typename Container,
        typename Visualizer = DefaultVisualizer<Container>,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class ShellSort : public Sorting<Container, Visualizer>{
    public:
        ShellSort(Visualizer* visualizer = nullptr):
            Sorting<Container, Visualizer>(visualizer){}

        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) override {
            using ValueType = typename std::iterator_traits<typename Container::iterator>::value_type;
            for (size_t gap = (end-begin)/2; gap > 0; gap /= 2){
                {
                    for (size_t i = gap; i < end-begin; i++)
                    {
                        if(this->visualizer) this->visualizer->Visualize(Operation::ACCESS, begin+i);
                        ValueType temp = *(begin+i);
                        size_t j;
                        for (j = i; j >= gap &&
                             (this->visualizer != nullptr ?
                                                    this->visualizer->Visualize(Operation::COMPARISON, begin + j - gap) :true)
                             && !cmp(*(begin + j - gap), temp); j -= gap){
                            if(this->visualizer) this->visualizer->Visualize(Operation::ACCESS, begin + j - gap);
                            *(begin + j) = *(begin + j - gap);
                            if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, begin+j);
                        }
                        *(begin + j) = temp;
                        if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, begin+j);
                    }
                }
            }
        }
    };

    //works only with cmp equal to < or >
    template<
        typename Container,
        typename Visualizer = DefaultVisualizer<Container>,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class PigeonholeSort : public Sorting<Container, Visualizer>{
    public:
        PigeonholeSort(Visualizer* visualizer = nullptr):
            Sorting<Container, Visualizer>(visualizer){}

        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) override {
            using Iterator = typename Container::iterator;
            using ValueType = typename std::iterator_traits<typename Container::iterator>::value_type;
            if(this->visualizer) this->visualizer->Visualize(Operation::ACCESS, begin);
            Iterator min = begin;
            Iterator max = begin;
            for (Iterator i = begin+1; i < end; i++) {
                if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, i, min);
                if (cmp(*i, *min)) min = i;
                if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, i, max);
                if (cmp(*max, *i)) max = i;
            }
            size_t range = (*max > *min ? *max - *min : *min - *max) + 1;
            std::vector<ValueType>holes[range];
            for (Iterator i = begin; i < end; i++){
                if(this->visualizer) this->visualizer->Visualize(Operation::ACCESS, i, min);
                if(*max > *min){
                    holes[*i - *min].push_back(*i);
                }
                else{
                    holes[*min - *i].push_back(*i);
                }
            }
            Iterator cur = begin;
            for (auto& hole:holes) {
                for (auto& item:hole){
                    *cur = item;
                    if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, cur);
                    cur++;
                }
            }
        }
    };

    template<
        typename Container,
        typename Visualizer = DefaultVisualizer<Container>,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class BucketSort : public Sorting<Container, Visualizer>{
    public:
        BucketSort(Visualizer* visualizer = nullptr):
            Sorting<Container, Visualizer>(visualizer),
            m_InsertionSort(visualizer) {}

        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) override {
            using Iterator = typename Container::iterator;
            using ValueType = typename std::iterator_traits<typename Container::iterator>::value_type;

            if(end - begin < 11){
                m_InsertionSort.Sort(begin, end, cmp);
                return;
            }

            Iterator min = begin;
            Iterator max = begin;
            for (Iterator i = begin+1; i < end; i++) {
                if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, i, min);
                if (cmp(*i, *min)) min = i;
                if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, i, max);
                if (cmp(*max, *i)) max = i;
            }

            std::vector<ValueType>buckets[end - begin + 1];

            for (Iterator i = begin; i < end; i++) {
                size_t bi;
                if(*min < *max){
                    if(this->visualizer) this->visualizer->Visualize(Operation::ACCESS, i, max);
                    bi = double(*i) / *max * (end-begin);
                    buckets[bi].push_back(*i);
                }
                else{
                    if(this->visualizer) this->visualizer->Visualize(Operation::ACCESS, i, min);
                    bi = double(*i) / *min * (end-begin);
                    buckets[end - begin-bi].push_back(*i);
                }
            }

            Iterator cur = begin;
            for (std::vector<ValueType>& bucket: buckets){
                for (ValueType& item: bucket){
                    *cur = item;
                    if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, cur);
                    cur++;
                }
            }

            cur = begin;

            for (const auto& bucket:buckets){
                Sort(cur, cur+bucket.size(), cmp);
                cur+=bucket.size();
            }
        }

    private:
        InsertionSort<Container, Visualizer>m_InsertionSort;
    };
}
