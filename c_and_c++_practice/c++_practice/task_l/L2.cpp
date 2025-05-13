#include <iostream>
#include <string>
#include <sstream>

class Parser{
    public:
        bool process(std::istream &);
    private:
        void gc();
        void S();
        void A();
        void B();
        std::istream *stream;
        int c;
};

bool
Parser::process(std::istream &strm){
    stream = &strm;
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

// S → AS | B

void
Parser::S(){
    if ((c == 'b') || (c == 'c')){
        A();
        S();
    } else{
        B();
    }
}

// A → b | c

void
Parser::A(){
    if ((c == 'b') || (c == 'c')){
        gc();
    } else{
        throw std::exception();
    }
}

// B → dBf | a | ε

void
Parser::B(){
    if (c == 'd'){
        gc();
        B();
        if (c != 'f'){
            throw std::exception();
        }
        gc();
    } else if (c =='a'){
        gc();
    }
}

int
main(){
    Parser prsr;
    std::string str;
    while(getline(std::cin, str)){
        std::stringstream stream;
        stream.str(str);
        if (prsr.process(stream)){
            std::cout << "YES" << std::endl;
        } else{
            std::cout << "NO" << std::endl;
        }
    }
}
