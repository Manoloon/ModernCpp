//
// Created by Manoloon on 28/12/2023.
//
#include <iostream>
#include <vector>
#include <string>

struct A {
    int x;
    int y;
};
void func(int&& y){
    std::cout << " y :" << y << std::endl;
}
int main() {
    //lambda
    // invoke
    std::cout << "invoke directly :" << [](int arg) { return (arg * 2); }(3) << std::endl;
    auto n = [](int arg) { return (arg * 2); }(1);
    std::cout << " invoke by assign : " << n << std::endl;

    // capture
    int x = 1;
    std::cout << "Capture by value x :" << [x](int arg) { return (arg * 2); }(2) << std::endl;
    [&x](int arg) { return (++x * arg); }(2);
    std::cout << "Capture by ref x :" << x << std::endl;

    // selective
    A ObjectA;
    ObjectA.x = 1;
    ObjectA.y = 1;
    std::cout << "Object A : " << ObjectA.x << ", " << ObjectA.y << std::endl;
    std::cout << "Selective Capture" << std::endl;
    [=, &ObjectA](int arg) { return (ObjectA.x++ * arg, 2 * arg); }(2);
    std::cout << "Capture selective ObjectA is by ref :" << ObjectA.x << ", others by value x : " << x << std::endl;

    // move semantics
    std::cout << "Move Semantics " << "\n";
    std::vector<std::string>vec(1000000);
    std::cout << " size of vec before move : " << vec.size() << std::endl;
    auto copyVec = vec;
    std::cout << " size of vec after copy to copyVec : " << vec.size() << ", size of copyVec: " << copyVec.size() <<  std::endl;
    auto vec2 = std::move(vec);
    std::cout << " size of vec after move : " << vec.size() << std::endl;
    std::cout << " size of vec2 after move : " << vec2.size() << std::endl;
    int a = 3; // same as *a = 3
    int *y = &a; // same as int y = a;
    func(4); // should be an rvalue; func(y) give error
}