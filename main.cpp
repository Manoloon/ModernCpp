//
// Created by Manoloon on 28/12/2023.
//
#include <thread>
#include <vector>
#include "src/TimedMutex.h"
#include "src/lockGuard.h"
#include "src/ThreadSafeVector.h"
int main() {
		std::vector<std::jthread> threads;
		std::vectors<std::string_view> strings{"abc","def","ghi","jkl","mno"};
		for(int i = 0; i<5;i++){
					threads.emplace_back(lockguard::Print(strings[i]));
		}	
}