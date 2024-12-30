//
// Created by pablo on 13/1/2024.
//

#ifndef MODERNCPP_BASICMODERNCPP_H
#define MODERNCPP_BASICMODERNCPP_H
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <memory>
#include <thread>

struct A {
    int x;
    int y;
};

class MovableType {
public:
    MovableType(const MovableType &) = delete;

    MovableType &operator=(const MovableType &) = delete;

    MovableType(MovableType &&) noexcept = default;

    MovableType &operator=(MovableType &&) noexcept = default;

    MovableType() = default;
};

void func(int &&y) {
    std::cout << " pass rvalue y :" << y << std::endl;
}

void func(const int &y) {
    std::cout << " pass lvalue y :" << y << std::endl;
}

namespace lambda{
    // invoke
    void invoke(){
        std::cout << "invoke directly :" << [](int arg) { return (arg * 2); }(3) << std::endl;
        auto n = [](int arg) { return (arg * 2); }(1);
        std::cout << " invoke by assign : " << n << std::endl;
    }

    void capture(){
        // capture
        int x = 1;
        std::cout << "Capture by value x :" << [x](int arg) { return (arg * 2); }(2) << std::endl;
        [&x](int arg) { return (++x * arg); }(2);
        std::cout << "Capture by ref x :" << x << std::endl;
    }

    void selectiveCapture(){
        // selective
        A ObjectA;
        int x = 2;
        ObjectA.x = 1;
        ObjectA.y = 1;
        std::cout << "Object A : " << ObjectA.x << ", " << ObjectA.y << std::endl;
        std::cout << "Selective Capture" << std::endl;
        [=, &ObjectA](int arg) { return (ObjectA.x++ * arg, 2 * arg); }(2);
        std::cout << "Capture selective ObjectA is by ref :" << ObjectA.x << ", others by value x : " << x << std::endl;
    }
}

namespace moveSemantic{
    void Call(){
        // move semantics
        std::cout << "Move Semantics " << "\n";
        std::vector<std::string> vec(1000000);
        std::cout << " size of vec before move : " << vec.size() << std::endl;
        auto copyVec = vec;
        std::cout << " size of vec after copy to copyVec : " << vec.size() << ", size of copyVec: " << copyVec.size()
                  << std::endl;
        auto vec2 = std::move(vec);
        std::cout << " size of vec after move : " << vec.size() << std::endl;
        std::cout << " size of vec2 after move : " << vec2.size() << std::endl;
        int a = 3; // same as *a = 3
        int *y = &a; // same as int y = a;
        // choose correct implementation for rvalue or lvalue
        func(4);
        func(a);
        // using movable-only type;
        MovableType M1;
        MovableType M2(std::move(M1));
        //MovableType M3(M2); // cannot be copy;
    }
}

namespace randomNumbers{
    // create random number engine.
    std::mt19937 mt;
    void Call(){
        /// Random Numbers;
        std::uniform_int_distribution<int> uid(0,100);
        std::cout << " random int bt 0 - 100 : " << uid(mt) << std::endl;
        std::uniform_real_distribution<double> fid(0,1);
        std::cout << " random float bt 0 - 1 : " << fid(mt) << std::endl;

        // Smart pointers : unique_ptr
        auto uPtr = std::make_unique<std::string>("hola");
        std::cout << "unique ptr : " << *uPtr << std::endl;
    }
}
#endif MODERNCPP_BASICMODERNCPP_H