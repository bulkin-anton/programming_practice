#include <iostream>

class A{
    public:
        A();
        void get_0() const;
        static int x;
};

A::A(){
    x = 0;
}

void
A::get_0() const{
    std::cout << "I AM THE BEST STUDENT!" << std::endl;
};
/*
int A::x;
int
main()
{
    const A a;
    a.x = 1;
    a.get_0();
    return 0;
}*/
