//
// Created by Manoloon on 28/12/2023.
//
#include <thread>
#include <vector>
#include <string>
#include "src/MyTimer.h"

#include "src/uniqueLock.h"
#include "src/ThreadSafeVector.h"
void ThreadVec(const std::vector<std::string>& vec)
{
    ThreadSafeVec<int> tsVec;
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; i++) {
        // testing unique_lock
        //threads.emplace_back(uniqueLock::Print, strings[i]);
        tsVec.push_back(i);
        tsVec.print();
    }
    for (auto &t: threads) {
        if (t.joinable()) {
            t.join();
        }
    }
}
int main() {
    
    std::vector<std::string> strings{"abc", "def", "ghi", "jkl", "mno"};
    auto t1 = MyTimer<std::chrono::nanoseconds>::duration(ThreadVec,strings);
    std::cout << std::endl;
    std::cout << std::chrono::duration<double,std::milli>(t1).count() << "ms";
}