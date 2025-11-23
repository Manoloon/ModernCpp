#pragma once
#include <type_traits>
#include <utility>
#include <atomic>
#include <type_traits>
#include <concepts>

/*
    Basic naive smart pointers
*/
// all three deleters when called on T*, it applies some function to that pointer

// wraps a copyable state(function pointer)
template<class T>
struct deleter_pointer_wrapper
{
    void (*pf) (T*);
    deleter_pointer_wrapper(void (*pf) (T*)) : pf{pf}{}

    void operator() (T* p) const {pf(p);}
};

template<class T>
struct default_deleter
{
    void operator() (T* p) const {delete p;}
};

template<class T>
struct default_deleter<T[]>
{
    void operator() (T* p) const {delete[] p;}
};

// most types are not candidates to be deleter functions.
template <class T>
struct is_deleter_function_candidate : std::false_type{};
template <class T>
struct is_deleter_function_candidate<void (*)(T*)>:std::true_type{};
template <class T>
constexpr auto is_deleter_function_candidate_v = is_deleter_function_candidate<T>::value;
/*
    unique_ptr general template

*/

template<class T,class D = default_deleter<T>>
class unique_ptr : std::conditional_t <is_deleter_function_candidate_v<D>,
                    deleter_pointer_wrapper<T>,D>
{
    using deleter_type = std::conditional_t<is_deleter_function_candidate_v<D>,deleter_pointer_wrapper<T>,D>;
    T* p = nullptr;
public:
    unique_ptr() =default;
    unique_ptr(T* p) : p{p} {}
    unique_ptr(T* p, void (*pf)(T*)): deleter_type{pf},p{p}{}
    ~unique_ptr()
    {
        (*static_cast<deleter_type*>(this)) (p);
    }

    // 
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;
    void swap(unique_ptr& other) noexcept 
    {
        std::swap(p,other.p);
    }
    // move constructor using exchange so p = other.p and other.p = nullptr
    unique_ptr(unique_ptr&& other) noexcept : p{std::exchange(other.p,nullptr)}{}
    unique_ptr& operator=(unique_ptr&& other) noexcept
    {
        unique_ptr{std::move(other)}.swap(*this);
    }

    // bool operator
    bool empty() const noexcept {return !p;}
    operator bool() const noexcept {return !empty();}
    bool operator==(const unique_ptr& other) const noexcept 
    {
        return p == other.p;
    }
    bool operator !=(const unique_ptr& other) const noexcept
    {
        return !(*this == other);
    }
    T* get() noexcept 
    {
        return p;
    }
    const T* get() const noexcept 
    {
        return p;
    }
    // Pointer-like functions
    T& operator*() noexcept {return *p;}
    const T& operator*() const noexcept {return *p;}
    T& operator->() noexcept {return p;}
    const T& operator->() const noexcept {return p;}
};

// unique_ptr specialization for arrays
template<class T,class D>
class unique_ptr<T[], D> : std::conditional_t<is_deleter_function_candidate_v<D>,deleter_pointer_wrapper<T>,D>
{
    using deleter_type = std::conditional_t<is_deleter_function_candidate_v<D>,deleter_pointer_wrapper<T>,D>;
    T* p = nullptr;
    public:
    unique_ptr() = default;
    unique_ptr(T* p): p{p}{}
    unique_ptr(T* p, void (*pf)(T*)) : deleter_type{pf},p{p}{}
    ~unique_ptr()
    {
        (*static_cast<deleter_type*>(this)) (p);
    }

    // 
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;
    void swap(unique_ptr& other) noexcept 
    {
        std::swap(p,other.p);
    }
    // move constructor using exchange so p = other.p and other.p = nullptr
    unique_ptr(unique_ptr&& other) noexcept : p{std::exchange(other.p,nullptr)}{}
    unique_ptr& operator=(unique_ptr&& other) noexcept
    {
        unique_ptr{std::move(other)}.swap(*this);
    }

    // bool operator
    bool empty() const noexcept {return !p;}
    operator bool() const noexcept {return !empty();}
    bool operator==(const unique_ptr& other) const noexcept 
    {
        return p == other.p;
    }
    bool operator !=(const unique_ptr& other) const noexcept
    {
        return !(*this == other);
    }
    T* get() noexcept 
    {
        return p;
    }
    const T* get() const noexcept 
    {
        return p;
    }
    // pointer-like functions 
    T& operator[](std::size_t n) noexcept {return p[n];}
    const T& operator[](std::size_t n) const noexcept {return p[n];}
};

/*
    SharedPtr
*/
template<class T>
class shared_ptr{
    T* p = nullptr;
    std::atomic<long long> *counter = nullptr;
    public:
    shared_ptr() = default;
    shared_ptr(T* p):p{p}
    {
        if(p) try
        {
            counter = new std::atomic<long long>(1LL);
        } catch(...)
        {
            delete p;
            throw;
        }
    }
    shared_ptr(const shared_ptr &other): p{other.p}, counter{other.counter}
    {
        if(counter) ++(*counter);
    }
    shared_ptr(shared_ptr&& other) noexcept :p{std::exchange(other.p,nullptr)},
                                            counter{std::exchange(other.counter,nullptr)}{}
                                            bool empty() const noexcept {return !p;}

