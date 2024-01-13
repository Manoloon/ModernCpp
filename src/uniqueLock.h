//
// Created by pablo on 13/1/2024.
//

#ifndef MODERNCPP_UNIQUELOCK_H
#define MODERNCPP_UNIQUELOCK_H
#include <thread>
#include <iostream>
#include <mutex>
#include <chrono>

namespace uniqueLock{
    using namespace std::chrono_literals;
    std::mutex mutex;
    void Task1(){
        std::lock_guard lck_guard(mutex) ;
        std::this_thread::sleep_for(5s);
    }
}
#endif //MODERNCPP_UNIQUELOCK_H
