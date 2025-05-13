#include <iostream>
#include <exception>
#include <sstream>

/*
<выражение> ::= <логическое-выражение> | <арифметическое-выражение>
<логическое-выражение> ::= <дизъюнкция>
<дизъюнкция> ::= <конъюнкция> | <дизъюнкция> '|' <дизъюнкция>
<конъюнкция> ::= <логический-операнд> | <конъюнкция> '&' <конъюнкция>
<логический-операнд> ::= 'T' | 'F' | '(' <логическое-выражение> ')' | <сравнение>
<сравнение> ::= <арифметическое-выражение> ('<' | '>' | '=') <арифметическое-выражение>
<арифметическое-выражение> ::= <сумма>
<сумма> ::= <произведение> | <сумма> '+' <сумма>
<произведение> ::= <арифметический-операнд> | <произведение> '*' <произведение>
<арифметический-операнд> ::= '0' | '1'| '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9' | '(' <арифметическое-выражение> ')'

E -> LE | AE
LE -> D
D -> Con | D'|'D
Con -> Lop | Con&Con
Lop -> true | false | (LE) | Comp
Comp -> AE < AE | AE > AE | AE = AE
AE -> Summ
Summ -> Mult | Summ + Summ
Mult -> Aop | Mult*Mult
Aop -> 0 .. 9 | (AE)

E -> D {|D}
D -> Con {&Con}
Con -> true | false | (E) | S [(<,>,=)S]
S -> P {+P}
P -> Aop {*Aop}
Aop -> 0 | 1 | ... | 9 | (D)

Equivalent for PC:
E -> AB
B -> '|'E | eps
A -> CD
D -> '&'A | eps
C -> PR | t | f
R -> '<'P | '>'P | '='P | eps
P -> SF
F -> '+'P | eps
S -> MG
G -> '*'S | eps
M -> 0 | 1 | ... | 9 | '('E')'

For programm:
*phase = LOGIC <=> phase = true*
*phase = ARITHMETIC <=> phase = false*
D -> C {'|' <phase ?= LOGIC> C <phase ?= LOGIC>}
C -> L { '&' <phase ?= LOGIC> L <phase ?= LOGIC> }
L -> 'T' <phase = LOGIC> | 'F' <phase = LOGIC> |
      S {('<' | '>' | '=') <phase ?= ARITHMETIC> S <phase = LOGIC>}
S -> P {'+' <phase ?= ARITHMETIC> P <phase ?= ARITHMETIC>}
P -> O {'*' <phase ?= ARITHMETIC> O <phase ?= ARITHMETIC>}
O -> ('1' | '2' | ... | '9') <phase = ARITHMETIC> | '('D')'
*/

class Parser{
    public:
        bool parse(std::istream &);
    private:
        void gc();
        void D();
        void C();
        void L();
        void S();
        void P();
        void O();
        std::istream *stream;
        int c;
        bool phase;
};

bool
Parser::parse(std::istream &strm){
    stream = &strm;
    try{
        gc();
        D();
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

// D -> C {'|' <phase ?= LOGIC> C <phase ?= LOGIC>}

void
Parser::D(){
    C();
    while (c == '|'){
        /*<*/
        if (!phase){
            throw std::exception();
        }
        /*>*/
        gc();
        C();
        /*<*/
        if (!phase){
            throw std::exception();
        }
        /*>*/
    }
}

// C -> L { '&' <phase ?= LOGIC> L <phase ?= LOGIC> }

void
Parser::C(){
    L();
    while (c == '&'){
        /*<*/
        if (!phase){
            throw std::exception();
        }
        /*>*/
        gc();
        L();
        /*<*/
        if (!phase){
            throw std::exception();
        }
        /*>*/
    }
}

/*
L -> 'T' <phase = LOGIC> | 'F' <phase = LOGIC> |
      S {('<' | '>' | '=') <phase ?= ARITHMETIC> S <phase = LOGIC>}
*/

void
Parser::L(){
    if ((c == 'T') || (c == 'F')){
        /*<*/
        phase = true;
        /*>*/
        gc();
    } else{
        S();
        if ((c == '<') || (c == '>') || (c == '=')){
            /*<*/
            if (phase){
                throw std::exception();
            }
            /*>*/
            gc();
            S();
            /*<*/
            phase = true;
            /*>*/
        }
    }
}

//S -> P {'+' <phase ?= ARITHMETIC> P <phase ?= ARITHMETIC>}

void
Parser::S(){
    P();
    while (c == '+'){
        /*<*/
        if (phase){
            throw std::exception();
        }
        /*>*/
        gc();
        P();
        /*<*/
        if (phase){
            throw std::exception();
        }
        /*>*/
    }
}

//P -> O {'*' <phase ?= ARITHMETIC> O <phase ?= ARITHMETIC>}

void
Parser::P(){
    O();
    while (c == '*'){
        /*<*/
        if (phase){
            throw std::exception();
        }
        /*>*/
        gc();
        O();
        /*<*/
        if (phase){
            throw std::exception();
        }
        /*>*/
    }
}

//O -> ('1' | '2' | ... | '9') <phase = ARITHMETIC> | '('D')'

void
Parser::O(){
    if ((c >= '0') && (c <= '9')){
        /*<*/
        phase = false;
        /*>*/
        gc();
    } else if (c == '('){
        gc();
        D();
        /*<*/
        if (c != ')'){
            throw std::exception();
        }
        /*>*/
        gc();
    } else{
        throw std::exception();
    }
}

int
main(){
    Parser prsr;
    std::string str;
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
