//
// Created by Manoloon on 9/1/2024.
//

#ifndef MODERNCPP_BASICTHREADS_H
#define MODERNCPP_BASICTHREADS_H
#include <thread>

class ThreadGuard{
    std::thread thr;
public:
    // move semantics
    ThreadGuard(std::thread&& _thr):thr(_thr){}
    ~ThreadGuard(){
        if(thr.joinable()){
            thr.join();
        }
    }
    ThreadGuard(const std::thread& thr) = delete;
    ThreadGuard operator=(const std::thread& thr) = delete;
};

void HelloThread(){
    std::cout << "Hello" << std::endl;
}
namespace BasicThreads{
    try{
        std::std::thread thr(HelloThread);
        ThreadGuard(thr);
        // force an exception
        throw std::std::exception;
    }
    catch(std::std::exception e){
        std::cout << " an exception has occured : " << e.what() << std::endl;
    }

}
#endif //MODERNCPP_BASICTHREADS_H
