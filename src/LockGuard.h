#ifndef MODERNCPP_LOCKGUARD_H
#define MODERNCPP_LOCKGUARD_H
#include <thread>
#include <iostream>
#include <mutex>
#include <chrono>
#include <string_view>

namespace LockGuard{
    using namespace std::chrono_literals;
    std::mutex mutex;
    void Print(std::string_view str){
        for(int i =0; i<5;i++){
            try{   
        	std::lock_guard lck_guard(mutex);
            std::cout << str[0] << str[1] << str[2] << std::endl;
            throw std::exception;
        	std::this_thread::sleep_for(5s);
            }
            catch(const std::exception& e){
                std::cout << "Exception caught :" << e.what() << std::endl;
            }
        } 
    }
}
#endif //MODERNCPP_LOCKGUARD_H