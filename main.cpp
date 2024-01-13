//
// Created by Manoloon on 28/12/2023.
//
#include <thread>
#include <vector>
#include "src/TimedMutex.h"
#include "src/lockGuard.h"


int main() {
		std::vector<std::jthread> threads;
		for(int i = 0; i<5;i++){
					threads.emplace_back(i);
		}
for(auto t : threads){
					
		}
	
}