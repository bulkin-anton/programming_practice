#include <iostream>
#include <sstream>
#include <vector>

/*
ITER_STAR, ITER_PLUS, OR, CONCAT, DIGIT, CHAR, EMPTY

R -> M {'|' M}
M -> eps | C | CM
C -: E | C* | C+
E -> '\d' | 'Tsymb' | (Reg)

R -> M {|M}
M -> eps | C{C}
C -> E {* | +}
E -> '\d' | 'Tsymb' | (R)

R -> M {'|'M <add to poliz OR>}
M -> eps <add to poliz OR> | C {C <add to poliz CONCAT>}
C -> E {* <add to poliz ITER_PLUS>| + <add to poliz ITER_STAR>}
E -> '\d' <add to poliz DIGIT> | 'Tsymb' <add to poliz CHAR> | ( R )
*/

class RegexParser{
    public:
        void parse(std::istream &);
        std::vector<PolizItem>::const_iterator begin() const;
        std::vector<PolizItem>::const_iterator end() const;
    private:
        void gc();
        void R();
        void M();
        void C();
        void E();
        Token c;
        TokenStreamIterator iter;
        std::vector<PolizItem> poliz;
};

std::vector<PolizItem>::const_iterator
RegexParser::begin() const{
    return poliz.begin();
}

std::vector<PolizItem>::const_iterator
RegexParser::end() const{
    return poliz.end();
}

void
RegexParser::parse(std::istream &stream){
    iter = stream;
    /*<*/
    poliz.clear();
    /*>*/
    gc();
    R();
    if (c.kind != Token::END) {
        throw std::exception();
    }
}

void
RegexParser::gc(){
    c = *iter;
    ++iter;
}

// R -> M {'|'M <add to poliz OR>}

void
RegexParser::R(){
    M();
    while (c.kind == Token::BAR){
        gc();
        M();
        /*<*/
        poliz.push_back({PolizItem::OR, 0});
        /*>*/
    }
}

// M -> eps <add to poliz OR> | C {C <add to poliz CONCAT>}

void
RegexParser::M(){
    if ((c.kind == Token::DIGIT) || (c.kind == Token::CHAR) || (c.kind == Token::OPEN)){
        C();
        while((c.kind == Token::DIGIT) || (c.kind == Token::CHAR) || (c.kind == Token::OPEN)){
            C();
            /*<*/
            poliz.push_back({PolizItem::CONCAT, 0});
            /*>*/
        }
    } else{
        /*<*/
        poliz.push_back({PolizItem::EMPTY, 0});
        /*>*/
    }
}

// C -> E {* <add to poliz ITER_PLUS>| + <add to poliz ITER_STAR>}

void
RegexParser::C(){
    E();
    while ((c.kind == Token::STAR) || (c.kind == Token::PLUS)){
        if (c.kind == Token::STAR){
            /*<*/
            poliz.push_back({PolizItem::ITER_STAR, 0});
            /*>*/
        } else{
            /*<*/
            poliz.push_back({PolizItem::ITER_PLUS, 0});
            /*>*/
        }
        gc();
    }
}

// E -> '\d' <add to poliz DIGIT> | 'Tsymb' <add to poliz CHAR> | ( R )

void
RegexParser::E(){
    if (c.kind == Token::DIGIT){
        /*<*/
        poliz.push_back({PolizItem::DIGIT, 0});
        /*>*/
        gc();
    } else if (c.kind == Token::CHAR){
        /*<*/
        poliz.push_back({PolizItem::CHAR, c.repr});
        /*>*/
        gc();
    } else if (c.kind == Token::OPEN){
        gc();
        R();
        if (c.kind != Token::CLOSE){
            throw std::exception();
        }
        gc();
    } else{
        throw std::exception();
    }
}
