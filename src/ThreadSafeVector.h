#ifndef MODERNCPP_THREADSAFEVECTOR_H
#define MODERNCPP_THREADSAFEVECTOR_H

#include<vector>
#include<mutex>

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
#endif //MODERNCPP_THREADSAFEVECTOR_H