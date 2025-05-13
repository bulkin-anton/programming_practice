#include <iostream>
#include <exception>
#include <string>

class Data{
    public:
        virtual Data* clone() const = 0;
        virtual ~Data();
};

Data::~Data() {}

class Text: public Data{
    public:
        Text(std::string);
        Data* clone() const;
        std::string value () const;
    private:
        std::string str;
};

Text::Text(std::string a): str(a) {}

Data*
Text::clone() const{
    return new Text(str);
}

std::string
Text::value() const{
    return str;
}

class Number: public Data{
    public:
        Number(int);
        Data* clone() const;
        int value () const;
    private:
        int num;
};

Number::Number(int a): num(a) {}

Data*
Number::clone() const{
    return new Number(num);
}

int
Number::value() const{
    return num;
}

class BoundedStack{
    public:
        BoundedStack(size_t);
        BoundedStack(const BoundedStack&);
        BoundedStack& operator = (BoundedStack);
        ~BoundedStack();
        size_t size() const;
        void push(const Data&);
        Data *pop();
    private:
        struct Element{
            Element();
            Element(const Data *);
            void swap(Element&);
            ~Element();
            Element(const Element&);
            Element& operator = (Element);
            Data *el;
        };
        void swap(BoundedStack&);
        size_t capacity;
        size_t len;
        Element *arr;
};

BoundedStack::Element::Element(){
    el = nullptr;
}

BoundedStack::Element::Element(const Data *x){
    el = x -> clone();
}

BoundedStack::Element::~Element(){
    delete el;
}

BoundedStack::Element::Element(const BoundedStack::Element &x){
    el = x.el -> clone();
}

BoundedStack::Element&
BoundedStack::Element::operator = (BoundedStack::Element x){
    swap(x);
    return *this;
}

void
BoundedStack::Element::swap(BoundedStack::Element &x){
    Data *tmp = x.el;
    x.el = el;
    el = tmp;
}

BoundedStack::BoundedStack(size_t x){
    arr = new Element[x];
    capacity = x;
    len = 0;
}

BoundedStack::BoundedStack(const BoundedStack &x){
    arr = new Element[x.capacity];
    for (size_t i = 0; i < x.len; i++){
        try{
            arr[i] = x.arr[i];
        }
        catch(...){
            delete []arr;
            throw;
        }
    }
    capacity = x.capacity;
    len = x.len;
}

BoundedStack::~BoundedStack(){
    delete []arr;
}

BoundedStack&
BoundedStack::operator = (BoundedStack x){
    swap(x);
    return *this;
}

void
BoundedStack::swap(BoundedStack &x){
    Element *tmp = x.arr;
    x.arr = arr;
    arr = tmp;
    size_t t = x.capacity;
    x.capacity = capacity;
    capacity = t;
    t = x.len;
    x.len = len;
    len = t;
}

size_t
BoundedStack::size() const{
    return len;
}

void
BoundedStack::push(const Data &x){
    if (len >= capacity){
        throw std::exception();
    }
    arr[len] = &x;
    len++;
}

Data*
BoundedStack::pop(){
    if (len == 0){
        throw std::exception();
    }
    Data *tmp;
    tmp = arr[--len].el;
    arr[len].el = nullptr;
    return tmp;
}
