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

class StackInterpreter{
    public:
        StackInterpreter(size_t);
        StackInterpreter(const StackInterpreter&);
        StackInterpreter& operator = (StackInterpreter);
        size_t size() const;
        void swap(StackInterpreter&);
        void save_back(Data *);
        virtual ~StackInterpreter();
        virtual void push(const Data&);
        virtual Data *pop();
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
        size_t capacity;
        size_t len;
        Element *arr;
};

StackInterpreter::Element::Element(){
    el = nullptr;
}

StackInterpreter::Element::Element(const Data *x){
    el = x -> clone();
}

StackInterpreter::Element::~Element(){
    delete el;
}

StackInterpreter::Element::Element(const StackInterpreter::Element &x){
    el = x.el -> clone();
}

StackInterpreter::Element&
StackInterpreter::Element::operator = (StackInterpreter::Element x){
    swap(x);
    return *this;
}

void
StackInterpreter::Element::swap(StackInterpreter::Element &x){
    Data *tmp = x.el;
    x.el = el;
    el = tmp;
}

StackInterpreter::StackInterpreter(size_t x){
    arr = new Element[x];
    capacity = x;
    len = 0;
}

StackInterpreter::StackInterpreter(const StackInterpreter &x){
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

StackInterpreter::~StackInterpreter(){
    delete []arr;
}

StackInterpreter&
StackInterpreter::operator = (StackInterpreter x){
    swap(x);
    return *this;
}

void
StackInterpreter::swap(StackInterpreter &x){
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
StackInterpreter::size() const{
    return len;
}

void
StackInterpreter::push(const Data &x){
    if (len >= capacity){
        throw std::exception();
    }
    arr[len] = &x;
    len++;
}

Data*
StackInterpreter::pop(){
    if (len == 0){
        throw std::exception();
    }
    Data *tmp;
    tmp = arr[--len].el;
    arr[len].el = nullptr;
    return tmp;
}

void
StackInterpreter::save_back(Data *x){
    arr[len++] = x;
}

class Instruction{
    public:
        virtual void run(StackInterpreter&) const = 0;
        virtual ~Instruction();
};

Instruction::~Instruction() {}

Number*
pop_and_get_number(StackInterpreter &x){
    Data *pos = x.pop();
    Number *ans = dynamic_cast<Number *>(pos);
    if (ans == 0){
        x.save_back(pos);
        throw std::exception();
    } else {
        return ans;
    }
}

class AddInstruction: public Instruction{
    public:
        void run(StackInterpreter&) const;
};

void
AddInstruction::run(StackInterpreter &x) const{
    Number *num1 = nullptr, *num2 = nullptr;
    try{
        num1 = pop_and_get_number(x);
        num2 = pop_and_get_number(x);
        x.push(Number(num1 -> value() + num2 -> value()));
    }
    catch(...){
        if (num1) x.save_back(num1);
        if (num2) x.save_back(num2);
        throw;
    }
    delete num1;
    delete num2;
}
