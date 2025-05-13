class C{
public:
    virtual ~C();
    int x;
    int y;
};

C::~C() {}

class A: public C{
};

class B: public C{
};

enum {LINE = -1};

#include <iostream>
int main(){
    int x;
    std::cin >> x;
    try{
        C c;
        A &a = static_cast<A &>(c);
        std::cout << "NO 1" << std::endl;
        B &b = dynamic_cast<B &>(a);
std::cout << "NO 1" << std::endl;
        if (static_cast<void *>(&a) == static_cast<void *>(&b)){
            std::cout << "ERROR 1" << std::endl;
            throw LINE;
        }
std::cout << "No 2" << std::endl;
        a.x = x;
        int i = c.x;
        if (i != x) throw LINE;

        b.x = 8;
        a.x = 10;
        if (b.x != 10) throw LINE;

        b.y = x;
        a.y = 5;
        i = b.y;
        if (i != x) throw LINE;

        std::cout << x << std::endl;
    } catch (int n){
        std::cout << n << std::endl;
    }
}
