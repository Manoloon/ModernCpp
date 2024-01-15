//
// Created by Manoloon on 28/12/2023.
//
#include <thread>
#include <vector>
#include <string>

#include "src/uniqueLock.h"
#include "src/ThreadSafeVector.h"

int main() {
    ThreadSafeVec<int> tsVec;
    std::vector<std::thread> threads;
    std::vector<std::string> strings{"abc", "def", "ghi", "jkl", "mno"};
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