#include <iostream>
#include <string>
#include <sstream>

/*
S -> a <stream << 2> A <stream << a> | bA <stream << b>
A -> a <stream << 2> A <stream << a> | b <stream << 2> A <stream << b> | eps
*/

class Parser{
    public:
        bool parse(std::istream &, std::ostream &);
    private:
        void gc();
        void S();
        void A();
        std::istream *stream;
        std::ostream *out;
        int c;
};

bool
Parser::parse(std::istream &strm, std::ostream &str2){
    stream = &strm;
    out = &str2;
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

// S -> a <stream << 2> A <stream << a> | bA <stream << b>

void
Parser::S(){
    if (c == 'a'){
        /*<*/
        *out << '2';
        /*>*/
        gc();
        A();
        /*<*/
        *out << 'a';
        /*>*/
    } else if (c == 'b'){
        gc();
        A();
        /*<*/
        *out << 'b';
        /*>*/
    } else{
        throw std::exception();
    }
}

// A -> a <stream << 2> A <stream << a> | bA <stream << b>

void
Parser::A(){
    if (c == 'a'){
        /*<*/
        *out << '2';
        /*>*/
        gc();
        A();
        /*<*/
        *out << 'a';
        /*>*/
    } else if (c == 'b'){
        gc();
        A();
        /*<*/
        *out << 'b';
        /*>*/
    }
}


int
main(){
    Parser prsr;
    std::string str;
    while(getline(std::cin, str)){
        std::stringstream stream;
        std::stringstream output;
        stream.str(str);
        if (prsr.parse(stream, output)){
            std::cout << output.str() << std::endl;
        } else{
            std::cout << "NO" << std::endl;
        }
    }
}