    ~shared_ptr()
    {
        if(counter)
        {
            auto expected = counter->load();
            auto desired = expected -1 ;
            while (counter->compare_exchange_weak(expected,desired))
            {
                desired = expected - 1;
            }
            if(desired == 0)
            {
                delete p;
                delete counter;
            }
        }
    }
    // operators
    operator bool() const noexcept {return !empty();}

    void swap(shared_ptr& other) noexcept 
    {
        std::swap(p,other.p);
        std::swap(counter,other.counter);
    }
    
    shared_ptr& operator=(const shared_ptr& other)
    {
        shared_ptr{other}.swap(*this);
        return *this;
    }
    shared_ptr& operator=(shared_ptr&& other) noexcept
    {
        shared_ptr{std::move(other)}.swap(*this);
        return *this;
    }
    bool operator==(const shared_ptr& other) const noexcept {return p == other.p;}
    // if std::c++20 this is infered.
    bool operator!=(const shared_ptr& other) const noexcept {return !(*this == other.p);}
    T* get() noexcept {return p;}
    const T* get() const noexcept {return p;}
    T& operator*() noexcept {return *p;}
    const T& operator*() const noexcept {return *p;}
    T* operator->() noexcept {return p;}
    const T* operator->() const noexcept { return p;}
};

/*
    dup_ptr its a smart ptr that handle single ownership ( movable but NOT copyable) but duplication of the pointee allowed
*/
// interface for clonable pointer
// this option is the less desirable because it force the user to use the interface , this also add an overhead
struct IClonable
{
    virtual IClonable* clone() const = 0;
    virtual ~IClonable() = default;
};
// using concepta
template<class T>
concept clonable = requires(const T* p)
{
    {p->clone()}-> std::convertible_to<T*>;
};
struct Copier
{
    template<class T>
    T* operator() (const T *p) const {return new T{*p};}
};
struct Cloner
{
    template<class T>
    T* operator() (const T* p) const { return p->clone();}
};
namespace usingInterface
{
    template<class T, class Dup = std::conditional_t<std::is_base_of_v<IClonable,T>,Cloner,Copier>>
    class dup_ptr
    {
        T* p{};
        public:
        dup_ptr(const dup_ptr& other):p{other.empty()? nullptr : Dup{}(other.p)}{}
    };
}

///////////////////////////////////////////////////////////
// using type_traits , Dr Walter Brown std::void_t
// std::void_t relies in SFINAE (Substitution failure is not an error)
template<class,class = void>
struct has_clone : std::false_type{};
template<class T>
constexpr bool has_clone_v = has_clone<T>::value;

template<class T, class Dup = std::__conditional_t<has_clone_v<T>,Cloner,Copier>>
class dup_ptr
{
    T* p{};
    public:
    dup_ptr(const dup_ptr& other): p{other.empty() ? nullptr : Dup{}(other.p)}{}
};
/////////////////////////////
/////// using concepts 

namespace usingConcepts
{
    template<class T, class Dup = std::conditional_t<clonable<T>,Cloner,Copier>>
    class dup_ptr
    {
        T* p{};
        public:
        dup_ptr(const dup_ptr& other):p{other.empty()? nullptr : Dup{}(other.p)}{}
    };
}

///////////////////////////////////////////////////////////////
void TestUniquePtr()
{
    struct X{};
    // this goes on main
    //unique_ptr<X> p{new X};
    class S
    {
        ~S(){}
        public:
        static void destroy(X *p){delete p;}
    };
    //this goes on main
    //unique_ptr<S,&S::destroy> p{new S;}
}
void TestSharedPtr()
{
    /*
    #include <thread>
    #include <chrono>
    #include <random>
    #include <iostream>

    struct X
    {
    int n;
    X(int n): n{n}{}
    ~X() { std::cout << "X::~X()\n";}
    };
    int main()
    {
        std::mt19937 prng{std::random_device{}()};
        std::uniform_int_distribution<int> die{200,300};
        shared_ptr<X> p{ nre X{3}};
        using std::chrono::milliseconds;
        std::thread th0{ [p, dt = die(prng)] 
        {
            std::this_thread::sleep_for(milliseconds{dt});
            std::cout << "end of th0, p->n: " << p->n << '\n';
        }};
        std::thread th1{ [p, dt = die(prng)] 
        {
            std::this_thread::sleep_for(milliseconds{dt});
            std::cout << "end of th1, p->n: " << p->n << '\n';
        }};
        th1.detatch();
        th0.detatch();
        std::this_thread::sleep_for(350ms);
        std::cout << "end main()\n";
    }
    */
}
