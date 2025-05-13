#include <iostream>

namespace containers{
    class DynArray{
        public:
            DynArray();
            DynArray(const DynArray&);
            DynArray& operator = (const DynArray&);
            int& operator [] (int);
            const int& operator [] (int) const;
            int size () const;
            ~DynArray();
        private:
            void increase ();
            int *arr;
            int len;
            int capacity;
    };

    DynArray::DynArray(){
        len = 0;
        capacity = 0;
        arr = nullptr;
    }

    DynArray::DynArray(const DynArray &x){
        len = x.len;
        capacity = x.capacity;
        arr = new int[x.capacity];
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
        len = x.len;
        capacity = x.capacity;
        arr = new int[x.capacity];
        for (int i = 0; i < len; i++){
            arr[i] = x.arr[i];
        }
        return *this;
    }

    int&
    DynArray::operator [] (int i){
        increase();
        if ((i + 1) >= len){
            len = i + 1;
        }
        return arr[i];
    }

    const int&
    DynArray::operator [] (int i) const{
        return arr[i];
    }

    int
    DynArray::size() const{
        return len;
    }

    void
    DynArray::increase(){
        if (len >= capacity){
            if (capacity){
                capacity *= 2;
            } else{
                capacity = 128;
            }
            int *new_arr = new int[capacity];
            for (int i = 0; i < len; i++){
                new_arr[i] = arr[i];
            }
            delete []arr;
            arr = new_arr;
        }
    }

    DynArray::~DynArray(){
        len = 0;
        capacity = 0;
        delete []arr;
    }
}

namespace iterators{
    class InserterIterator{
        public:
            InserterIterator(containers::DynArray &x);
            int& operator * ();
            const int& operator * () const;
            InserterIterator operator ++ (int);
        private:
            int i;
            containers::DynArray *arr;
    };

    InserterIterator::InserterIterator(containers::DynArray &x){
        arr = &x;
        i = 0;
    }

    int&
    InserterIterator::operator * (){
        return (*arr)[i];
    }

    const int&
    InserterIterator::operator * () const{
        return (*arr)[i];
    }

    InserterIterator
    InserterIterator::operator ++ (int){
        InserterIterator tmp(*this);
        i++;
        return tmp;
    }

    class InputIterator{
        public:
            InputIterator();
            InputIterator(std::istream&);
            InputIterator(const InputIterator&);
            int operator * () const;
            InputIterator operator ++ (int);
            bool operator != (const InputIterator&) const;
        private:
            std::istream &in;
            int x;
            int err;
    };

    InputIterator::InputIterator(): in(std::cin), x(0), err(1) {}

    InputIterator::InputIterator(std::istream &t): in(t) {
        int num;
        if (in >> num){
            err = 0;
            x = num;
        } else {
            err = 1;
            x = 0;
        }
    }

    InputIterator::InputIterator(const InputIterator &t): in(t.in), x(t.x), err(t.err) {}

    int
    InputIterator::operator * () const{
        return x;
    }

    InputIterator
    InputIterator::operator ++ (int){
        InputIterator tmp(*this);
        int num;
        if (in >> num){
            err = 0;
            x = num;
        } else {
            err = 1;
            x = 0;
        }
        return tmp;
    }

    bool
    InputIterator::operator != (const InputIterator &t) const{
        if (err != t.err){
            return 1;
        }
        return 0;
    }
}
