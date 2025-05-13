#include <iostream>

class Person{
    public:
        Person(const char*, int, bool);
        const char* name() const;
        int age() const;
        bool man() const;
    private:
        const char *_name;
        int _age;
        bool _man;
};

Person::Person(const char *str, int years, bool state): _name(str), _age(years), _man(state) {}

const char*
Person::name() const{
    return _name;
}

int
Person::age() const{
    return _age;
}

bool
Person::man() const{
    return _man;
}

class Selection{
    public:
        Selection(Person *, int, int);
        class Iterator{
            public:
                Iterator(const Selection&, int);
                const Person* operator -> () const;
                Iterator& operator ++ ();
                bool operator != (const Iterator&) const;
            private:
                const Selection &cr;
                int i;
                bool found_first;
        };
        Iterator begin () const;
        Iterator end () const;
        bool is_fit(int i) const;
        int get_len() const;
        const Person* get_person(int i) const;
    private:
        int criteria; // 1 - men, 0 - age;
        Person *arr;
        int len;
};

Selection::Iterator::Iterator(const Selection &x, int cnt): cr(x), i(cnt), found_first(false) {}

const Person*
Selection::get_person(int i) const{
    return &arr[i];
}

const Person*
Selection::Iterator::operator -> () const{
    return cr.get_person(i);
}

bool
Selection::Iterator::operator != (const Selection::Iterator &l) const{
    if (i != l.i){
        return 1;
    }
    return 0;
}

bool
Selection::is_fit(int t) const{
    if (criteria){
        return arr[t].man();
    } else{
        return ((arr[t].age() >= 18) && (arr[t].age() <= 35));
    }
}

Selection::Iterator&
Selection::Iterator::operator ++ (){
    if (!(found_first)){
        i--;
        found_first = true;
    }
    i++;
    while (i < cr.get_len()){
        if (cr.is_fit(i)){
            break;
        } else {
            i++;
        }
    }
    return *this;
}

Selection::Selection(Person *a, int l, int cr){
    criteria = cr;
    arr = a;
    len = l;
}

int
Selection::get_len () const{
    return len;
}

Selection::Iterator
Selection::begin() const{
    return Iterator(++Iterator(*this, 0));
}

Selection::Iterator
Selection::end() const{
    if (len){
        return Iterator(*this, len);
    } else return Iterator(*this, 0);
}


class MenPersonView: public Selection{
    public:
        MenPersonView(Person *, int);
};

class YoungPersonView: public Selection{
    public:
        YoungPersonView(Person *, int);
};

YoungPersonView::YoungPersonView(Person *ptr, int length): Selection(ptr, length, 0) {}

MenPersonView::MenPersonView(Person *ptr, int length): Selection(ptr, length, 1) {}

class Persons{
    public:
        Persons();
        ~Persons();
        void add(const Person&);
        MenPersonView men() const;
        YoungPersonView young() const;
    private:
        int len;
        int capacity;
        Person *arr;
};

Persons::Persons(){
    len = 0;
    capacity = 0;
    arr = nullptr;
}

Persons::~Persons(){
    delete []arr;
}

void
Persons::add(const Person &x){
    if (len == capacity){
        if (capacity){
            capacity *= 2;
        } else{
            capacity = 128;
        }
        Person *new_arr = reinterpret_cast<Person*>(new char[capacity*sizeof(Person)]);
        for (int i = 0; i < len; i++){
            new (new_arr + i * sizeof(Person)) Person(arr[i]);
        }
        delete []arr;
        arr = new_arr;
    }
    arr[len++] = x;
}

MenPersonView
Persons::men() const{
    return MenPersonView(arr, len);
}

YoungPersonView
Persons::young() const{
    return YoungPersonView(arr, len);
}

class FastPersons: public Persons{
    public:
        void add(const Person&);
        MenPersonView men() const;
        YoungPersonView young() const;
};
