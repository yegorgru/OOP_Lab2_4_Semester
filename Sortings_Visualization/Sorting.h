#pragma once

#include <type_traits>
#include <iterator>
#include <algorithm>
#include <functional>

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
        SELECTIONSORT
    };

    class DefaultVisualizer{
    public:
        bool Visualize(Operation operation, size_t first, size_t second = INT_MAX);
    };

    template<
        typename Container,
        typename Visualizer = DefaultVisualizer,
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
        typename Visualizer = DefaultVisualizer,
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
                    if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, j-begin, j+1-begin);
                    if (cmp(*(j + 1), *j)){
                        std::swap(*j, *(j + 1));
                        if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, j-begin, j+1-begin);
                    }
                }
            }
        }
    };

    template<
        typename Container,
        typename Visualizer = DefaultVisualizer,
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
                ValueType key = *i;
                while (j > begin && (this->visualizer != nullptr ?
                       this->visualizer->Visualize(Operation::COMPARISON, j-1-begin) :true) &&
                       cmp(key,*(j-1))) {
                    *j = *(j-1);
                    if(this->visualizer) {
                        this->visualizer->Visualize(Operation::CHANGE, j-begin);
                        this->visualizer->Visualize(Operation::ACCESS, j-1-begin);
                    }
                    j--;
                }
                *j = key;
                if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, j-begin);
            }
        }
    };

    template<
        typename Container,
        typename Visualizer = DefaultVisualizer,
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
                    if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, j-begin, min-begin);
                    if (cmp(*j, *min))
                    {
                        min = j;
                        if(this->visualizer){
                            this->visualizer->Visualize(Operation::ACCESS, j-begin);
                            this->visualizer->Visualize(Operation::CHANGE, min-begin);
                        }
                    }
                }
                if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, i-begin, min-begin);
                if (min != i)
                {
                    std::swap(*i, *min);
                    if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, i-begin, min-begin);
                }
            }
        }
    };

    /*template<
        typename Container,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class CycleSort : public Sorting<Container>{
    public:
        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; },
                  std::function <void(Operation, size_t)> visualize = nullptr) override {
            using Iterator = typename Container::iterator;
            using ValueType = typename std::iterator_traits<typename Container::iterator>::value_type;
            for( Iterator i = begin; i < end - 1; i++ )
            {
                ValueType cur = *i;
                size_t pos = i-begin;
                for( Iterator j = i + 1; j < end; j++ ){
                    if( cmp(*j,cur)){
                        pos++;
                    }
                }
                if( i-begin == pos ){
                    continue;
                }
                while( *(begin+pos) == cur ){
                    pos++;
                }
                std::swap( cur, *(begin+pos));
                while( i-begin != pos ){
                    pos = i-begin;
                    for( Iterator j = i + 1; j < end; j++ ){
                        if( cmp(*j, cur)) {
                            pos++;
                        }
                    }
                    while( *(begin+pos) == cur ){
                        pos++;
                    }
                    std::swap( cur, *(begin+pos) );
                }
            }
        }
    };

    template<
        typename Container,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class ShakerSort : public Sorting<Container>{
    public:
        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; },
                  std::function <void(Operation, size_t)> visualize = nullptr) override {
            using Iterator = typename Container::iterator;
            size_t border=end-begin;
            Iterator left = begin;
            Iterator right = end - 1;
            do {
                for (Iterator i = left; i < right; i++) {
                    if (cmp(*(i+1), *i)) {
                        std::swap(*i, *(i+1));
                        border=i-begin;
                    }
                }
                right=begin+border;
                for (Iterator i = right; i > left; i--) {
                    if (cmp(*i, *(i-1))) {
                        std::swap(*i, *(i-1));
                        border=i-begin;
                    }
                }
                left=begin+border;
            } while (left < right);
        }
    };

    template<
        typename Container,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class CombSort : public Sorting<Container>{
    public:
        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; },
                  std::function <void(Operation, size_t)> visualize = nullptr) override {
            using Iterator = typename Container::iterator;
            const double factor = 1.2473309;
            size_t step = end-begin;
            while (step >= 1) {
                for (Iterator i = begin; i + step < end; i++) {
                    if (cmp(*(i+step),*i)) {
                        std::swap(*i, *(i + step));
                    }
                }
                step /= factor;
            }
        }
    };

    template<
        typename Container,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class GnomeSort : public Sorting<Container>{
    public:
        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; },
                  std::function <void(Operation, size_t)> visualize = nullptr) override {
            using Iterator = typename Container::iterator;
            Iterator i = begin+1;
            Iterator j = begin+2;
            while(i < end){
                if(cmp(*(i-1), *i)){
                    i = j;
                    j = j < end ? j+1 : j;
                }
                else{
                    std::swap(*(i-1), *i);
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
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class OddEvenSort : public Sorting<Container>{
    public:
        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; },
                  std::function <void(Operation, size_t)> visualize = nullptr) override {
            for (size_t i = 0; i < end-begin; i++) {
                for (size_t j = (i % 2) ? 0 : 1; j + 1 < end-begin; j += 2) {
                    if (cmp(*(begin+j+1), *(begin+j))) {
                        std::swap(*(begin+j+1), *(begin+j));
                    }
                }
            }
        }
    };*/
}
