//
// Created by pablo on 13/1/2024.
//

#ifndef MODERNCPP_UNIQUELOCK_H
#define MODERNCPP_UNIQUELOCK_H
#include <thread>
#include <iostream>
#include <mutex>
#include <chrono>
#include <string_view>

namespace uniqueLock{
    using namespace std::chrono_literals;
    std::mutex mutex;
    void Print(std::string_view str){
        for(int i =0; i<5;i++){
            try{   
        	std::lock_guard lck_guard(mutex);
            std::cout << str[0] << str[1] << str[2] << std::endl;
            throw Exception;	
        	std::this_thread::sleep_for(5s);
            }
            catch(const Exception& e){
                std::cout << "Exception caught :" << e.what() << std::endl;
            }
        } 
    }
}
#endif //MODERNCPP_UNIQUELOCK_H
