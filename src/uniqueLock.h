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

namespace uniqueLock {
    using namespace std::chrono_literals;
    std::mutex mutex;

    void Print(std::string_view str) {
        for (int i = 0; i < 5; i++) {
            std::unique_lock uniLock(mutex);
            std::cout << str[0] << str[1] << str[2] << std::endl;
            uniLock.unlock();
            std::this_thread::sleep_for(50ms);
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
        threads.emplace_back(uniqueLock::Print, strings[i]);
    }
    for (auto &t: threads) {
        if (t.joinable()) {
            t.join();
        }
    }
}
 * */
#endif //MODERNCPP_UNIQUELOCK_H
