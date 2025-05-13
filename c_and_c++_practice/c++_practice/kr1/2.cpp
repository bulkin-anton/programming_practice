#include <iostream>

class A{
    public:
        A();
        A(const A&);
};

A::A() {}

A::A(const A&){
    std::cout << "inizialisation of creating object" << std::endl;
}

class B{
    public:
        B();
        B(const B&);
};

B::B() {}

B::B(const B&){
    std::cout << "objects passing as arguements in function by value" << std::endl;
}

class C{
    public:
        C();
        C(const C&);
};

C::C() {}

C::C(const C&){
    std::cout << "objects passing as return in function by value" << std::endl;
}

class D{
    public:
        explicit D(int i);
        D(const D &);
};

D::D(int i) {}

D::D(const D&){
    std::cout << "inizialisation of creating object by temporary one" << std::endl;
}

C
func(B a){
    C d;
    return d;
}

int main(){
    A a;
    A b = a;
    a = b;
    B d;
    C f;
    f = func(d);
    D c = D(1);
}
