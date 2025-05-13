#include <typeinfo>

template <typename T>
class Iterator{
    public:
        Iterator(T*, int);
        T& operator * ();
        Iterator & operator ++ ();
        Iterator & operator ++ (int);
        bool operator != (const Iterator &) const;
        bool operator == (const Iterator &) const;
    private:
        T* ptr;
        int pos;
};

template <typename T>
Iterator<T>::Iterator(T *x, int i): ptr(x), pos(i) {}

template <typename T>
T&
Iterator<T>::operator * (){
    return *(ptr + pos);
}

template <typename T>
Iterator<T>&
Iterator<T>::operator ++ (){
    ++pos;
    return *this;
}

template <typename T>
Iterator<T>&
Iterator<T>::operator ++ (int){
    Iterator<T> tmp = *this;
    ++pos;
    return tmp;
}

template <typename T>
bool
Iterator<T>::operator == (const Iterator &x) const{
    return ((ptr == x.ptr) && (pos == x.pos));
}

template <typename T>
bool
Iterator<T>::operator != (const Iterator &x) const{
    return (!((ptr == x.ptr) && (pos == x.pos)));
}


template <typename T>
class Vector{
    public:
        Vector();
        Vector(const Vector &);
        ~Vector();
        Vector& operator = (const Vector &);
        Iterator<T> begin() const;
        Iterator<T> end() const;
        void increase();
        T& operator [] (int);
        const T& operator [] (int) const;
    private:
        T *arr;
        int len;
};

template <typename T>
Vector<T>::Vector(): arr(nullptr), len(0) {}

template <typename T>
Vector<T>::Vector(const Vector &x){
    if (x.len){
        arr = new T[x.len];
        for (int i = 0; i < x.len; ++i){
            arr[i] = x.arr[i];
        }
    } else{
        arr = nullptr;
    }
    len = x.len;
};

template <typename T>
Vector<T>::~Vector(){
    delete [] arr;
}

template <typename T>
Vector<T>&
Vector<T>::operator = (const Vector &x){
    if (this == &x){
        return *this;
    }
    T* new_arr = nullptr;
    if (x.len){
        new_arr = new T[x.len];
        for (int i = 0; i < x.len; ++i){
            new_arr[i] = x.arr[i];
        }
    }
    len = x.len;
    delete []arr;
    arr = new_arr;
    return *this;
}

template <typename T>
Iterator<T>
Vector<T>::begin() const{
    return Iterator<T>(arr, 0);
}

template <typename T>
Iterator<T>
Vector<T>::end() const{
    return Iterator<T>(arr, len);
}

template <typename T>
T&
Vector<T>::operator [] (int i){
    return *(arr + i);
}


template <typename T>
const T&
Vector<T>::operator [] (int i) const{
    return *(arr + i);
}

template <typename T>
void
Vector<T>::increase (){
    T *new_arr = new T[len + 1];
    for (int i = 0; i < len; ++i){
        new_arr[i] = arr[i];
    }
    ++len;
    delete []arr;
    arr = new_arr;
}

template <typename T>
T
f(T x, T y){
    if (x.begin() != y.begin()) {
        throw std::exception();
    }
    return x;
}

/*
passes tests of:

#include <iostream>
int
main() {
    Vector<std::string> a;
    a.increase();
    a.increase();
    a.increase();
    a[0] = "11"; a[1] = "222"; a[2] = "vmk";
    Vector<int> b1;
    b1.increase();
    b1.increase();
    b1.increase();
    b1[0] = 3; b1[1] = 2;
    Vector<std::string> b(a);
    Vector<std::string> c = b;
    c = b;
    for (Iterator<std::string> it1 = c.begin(); it1 != c.end(); ++it1) {
        std::cout << *it1 << std::endl;
    }
    try {
        f(a, b);
    }
    catch(...) {
        std::cout << "NO" << std::endl;
        return 0;
    }
    std::cout << "YES" << std::endl;
    return 0;
}
*/
