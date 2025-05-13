#include <iostream>

class A{
    public:
        A();
        int get_color() const;
        void set_color(int);
        friend std::ostream& operator << (std::ostream&, const A&);
        ~A();
    private:
        int color;
};

class UniquePtr{
    public:
        UniquePtr();
        UniquePtr(UniquePtr&);
        UniquePtr(A*);
        UniquePtr& operator = (UniquePtr&);
        A& operator * ();
        A* operator -> ();
        const A& operator * () const;
        const A* operator -> () const;
        ~UniquePtr();
    private:
        A *ptr;
};

A::A(){
    color = 0;
}

A::~A(){
    color = 0;
}

int
A::get_color() const{
    return color;
}

void
A::set_color(int n){
    color = n;
}

UniquePtr::UniquePtr(){
    ptr = nullptr;
}

UniquePtr::UniquePtr(UniquePtr& x){
    ptr = x.ptr;
    x.ptr = nullptr;
}

UniquePtr::~UniquePtr(){
    delete ptr;
}

UniquePtr::UniquePtr(A *x){
    ptr = x;
}

UniquePtr&
UniquePtr::operator = (UniquePtr &x){
    if (ptr != x.ptr){
        delete ptr;
        ptr = x.ptr;
        x.ptr = nullptr;
    }
    return *this;
}

A*
UniquePtr::operator -> (){
    return ptr;
}

A&
UniquePtr::operator * (){
    return *ptr;
}

const A*
UniquePtr::operator -> () const{
    return ptr;
}

const A&
UniquePtr::operator * () const{
    return *ptr;
}

std::ostream& operator << (std::ostream &out, const A &x) {
    out << "color = " << x.get_color();
    return out;
}
