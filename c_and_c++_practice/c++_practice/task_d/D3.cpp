#include <iostream>

namespace containers{
    class DynArray{
        public:
            class Iterator{
                public:
                    Iterator(int*, int);
                    bool operator != (const Iterator&) const;
                    Iterator& operator ++ ();
                    int operator * () const;
                private:
                    int *pntr;
                    int i;
            };
            DynArray();
            DynArray(const DynArray&);
            DynArray& operator = (const DynArray&);
            int& operator [] (int);
            const int& operator [] (int) const;
            int size () const;
            Iterator begin_iterator() const;
            Iterator end_iterator () const;
            ~DynArray();
        private:
            void increase ();
            int *arr;
            int len;
            int capacity;
    };

    DynArray::Iterator::Iterator(int *t, int k){
        pntr = t;
        i = k;
    }

    bool
    DynArray::Iterator::operator != (const Iterator &t) const{
        if (i != t.i){
            return 1;
        }
        return 0;
    }

    DynArray::Iterator&
    DynArray::Iterator::operator ++ (){
        ++i;
        return *this;
    }

    int
    DynArray::Iterator::operator * () const{
        return pntr[i];
    }

    DynArray::Iterator
    DynArray::end_iterator () const{
        return Iterator(arr, len);
    }

    DynArray::Iterator
    DynArray::begin_iterator() const{
        return Iterator(arr, 0);
    }

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
        i = x.size();
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

namespace algorithms
{
    iterators::InserterIterator
    copy(
        iterators::InputIterator iterator,
        iterators::InputIterator end,
        iterators::InserterIterator begin2)
    {
        iterators::InserterIterator iterator2 = begin2;
        while (iterator != end) {
            *iterator2++ = *iterator++;
        }
        return iterator2;
    }

    class IsEven{
        public:
            IsEven(bool);
            bool operator () (int) const;
        private:
            bool state;
    };

    IsEven::IsEven(bool x): state(x) {}

    bool
    IsEven::operator () (int x) const{
        if ((x % 2) == !(state)){
            return 1;
        }
        return 0;
    }

    class AddTo{
        public:
            AddTo(int&);
            void operator () (int);
        private:
            int *x;
    };

    AddTo::AddTo(int &t){
        x = &t;
    }

    void
    AddTo::operator () (int s){
        *x += s;
    }
}
