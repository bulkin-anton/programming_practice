#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <stack>
#include <vector>
#include <set>
/*
T -> N
N -> L | NL
L -> Name ()
NL -> Name ( ST )
ST -> T | ST , T
Name -> a | b | c | ... | A | B | C | ... | Z

S -> N (B)
B -> S,B | S | eps
N -> ...

S -> A <end poliz>
A -> <insert c in poliz> D '(' B <insert '&' in poliz> ')'
B -> eps | C
C -> A { ',' A }
D -> literal
*/

class Component;

class Parser{
    public:
        bool parse(std::istream &, const std::map<char, Component *> &);
        std::vector<char>& get_poliz();
    private:
        void gc();
        void S();
        void A();
        void B();
        void C();
        void D();
        std::istream *stream;
        int c;
        std::vector<char> poliz;
};

std::vector<char>&
Parser::get_poliz(){
    return poliz;
}

bool
Parser::parse(std::istream &strm, const std::map<char, Component *> &comp){
    stream = &strm;
    components = &comp;
    try{
        gc();
        S();
    }
    catch(...){
        return false;
    }
    if (stream -> eof()){
        return true;
    }
    return false;
}

void
Parser::gc(){
    c = stream -> get();
}

// S -> A <end poliz>

void
Parser::S(){
    A();
    poliz.erase(--poliz.end());
}

// A -> <insert c in poliz> D '(' B <insert '&' in poliz> ')'

void
Parser::A(){
    /*<*/
    poliz.push_back(c);
    if (nodes.find(c) != nodes.end()){
        throw std::exception();
    }
    if (components -> find(c) == components -> end()){
        throw std::exception();
    }
    nodes.insert(c);
    /*>*/
    D();
    if (c != '('){
        throw std::exception();
    }
    gc();
    B();
    /*<*/
    poliz.push_back('&');
    /*>*/
    if (c != ')'){
        throw std::exception();
    }
    gc();
}

// B -> eps | C

void
Parser::B(){
    if (isalpha(c)){
        C();
    }
}

// C -> A { ',' A }

void
Parser::C(){
    A();
    while (c == ','){
        gc();
        A();
    }
}

// D -> literal

void
Parser::D(){
    if (!isalpha(c)){
        throw std::exception();
    } else{
        gc();
    }
}

Component *
make_from_text(std::string const &text, std::map<char, Component *> const & components) {
    std::stringstream stream;
    Parser prsr;
    stream.str(text);
    if (!(prsr.parse(stream, components))) {
        throw std::exception();
    }
    std::vector<char> poliz = prsr.get_poliz();
    std::stack<char> stack;
    for (std::vector<char>::const_iterator i = poliz.begin(); i != poliz.end(); ++i) {
        if (isalpha(*i)) {
            stack.push(*i);
        } else{
            char l1 = stack.top();
            stack.pop();
            char l2 = stack.top();
            components.at(l2) -> add_subcomponent(components.at(l1));
        }
    }
    return components.at(stack.top());
}
