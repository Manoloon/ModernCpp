#pragma once
/*
    templates with ranges and views to filter
*/
#include <ranges>
#include <iostream>

void FindGreaterAndDoubleIt(std::span<int>numbers,int lowerBound = 0)
{
    auto isSmaller = [&lowerBound](int i) {return i < lowerBound;};
    auto toDouble = [](int i){ return i * 2;};
    // will only shows those numbers that match with filter and then transform them
    for(int d : numbers | std::views::filter(isSmaller) | std::views::transform(toDouble))
    {
        std::cout << d << ' ';
    }
}