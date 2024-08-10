#pragma once

#include <chrono>
#include <iostream>
#include <functional>
#include <type_traits>

template <typename Time = std::chrono::microseconds,
          typename Clock = std::chrono::high_resolution_clock>
struct MyTimer
{
    template<typename F, typename... Args>
    static Time duration(F&& f, Args&&... args)
    {
        auto start = Clock::now();
        if constexpr (std::is_void_v<std::invoke_result_t<F, Args...>>)
            std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
        else
        {
            auto result = std::invoke(std::forward<F>(f),std::forward<Args>(args)...);
            (void)result;
        }
            
        auto end = Clock::now();
        return std::chrono::duration_cast<Time>(end - start);
    }
};