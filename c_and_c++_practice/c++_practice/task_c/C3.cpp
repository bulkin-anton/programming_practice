#include <iostream>

class DebugPrinter;

class IntCharPair
{
    public:
        IntCharPair(int, char);
        friend DebugPrinter& out(DebugPrinter&, const IntCharPair&);
    private:
        int n;
        char c;
};

IntCharPair::IntCharPair(int a, char b){
    n = a;
    c = b;
}

class DebugPrinter{
    public:
        static DebugPrinter& get();
        DebugPrinter& out(int);
        DebugPrinter& out(char);
    private:
        struct Object{
            DebugPrinter *ptr;
            int cnt;
            ~Object();
        };
        static Object obj;
        DebugPrinter();
        ~DebugPrinter();
};

DebugPrinter::Object DebugPrinter::obj = {0, 0};

DebugPrinter::Object::~Object(){
    delete ptr;
    cnt = 0;
}

DebugPrinter::DebugPrinter(){
    std::cout << "Debugger is created." << std::endl;
}

DebugPrinter::~DebugPrinter(){
    std::cout << "Debugger is destroyed." << std::endl;
}

DebugPrinter&
DebugPrinter::out(int x){
    std::cout << x;
    return *this;
}

DebugPrinter&
DebugPrinter::out(char x){
    std::cout << x;
    return *this;
}

DebugPrinter&
DebugPrinter::get(){
    if (obj.cnt == 0){
        obj.ptr = new DebugPrinter;
        obj.cnt++;
        return *obj.ptr;
    } else return *obj.ptr;
}

DebugPrinter&
out(DebugPrinter& x, const IntCharPair& pair){
    return x.out('(').out(pair.n).out(',').out(' ').out(pair.c).out(')');
}
