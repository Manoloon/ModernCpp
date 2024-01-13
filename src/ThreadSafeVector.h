// thread safe vector class
// critical section : push_back()

#include<vector>
#include<mutex>

template class <typename T>
class ThreadSafeVec{
    std::mutex mut;
    std::vector<T> vec;
    public:
    void push_back(const T& item){
        mut.lock();
        vec.push_back(item);
        mut.unlock();
    }
};