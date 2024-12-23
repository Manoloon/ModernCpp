#pragma once
#include <concepts>
#include <ranges>
#include <algorithm>

#include <vector>
#include <iostream>

template<typename T>
concept IsSortable =
    std::ranges::range<T> &&
    std::sortable<std::ranges::iterator_t<T>> &&
    std::integral<std::ranges::range_value_t<T>>;

namespace myAlgo
{
    template<typename T>
    requires IsSortable<T>
    void sort(T& container)
    {
        std::sort(std::begin(container),std::end(container));
    };
}

void MySortTest()
{
    std::vector<int> vec{98, 38, 24, 66, 70, 48, 82, 41, 8, 29, 10, 1, 40, 53, 7, 80, 43, 45, 46, 25, 
                        68, 96, 14, 95, 20, 31, 74, 75, 16, 85, 30, 34, 92, 58, 42, 19, 33, 56, 79, 59, 
                        65, 22, 73, 44, 83, 71, 49, 36, 21, 11, 84, 63, 28, 26, 37, 67, 77, 89, 39, 69, 
                        81, 52, 13, 3, 27, 100, 15, 97, 76, 47, 78, 54, 60, 72, 32, 57, 99, 35, 64, 93, 62, 
                        55, 88, 86, 87, 50, 9, 23, 6, 5, 12, 17, 61, 4, 2, 18, 51, 94, 91, 90};
    myAlgo::sort(vec);
    for(auto v : vec)
    {
        std::cout << v << ",";
    }
    std::cout << '\n';
}