#include <iostream>
#include <string>
#include <sstream>

/*
S -> <cnt = 0> A <cnt ?= 0>
A -> a <cnt++> A | b <cnt -= 2> A | eps
*/

class Parser{
    public:
        bool parse(std::istream &);
    private:
        void gc();
        void S();
        void A();
        std::istream *stream;
        int c;
        int cnt = 0;
};

bool
Parser::parse(std::istream &strm){
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

// S -> <cnt = 0> A <cnt ?= 0>

void
Parser::S(){
    /*<*/
    cnt = 0;
    /*>*/
    A();
    /*<*/
    if (cnt != 0){
        throw std::exception();
    }
    /*>*/
}

// A -> a <cnt++> A | b <cnt -= 2> A | eps

void
Parser::A(){
    if (c == 'a'){
        /*<*/
        ++cnt;
        /*>*/
        gc();
        A();
    } else if (c == 'b'){
        /*<*/
        cnt -= 2;
        /*>*/
        gc();
        A();
    } else if (c != EOF){
        throw std::exception();
    }
}


int
main(){
    Parser prsr;
    std::string str;
    std::cout << 2 << std::endl;
    while(getline(std::cin, str)){
        std::stringstream stream;
        stream.str(str);
        if (prsr.parse(stream)){
            std::cout << "YES" << std::endl;
        } else{
            std::cout << "NO" << std::endl;
        }
    }
}
