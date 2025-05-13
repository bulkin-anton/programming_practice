#include <exception>
#include <iostream>
#include <string>
#include <sstream>

/*
 * В полизе - nullptr означает по сути закрытие скобки элемента
 * и добавление этого элемента внутрь предыдущего в стеке:
 * Stack: a b nullptr c nullptr <- top
 * b in a, c in a => a(b(), c())
*/

/*
 * 1) сделать set для имен в std::tring
 * 2) сделать MultySet<Component*> при помощи MultySet<Pair> из make_from_text
 *
 * т.е.:
 *
 * 1) поиск среди MultySet<std::string> names - есть => все плохо
 * 2) поиск среди MultySet<Pair> по name - есть => ок и добавляем Component* из Pair в полиз
 * и добавляем str(лежит имя) в MultySet<std::string>
 *
 * 3) добавляем nullptr в полиз при закрытии скобки ')' в S()
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

/*
class Box: public Component {
public:
    Box(const std::string &);
    Box(const Box &);
    Box & operator = (const Box &);
    ~Box() = default;
private:
    const std::string & name() const;
    std::string name_str;
};

Box::Box(const std::string & x): Component(), name_str(x) {}

Box::Box(const Box & copy): Component(), name_str(copy.name_str) {}

Box &
Box::operator = (const Box & x) {
    if (&x != this) {
        set.clear();
        name_str = x.name_str;
    }
    return *this;
}

const std::string &
Box::name() const {
    return name_str;
}
*/

struct Pair{
    std::string name;
    Component *component;
};

/*
T -> N
N -> LN | NLN
LN -> Name()
NLN -> Name(ST)
ST -> T | ST, T
Name -> not empty sequence of letters and digits starting with letter
_____________________________________________________________________

S -> Name(T)
T -> P | eps
P -> S {, S}
Name -> not empty sequence of letters and digits starting with letter

*/

class Parser{
    public:
        void parse(const std::string &, const MultySet<Pair> &);
        MultySet<Component *> get_poliz() const;
    private:
        void gc();
        void gc2();
        void F();
        void S();
        void P();
        void N();
        void T();
        int c;
        std::stringstream stream;
        const MultySet<Pair> * components;
        MultySet<Component *> poliz;
        MultySet<std::string> names;
};

int
find(const MultySet<std::string> & set, const std::string & key) {
    for (int i = 0; i < set.size(); ++i) {
        if (set[i] == key) {
            return 1;
        }
    }
    return 0;
}

Component *
components_find(const MultySet<Pair> & set, const std::string & key) {
    for (int i = 0; i < set.size(); ++i) {
        if (set[i].name == key) {
            return set[i].component;
        }
    }
    return nullptr;
}

MultySet<Component *>
Parser::get_poliz() const{
    return poliz;
}

void
Parser::gc(){
    c = ' ';
    while (c == ' '){
        c = stream.get();
    }
}

void
Parser::gc2(){
    c = stream.get();
}

void
Parser::parse(const std::string &x, const MultySet<Pair> &cmp){
    components = &cmp;
    stream.str(x);
    gc();
    F();
    if (!(stream.eof())){
        throw std::exception();
    }
}

void
Parser::F(){
    S();
    Component *ptr;
    poliz.del(poliz.size() - 1, ptr);
}

void
Parser::S(){
    N();
    if (c != '('){
        throw std::exception();
    }
    gc();
    T();
    poliz.add(nullptr);
    if (c != ')'){
        throw std::exception();
    }
    gc();
}

void
Parser::T(){
    if (isalpha(c)){
        P();
    }
}

void
Parser::P(){
    S();
    while (c == ','){
        gc();
        S();
    }
}

void
Parser::N(){
    if (!(isalpha(c))){
        throw std::exception();
    } else{
        std::string str;
        str.clear();
        str.push_back(static_cast<char>(c));
        gc2();
        while ((isalpha(c)) || (isdigit(c))){
            str.push_back(static_cast<char>(c));
            gc2();
        }
        if (find(names, str) != 0) {
            throw std::exception();
        }
        if (components_find(*components, str) == nullptr) {
            throw std::exception();
        }
        poliz.add(components_find(*components, str));
        names.add(str);
        if (c == ' '){
            gc();
        }
    }
}

Component*
make_from_text(const std::string &text, const MultySet<Pair> &components){
    Parser parser;
    parser.parse(text, components);
    MultySet<Component *> poliz = parser.get_poliz();
    MultySet<Component *> stack;
    for (auto i = 0; i < poliz.size(); ++i) {
        if (poliz[i] != nullptr) {
            stack.add(poliz[i]);
            continue;
        } else{
            Component * high = stack[stack.size() - 1];
            Component *ptr;
            stack.del(stack.size() - 1, ptr);
            Component * low = stack[stack.size() - 1];
            low->add(*high);
        }
    }
    return stack[stack.size() - 1];
}

int
main() {
    MultySet<Pair> components;
    Box A1("a1"), B1("b1"), C1("c1"),
    D1("d1"), G1("g1"), H1("h1"), L1("l1"), M1("m1");
    components.add({"a1", &A1});
    components.add({"b1", &B1});
    components.add({"c1", &C1});
    components.add({"d1", &D1});
    components.add({"g1", &G1});
    components.add({"h1", &H1});
    components.add({"l1", &L1});
    components.add({"m1", &M1});
    Component * node = nullptr;
    try {
        node = make_from_text("c1      (a1(b1()),d1(g1(),h1(l1(),m1())))",
        components);
    }
    catch (...) {
        std::cout << "NO" << std::endl;
        return 0;
    }
    std::cout << *node << std::endl;
    return 0;
}

