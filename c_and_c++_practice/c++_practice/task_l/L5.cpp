#include <iostream>
#include <exception>

/*
Terminals of grammar:
OPEN, CLOSE, STAR, PLUS, BAR, DIGIT, TERM_SYMBOL
  a     b      c     d    e     f        g

Grammar from task:

S -> A | AeS
A -> C | CA | ε
C -> E | Cc | Cd
E -> f | g | aSb

Equavalent grammar:

S -> AF
F -> eS | ε
A -> fBA | gBA | aSbBA | ε
B -> cB | dB | ε
*/

class RegexParser{
    public:
        RegexParser();
        void parse(std::istream &);
    private:
        void gc(std::istream&);
        void S();
        void A();
        void B();
        void F();
        Token c;
};

RegexParser::RegexParser(): c() {}

void
RegexParser::parse(std::istream &stream){
    gc(stream);
    S();
    if (c.kind != Token::END) {
        throw std::exception();
    }
}

void
RegexParser::gc(std::istream &stream = std::cin){
    static TokenStreamIterator iterator(stream);
    c = *iterator;
    ++iterator;
}

// S -> AF

void
RegexParser::S(){
    A();
    F();
}

// A -> fBA | gBA | aSbBA | ε

void
RegexParser::A(){
    if ((c.kind == Token::DIGIT) || (c.kind == Token::CHAR)){
        gc();
        B();
        A();
    } else if (c.kind == Token::OPEN){
        gc();
        S();
        if (c.kind != Token::CLOSE){
            throw std::exception();
        }
        gc();
        B();
        A();
    }
}

// B -> cB | dB | ε

void
RegexParser::B(){
    if ((c.kind == Token::STAR) || (c.kind == Token::PLUS)){
        gc();
        B();
    }
}

// F -> eS | ε

void
RegexParser::F(){
    if (c.kind == Token::BAR){
        gc();
        S();
    }
}

int
main(){
    RegexParser prsr;
    try {
        prsr.parse(std::cin);
    }
    catch(...) {
        std::cout << "NO" << std::endl;
        return 0;
    }
    std::cout << "YES" << std::endl;
    return 0;
}
