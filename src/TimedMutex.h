//
// Created by pablo on 13/1/2024.
//

#ifndef MODERNCPP_TIMEDMUTEX_H
#define MODERNCPP_TIMEDMUTEX_H
#include <mutex>
#include <thread>
#include <chrono>
#include <iostream>
using namespace std::chrono_literals;
// timed_mutex
//try_lock_until();
//try_lock_for(n)
namespace timed_mutex_tryFor{
    std::timed_mutex tmutex;
    void Task1(){
        std::cout << "Task1 : try lock" << "\n";
        tmutex.lock();
        std::this_thread::sleep_for(5s);
        std::cout << "Task1 : unlock" << "\n";
        tmutex.unlock();
    }
    void Task2(){
        std::this_thread::sleep_for(500ms);
        std::cout << "Task2 : try to lock" << "\n";
        while(!tmutex.try_lock_for(1s)){
            std::cout << "Task2 : could not lock" << "\n";
        }
        std::cout << "Task2 : has locked mutex" << "\n";
        tmutex.unlock();
    };
}
namespace timed_mutex_tryUntil{
    auto time_point = std::chrono::system_clock::now() + 900ms;
    std::timed_mutex tmutex;
    void Task1(){
        std::cout << "Task1 : try lock" << "\n";
        tmutex.lock();
        std::this_thread::sleep_for(5s);
        std::cout << "Task1 : unlock" << "\n";
        tmutex.unlock();
    }
    void Task2(){
            //std::thread::sleep(500ms);
            std::cout << "Task2 : try to lock" << std::endl;
            while(!tmutex.try_lock_until(time_point)){
                std::cout << "Task2 : could not lock" << std::endl;
            }
            std::cout << "Task2 : has locked mutex\n";
            tmutex.unlock();
    }
}
#endif //MODERNCPP_TIMEDMUTEX_H
