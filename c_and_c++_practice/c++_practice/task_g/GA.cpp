#include <iostream>

class A{
    public:
        virtual ~A();
};

A::~A() {}

class B{
    public:
        virtual ~B();
};

B::~B() {}

class C: public B, public A{
    public:
        C();
};

C::C() {}

static C a;

A*
f(){
    return &a;
}

int
main(){
    A* p = f();
    B* q;
    if ((q = dynamic_cast<B *>(p)) && (static_cast<void*>(p) != static_cast<void *>(q))){
        std::cout << "ALL GOOD" << std::endl;
    }
}
