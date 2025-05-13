#include <iostream>

class UniquePtr{
    public:
        UniquePtr();
        UniquePtr(UniquePtr& x);
        ~UniquePtr();
        static UniquePtr make(int n);
        char& get(int n);
        const char& get(int n) const;
    private:
        UniquePtr(int n);
        char *point;
        int size;
};

UniquePtr::UniquePtr(){
    point = 0;
    size = 0;
}

UniquePtr::UniquePtr(UniquePtr& x){
    size = x.size;
    point = x.point;
    x.point = 0;
    x.size = 0;
}

UniquePtr::UniquePtr(int n){
    point = new char[n];
    size = n;
}

UniquePtr::~UniquePtr(){
    delete []point;
    size = 0;
}

UniquePtr
UniquePtr::make(int n){
    UniquePtr x(n);
    return x;
}

char&
UniquePtr::get(int n){
    return point[n];
}

const char&
UniquePtr::get(int n) const{
    return point[n];
}
