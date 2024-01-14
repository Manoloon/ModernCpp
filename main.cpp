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
		for(int i = 0; i<5;i++){
            threads.emplace_back(LckGuard::Print);
		}
        for(auto &t : threads){
            t.join();
        }

}