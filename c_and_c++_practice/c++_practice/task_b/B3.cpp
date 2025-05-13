#include <iostream>
using namespace std;

class A{
    public:
        A();
        A(const A& x);
        A(double n);
        A(float a, unsigned short b);
        ~A(void);
        void m(void);
    private:
        int a = 0;
};

A::A(){
    cout << "1" << endl;
    a = 0;
}

A::A(const A& x){
    cout << "2" << endl;
    a = x.a;
}

A::A(double n){
    cout << "3" << endl;
    a = static_cast<int> (n);
}

A::A(float x, unsigned short b){
    cout << "4" << endl;
    a = static_cast<int> (x * b);
}

A::~A(void){
    cout << "5" << endl;
}

void A::m(void){
    A *x = new A;
    delete x;
    A *x1 = new A(3.5);
    A *x2 = new A(*x1);
    delete x1;
    delete x2;
    A x3(*this);
    A x4(2.5, 1);
}
