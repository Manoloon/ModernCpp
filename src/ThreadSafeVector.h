#ifndef MODERNCPP_THREADSAFEVECTOR_H
#define MODERNCPP_THREADSAFEVECTOR_H

#include<vector>
#include<mutex>

#include <thread>
#include "MyTimer.h"
#include <iostream>

template<typename T>
class ThreadSafeVec{
    std::mutex mut;
    std::vector<T> vec;
    public:
    void push_back(const T& item){
        mut.lock();
        vec.push_back(item);
        mut.unlock();
    }
    void print(){
        mut.lock();
        for(auto i : vec){
            std::cout << i << ", ";
        }
        mut.unlock();
    }
};
/*
 * main used:
 * int main() {
    ThreadSafeVec<int> tsVec;
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; i++) {
        tsVec.push_back(i);
        tsVec.print();
    }
    for (auto &t: threads) {
        if (t.joinable()) {
            t.join();
        }
    }
}
 * */
void TvecSafeTest()
{
    ThreadSafeVec<int> tsVec;
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; i++) {
        tsVec.push_back(i);
        tsVec.print();
    }
    for (auto &t: threads) {
        if (t.joinable()) {
            t.join();
        }
    }
    std::vector<std::string> strings{"abc", "def", "ghi", "jkl", "mno"};
    auto t1 = MyTimer<std::chrono::nanoseconds>::duration(tsVec,strings);
    std::cout << std::endl;
    std::cout << std::chrono::duration<double,std::milli>(t1).count() << "ms";
}
#endif //MODERNCPP_THREADSAFEVECTOR_H