#include <exception>
#include <iostream>
#include <sstream>
class Parser {
public:
    Parser();
    bool parse(std::istream &);
private:
    std::istream * stream;
    int c;
    void gc();
    void S();
    void A();
    void C();
    void B();
};

Parser::Parser(): stream(nullptr), c(0) {}

bool
Parser::parse(std::istream & x) {
    stream = &x;
    gc();
    try {
        S();
        std::cout << std::endl;
    }
    catch (...) {
        return false;
    }
    if (!stream->eof()) {
        return false;
    }
    return true;
}

void
Parser::gc() {
    c = stream->get();
}

// S ->  BC
// B -> ab<cd>B | eps
// C -> cd<ab>C | eps

void
Parser::S() {
    if (c == 'a'){
        gc();
        A();
    }
}

void
Parser::A() {
    if (c == 'b'){
        gc();
        B();
    } else if (c == 'c'){
        gc();
        C();
    } else{
        throw std::exception();
    }
}

void
Parser::B() {
    if (c == 'a'){
        gc();
        if (c != 'b'){
            throw std::exception();
        }
        std::cout << "cd" ;
        gc();
        B();
    }
}

void
Parser::C() {
    if (c == 'c'){
        gc();
        if (c != 'd'){
            throw std::exception();
        }
        gc();
        std::cout << "ab" ;
        C();
    }
}

int
main() {
    std::string s;
    while (getline(std::cin, s)) {
        std::stringstream new_stream;
        Parser parser;
        new_stream.str(s);
        std::cout << (parser.parse(new_stream) ? "YES"  :  "NO") << std::endl;
    }
    return 0;
}
