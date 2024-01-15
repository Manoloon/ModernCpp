#ifndef MODERNCPP_LOCKGUARD_H
#define MODERNCPP_LOCKGUARD_H
#include <thread>
#include <iostream>
#include <mutex>
#include <chrono>
#include <string_view>

namespace LckGuard{
    using namespace std::chrono_literals;
    std::mutex mutex;
    void Print(std::string_view str){
        for(int i =0; i<5;i++){
            try{   
        	std::lock_guard lck_guard(mutex);
            std::cout << str[0] << str[1] << str[2] << std::endl;
                // if I run this, as the lockguard still in scope and
                //mutex still locked, every thread have to wait 50 miliseconds
                // thats why unique_lock are super useful.
            //throw std::exception();
        	std::this_thread::sleep_for(50ms);
            }
            catch(const std::exception& e){
                std::cout << "Exception caught :" << e.what() << std::endl;
            }
        } 
    }
}
/*
 * Use in main:
 * int main() {
    // lock guard use
    std::vector<std::thread> threads;
    std::vector<std::string> strings{"abc", "def", "ghi", "jkl", "mno"};
    for (int i = 0; i < 5; i++) {
        threads.emplace_back(LckGuard::Print,strings[i]);
    }
    for (auto &t: threads) {
        if (t.joinable()) {
            t.join();
        }
    }
}
 * */
#endif //MODERNCPP_LOCKGUARD_H