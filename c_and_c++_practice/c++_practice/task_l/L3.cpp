#include <iostream>
#include <exception>
#include <sstream>

/*
S → bS | aAB
A → bcA | ccA | ε
B → cbB | ε

All steps of criteria algorithm for PC are achievable
except for one (3):
follow(A) = {c}
                   => intersection is not empty = {c}
first(A) = {c, b}

Language = {b^n a (bc|cc)^k (cb)^l; n,k,l >= 0}

New grammar:
S -> bS | aF
F -> bcF | cE | ε
E -> cF | bD
D -> cbD | ε
*/

class Parser{
    public:
        bool process(std::istream &);
    private:
        void gc();
        void S();
        void F();
        void E();
        void D();
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

// S -> bS | aF

void
Parser::S(){
    if (c == 'b'){
        gc();
        S();
    } else if (c == 'a'){
        gc();
        F();
    } else{
        throw std::exception();
    }
}

// F -> bcF | cE | ε

void
Parser::F(){
    if (c == 'b'){
        gc();
        if (c == 'c'){
            gc();
            F();
        }
        else{
            throw std::exception();
        }
    } else if (c == 'c'){
        gc();
        E();
    }
}

// E -> cF | bD

void
Parser::E(){
    if (c == 'c'){
        gc();
        F();
    } else if (c =='b'){
        gc();
        D();
    } else{
        throw std::exception();
    }
}

// D -> cbD | ε

void
Parser::D(){
    if (c == 'c'){
        gc();
        if (c == 'b'){
            gc();
            D();
        }
        else{
            throw std::exception();
        }
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
