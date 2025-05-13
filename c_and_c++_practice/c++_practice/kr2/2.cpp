#include <exception>
template <typename T, int M>
class Stack{
    public:
        Stack();
        ~Stack();
        void pop(T &);
        void push(const T&);
    private:
        T* arr;
        int capacity = M;
        int len;
};

template <typename T, int M>
Stack<T, M>::Stack(){
    arr = new T[M];
    len = 0;
};

// not sure what wht will be with copy constructor and operator =

template <typename T, int M>
Stack<T, M>::~Stack(){
    delete arr;
    //mb usage of destructors for each element
}

template <typename T, int M>
void
Stack<T, M>::pop(T &x){
    if (len == 0){
        throw std::exception();
    }
    x = arr[len - 1];
    --len;
}

template <typename T, int M>
void
Stack<T, M>::push(const T &x){
    if (len == capacity){
        throw std::exception();
    }
    arr[len] = x;
    ++len;
}
