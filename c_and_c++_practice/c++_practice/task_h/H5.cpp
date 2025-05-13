#include <iostream>

template <typename T, typename U>
void f(T, U) { std::cout << "f-T-U" << std::endl; }

template <typename U>
void f(short, U) { std::cout << "f-short-U" << std::endl; }

template <typename T>
void f(T x, int) { std::cout << "f-T-int" << std::endl; void *p = &x[0]; }

template <typename T>
void f(T *, int) { std::cout << "f-T*-int" << std::endl; }

template <typename T, typename U>
void f(T, U, U) { std::cout << "f-T-U-U" << std::endl; }

template <>
void f(int, int) { std::cout << "f-int-int" << std::endl; }

void f(int, int) { std::cout << "int-int" << std::endl; }

void f(short, short) { std::cout << "short-short" << std::endl; }


#include <iostream>
#include <string>
// insert arguments for each call

int main()
{
    f(true, 1);    // f-T-U
    f(static_cast<std::string>("123"), 3);    // f-T-int
    f("123", 2);    // f-T*-int
    f(false, 1, 1);    // f-T-U-U
    f(short(1), long(1));    // f-short-U
    f(short(1), short(1));    // short-short
    f(1, 1);    // int-int
}
