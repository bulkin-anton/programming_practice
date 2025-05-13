#include <exception>
#include <iostream>
#include <string>

/*
 * В PROTECTED!!! :
 *
 * MultySet<Component *> set;
 * virtual const std::string& name() const = 0;
 *
*/

template <typename T>
class MultySet{
    public:
        MultySet();
        MultySet(const MultySet<T> &x, int new_cap = -1);
        ~MultySet();
        MultySet<T>& operator = (MultySet<T>);
        T& operator [] (int);
        const T& operator [] (int) const;
        void clear();
        int size() const;
        void add(const T&);
        void del(int, T&);
    private:
        void swap(MultySet<T> &);
        T *arr;
        int cap;
        int len;
};

template <typename T>
MultySet<T>::MultySet(){
    arr = new T[1];
    cap = 1;
    len = 0;
}

template <typename T>
MultySet<T>::~MultySet(){
    delete []arr;
}

template <typename T>
MultySet<T>::MultySet(const MultySet<T> &x, int new_cap){
    if (x.cap < new_cap){
        cap = new_cap;
    } else{
        cap = x.cap;
    }
    arr = new T[cap];
    len = x.len;
    try{
        for (int i = 0; i < len; ++i){
            arr[i] = x.arr[i];
        }
    }
    catch(...){
        delete []arr;
        throw;
    }
}

template <typename T>
MultySet<T>&
MultySet<T>::operator = (MultySet<T> x){
    swap(x);
    return *this;
}

template <typename T>
T&
MultySet<T>::operator [] (int i){
    if ((i >= len) || (i < 0)){
        throw std::exception();
    }
    return *(arr + i);
}

template <typename T>
const T&
MultySet<T>::operator [] (int i) const{
    if ((i >= len) || (i < 0)){
        throw std::exception();
    }
    return arr[i];
}

template <typename T>
void
MultySet<T>::clear(){
    len = 0;
}

template <typename T>
int
MultySet<T>::size() const{
    return len;
}

template <typename T>
void
MultySet<T>::add(const T &x){
    if (cap == len){
        MultySet<T> copy(*this, cap * 2);
        copy.arr[len] = x;
        ++copy.len;
        *this = copy;
    } else{
        arr[len] = x;
        ++len;
    }
}

template <typename T>
void
MultySet<T>::del(int i, T &x){
    T el = (*this)[i];
    MultySet<T> tmp(*this);
    tmp[i] = tmp[tmp.len - 1];
    x = el;
    --tmp.len;
    *this = tmp;
}

template <typename T>
void
MultySet<T>::swap(MultySet<T> &x){
    T *tmp = x.arr;
    x.arr = arr;
    arr = tmp;
    cap = x.cap;
    len = x.len;
}

class Component{
    public:
        Component();
        Component(const Component&) = delete;
        Component& operator = (const Component&) = delete;
        virtual ~Component();
        int count() const;
        Component& subcomponent(int);
        const Component& subcomponent(int) const;
        void add(Component &);
        friend std::ostream& operator << (std::ostream&, const Component &);
    protected:
        MultySet<Component *> set;
        virtual const std::string& name() const = 0;
};

Component::Component(): set() {}

Component::~Component() {}

int
Component::count() const{
    return set.size();
}

const Component&
Component::subcomponent(int i) const{
    return *set[i];
}

Component&
Component::subcomponent(int i){
    return *set[i];
}

void
Component::add(Component &x){
    set.add(&x);
}

std::ostream&
operator << (std::ostream &stream, const Component &x){
    stream << x.name() << '(';
    for (int i = 0; i < x.count(); ++i){
        stream << *x.set[i];
        if (i != (x.count() - 1)){
            stream << ", ";
        }
    }
    stream << ')';
    return stream;
}

class Box: public Component{
    public:
        Box(const std::string &);
        Box(const Box&);
        Box& operator = (const Box&);
        ~Box();
    private:
        std::string str;
        std::string n;
        const std::string& name() const;
};

Box::Box(const std::string &x): Component(), str(x), n("qwerty") {}

Box::Box(const Box &x): Component(), str(x.str), n("qwerty") {}

Box::~Box() {}

Box&
Box::operator = (const Box &x){
    if (this != &x){
        Box tmp = *this;
        tmp.set.clear();
        tmp.str = x.str;
        tmp.n = "qwerty";
        *this = tmp;
    }
    return *this;
}

const std::string&
Box::name() const{
    return n;
}
