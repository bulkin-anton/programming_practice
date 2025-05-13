#include <iostream>
#include <string>
#include <sstream>

/*
 * Пробел между лексемами означает наличие пробела/ов
 * между нетерминалами в грамматике и терминалами/нетерминалами
 *
 * НЕ ВНУТРИ ИМЕНИ
*/

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
        void parse(const std::string &);
    private:
        void gc();
        void S();
        void P();
        void N();
        void T();
        int c;
        std::stringstream stream;
};

void
Parser::gc(){
    c = ' ';
    while (c == ' '){
        c = stream.get();
    }
}

void
Parser::parse(const std::string &x){
    stream.str(x);
    gc();
    S();
    if (!(stream.eof())){
        throw std::exception();
    }
}

void
Parser::S(){
    N();
    if (c != '('){
        throw std::exception();
    }
    gc();
    T();
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
        gc2();
        while ((isalpha(c)) || (isdigit(c))){
            gc2();
        }
        if (c == ' '){
            gc();
        }
    }
}
