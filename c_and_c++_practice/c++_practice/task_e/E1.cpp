#include <iostream>

class Vector{
    public:
        Vector(size_t el_size);
        ~Vector();
        char *append();
        char *get_pos() const;
        int size() const;
        void del_arr();
        Vector& operator = (const Vector &x);
        Vector(const Vector&);
    private:
        char *arr;
        int len;
        int capacity;
        size_t _size;
};

Vector::Vector(size_t el_size){
    _size = el_size;
    capacity = 0;
    len = 0;
    arr = nullptr;
}

Vector::~Vector(){
    _size = 0;
    len = 0;
    capacity = 0;
    delete []arr;
}

Vector::Vector(const Vector &x){
    _size = x._size;
    capacity = x.capacity;
    len = x.len;
    arr = new char[capacity];
    for (int i = 0; i < len; i++){
        arr[i] = x.arr[i];
    }
}

Vector&
Vector::operator = (const Vector &x){
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
Vector::del_arr(){
    delete []arr;
    arr = nullptr;
    capacity = 0;
    len = 0;
}

char*
Vector::append(){
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
Vector::size() const{
    return len/_size;
}

char*
Vector::get_pos() const{
    return arr;
}

class IntVector : private Vector{
    public:
        IntVector();
        int& operator [] (int);
        const int& operator [] (int) const;
        void insert(int);
        using Vector::size;
};

IntVector::IntVector(): Vector(sizeof(int)) {}

int&
IntVector::operator [] (int i){
    if ((i < 0) || (i >= size())){
        exit(1);
    } else{
        return *(reinterpret_cast<int *> (get_pos() + i * sizeof(int)));
    }
}

const int&
IntVector::operator [] (int i) const{
    if ((i < 0) || (i >= size())){
        exit(1);
    } else{
        return *(reinterpret_cast<int *> (get_pos() + i * sizeof(int)));
    }
}

void
IntVector::insert(int n){
    new (reinterpret_cast<int *> (append())) int(n);
}

class DoubleVector : private Vector{
    public:
        DoubleVector();
        double& operator [] (int);
        const double& operator [] (int) const;
        void insert(double);
        using Vector::size;
};

DoubleVector::DoubleVector(): Vector(sizeof(double)) {}

double&
DoubleVector::operator [] (int i){
    if ((i < 0) || (i >= size())){
        exit(1);
    } else{
        return *(reinterpret_cast<double *> (get_pos() + i * sizeof(double)));
    }
}

const double&
DoubleVector::operator [] (int i) const{
    if ((i < 0) || (i >= size())){
        exit(1);
    } else{
        return *(reinterpret_cast<double *> (get_pos() + i * sizeof(double)));
    }
}

void
DoubleVector::insert(double n){
    new (reinterpret_cast<double *> (append())) double(n);
}

class IntVectorVector : private Vector{
    public:
        using Vector::size;
        IntVectorVector();
        IntVector& operator [] (int);
        const IntVector& operator [] (int) const;
        void insert(const IntVector&);
        IntVectorVector(const IntVectorVector&);
        IntVectorVector& operator = (const IntVectorVector&);
        ~IntVectorVector();
};

IntVectorVector::IntVectorVector(): Vector(sizeof(IntVector)) {}

IntVector&
IntVectorVector::operator [] (int i){
    if ((i < 0) || (i >= size())){
        exit(1);
    } else{
        return *(reinterpret_cast<IntVector *> (get_pos() + i * sizeof(IntVector)));
    }
}

const IntVector&
IntVectorVector::operator [] (int i) const{
    if ((i < 0) || (i >= size())){
        exit(1);
    } else{
        return *(reinterpret_cast<IntVector *> (get_pos() + i * sizeof(IntVector)));
    }
}

void
IntVectorVector::insert(const IntVector &n){
    new (reinterpret_cast<IntVector *> (append())) IntVector(n);
}

IntVectorVector::~IntVectorVector(){
    int arr_len = size();
    for (int i = 0; i < arr_len; i++){
        (*reinterpret_cast<IntVector *> (get_pos() + i * sizeof(IntVector))).~IntVector();
    }
}

IntVectorVector::IntVectorVector(const IntVectorVector &x): Vector(sizeof(IntVector)){
    int arr_len = x.size();
    for (int i = 0; i < arr_len; i++){
        insert(x[i]);
    }
}

IntVectorVector&
IntVectorVector::operator = (const IntVectorVector &x){
    if (this == &x){
        return *this;
    }
    int arr_len = size();
    for (int i = 0; i < arr_len; i++){
        (*reinterpret_cast<IntVector *> (get_pos() + i * sizeof(IntVector))).~IntVector();
    }
    arr_len = x.size();
    del_arr();
    for (int i = 0; i < arr_len; i++){
        insert(x[i]);
    }
    return *this;
}
