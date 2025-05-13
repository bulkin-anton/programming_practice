#include <iostream>
#include <new>
class DynArray{
    public:
        DynArray(size_t el_size);
        ~DynArray();
        char *append();
        char *get_pos() const;
        int size() const;
        void del_arr();
        DynArray& operator = (const DynArray &x);
        DynArray(const DynArray&);
    private:
        char *arr;
        int len;
        int capacity;
        size_t _size;
};

DynArray::DynArray(size_t el_size){
    _size = el_size;
    capacity = 0;
    len = 0;
    arr = nullptr;
}

DynArray::~DynArray(){
    _size = 0;
    len = 0;
    capacity = 0;
    delete []arr;
}

DynArray::DynArray(const DynArray &x){
    _size = x._size;
    capacity = x.capacity;
    len = x.len;
    arr = new char[capacity];
    for (int i = 0; i < len; i++){
        arr[i] = x.arr[i];
    }
}

DynArray&
DynArray::operator = (const DynArray &x){
    if (this == &x){
        return *this;
    }
    delete []arr;
    arr = new char[x.capacity];
    len = x.len;
    capacity = x.capacity;
    _size = x._size;
    for (int i = 0; i < len; i++){
        arr[i] = x.arr[i];
    }
    return *this;
}

void
DynArray::del_arr(){
    delete []arr;
    arr = nullptr;
    capacity = 0;
    len = 0;
}

char*
DynArray::append(){
    if (len == capacity){
        if (capacity){
            capacity *= 2;
        } else{
            capacity = 128;
        }
        char *new_arr = new char[capacity];
        for (int i = 0; i < len; i++){
            new_arr[i] = arr[i];
        }
        delete []arr;
        arr = new_arr;
    }
    len += _size;
    return &arr[len - _size];
}

int
DynArray::size() const{
    return len/_size;
}

char*
DynArray::get_pos() const{
    return arr;
}

template <typename T>
class Vector: private DynArray{
    public:
        using DynArray::size;
        Vector();
        Vector(const Vector&);
        ~Vector();
        Vector& operator = (const Vector&);
        const T& operator [] (int) const;
        T& operator [] (int);
        void insert(const T&);
};

template <typename T>
Vector<T>::Vector(): DynArray(sizeof(T)) {}

template <typename T>
T&
Vector<T>::operator [] (int i){
    if ((i < 0) || (i >= size())){
        exit(1);
    } else{
        return *(reinterpret_cast<T *> (get_pos() + i * sizeof(T)));
    }
}

template <typename T>
const T&
Vector<T>::operator [] (int i) const{
    if ((i < 0) || (i >= size())){
        exit(1);
    } else{
        return *(reinterpret_cast<T *> (get_pos() + i * sizeof(T)));
    }
}

template <typename T>
void
Vector<T>::insert(const T &n){
    new (reinterpret_cast<T *> (append())) T(n);
}

template <typename T>
Vector<T>::~Vector(){
    int arr_len = size();
    for (int i = 0; i < arr_len; i++){
        (*reinterpret_cast<T *> (get_pos() + i * sizeof(T))).~T();
    }
}

template <typename T>
Vector<T>::Vector(const Vector &x): DynArray(sizeof(T)){
    int arr_len = x.size();
    for (int i = 0; i < arr_len; i++){
        insert(x[i]);
    }
}

template <typename T>
Vector<T>&
Vector<T>::operator = (const Vector<T> &x){
    if (this == &x){
        return *this;
    }
    int arr_len = size();
    for (int i = 0; i < arr_len; i++){
        (*reinterpret_cast<T *> (get_pos() + i * sizeof(T))).~T();
    }
    arr_len = x.size();
    del_arr();
    for (int i = 0; i < arr_len; i++){
        insert(x[i]);
    }
    return *this;
}
