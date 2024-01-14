#ifndef MODERNCPP_LOCKGUARD_H
#define MODERNCPP_LOCKGUARD_H
#include <thread>
#include <iostream>
#include <mutex>
#include <chrono>
#include <string_view>

namespace LckGuard{
    using namespace std::chrono_literals;
    std::vector<std::string> strings{"abc","def","ghi","jkl","mno"};
    std::mutex mutex;
    void Print(){
        for(int i =0; i<5;i++){
            try{   
        	std::lock_guard lck_guard(mutex);
            std::cout << strings[0] << strings[1] << strings[2] << std::endl;
            throw std::exception();
        	std::this_thread::sleep_for(5s);
            }
            catch(const std::exception& e){
                std::cout << "Exception caught :" << e.what() << std::endl;
            }
        } 
    }
}
#endif //MODERNCPP_LOCKGUARD_H