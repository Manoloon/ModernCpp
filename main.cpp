//
// Created by Manoloon on 28/12/2023.
//
#include <thread>
#include <vector>
#include <string>
#include "src/TimedMutex.h"
#include "src/lockGuard.h"
#include "src/ThreadSafeVector.h"

int main() {
        std::vector<std::thread> threads;
        std::vector<std::string> strings{"abc","def","ghi","jkl","mno"};
		for(int i = 0; i<5;i++){
					threads.emplace_back(LockGuard::Print(strings[i]));
		}
        for(auto &t : threads){
            t.join();
        }
}