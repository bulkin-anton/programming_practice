#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <set>

/*
<выражение> ::= <последовательность>
<последовательность> ::= <присваивание> | <присваивание> "," <последовательность>
<присваивание> ::= <переменная> "=" <присваивание> | <арифметика>
<арифметика> ::= <операнд> | <вычитание>
<вычитание> ::= <арифметика> "-" <арифметика>
<операнд> ::= <переменная> | <число> | "(" <выражение> ")"
<переменная> ::= буква
<число> ::= цифра

Expression -> Sequence
Sequence -> Assigment | Assigment,Sequence
Assigment -> Variable=Assigment | Arithmetic
Arithmetic -> Operand | Subtraction
Subtraction -> Arithmetic-Arithmetic
Operand -> Variable | Number | (Expression)
Variable -> letter
Number -> digit

Expression ->  Assigment {,Ass}
Assigment ->   Arithmetics <del assign_var members>
               {= <check 1 literal on left> <append assign_var> Arithmetics}
               <check init> <set var-s> <append inited>
Arithmetics -> Operand <start cnt interations> {- <check if not inited first> <save answer>
               Operand <check initialisation> <save and set answer> <iterations += 1>}
               <set 1 left lit if true>
Operand ->     letter <set 1 left lit> <save copy of literal> <check and save if inited> |
               digit <set initialisation> <set that not 1 left lit> <save cur value> |
               (Expr) <set initialisation> <set that not 1 left lit>
*/

class Parser{
    public:
        bool parse(std::istream &);
        int get_answer() const;
    private:
        void gc();
        void expression();
        void assigment();
        void arithmetics();
        void operand();
        void initialise_var();
        void add_initialised();
        std::istream *stream;
        int c;
        int lit_copy;
        int answer;
        bool left_lit;
        bool init;
        std::vector<int> assign_var;
        std::set<int> init_var;
        std::map<int, int> values_var;
};

int
Parser::get_answer() const{
    return answer;
}

void
Parser::initialise_var(){
    for (size_t i = 0; i < assign_var.size(); ++i){
        values_var[assign_var[i]] = answer;
    }
}

void
Parser::add_initialised(){
    for (size_t i = 0; i < assign_var.size(); ++i){
        init_var.insert(assign_var[i]);
    }
}

bool
Parser::parse(std::istream &strm){
    stream = &strm;
    /*<*/
    assign_var.clear();
    init_var.clear();
    values_var.clear();
    /*>*/
    try{
        gc();
        expression();
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

// Expr -> Ass {,Ass}

void
Parser::expression(){
    assigment();
    while (c == ','){
        gc();
        assigment();
    }
}

/*
Ass -> Arithm <del assign_var members>
       {= <check 1 literal on left> <append assign_var> Arithm}
       <check init> <set var-s> <append inited>
*/

void
Parser::assigment(){
    arithmetics();
    /*<*/
    assign_var.clear();
    /*>*/
    while(c == '='){
        /*<*/
        if (!left_lit){
            throw std::exception();
        }
        assign_var.push_back(lit_copy);
        /*>*/
        gc();
        arithmetics();
    }
    /*<*/
    if (!init){
        throw std::exception();
    }
    initialise_var();
    add_initialised();
    /*>*/
}

/*
Arithm -> Operand <start cnt interations> {- <check if not inited first> <save answer>
          Operand <check initialisation> <save and set answer> <iterations += 1>}
          <set 1 left lit if true>
*/

void
Parser::arithmetics(){
    operand();
    /*<*/
    int cnt = 0;
    /*>*/
    while(c == '-'){
        /*<*/
        if ((cnt == 0) && (!init)){
            throw std::exception();
        }
        int prev_ans = answer;
        /*>*/
        gc();
        operand();
        /*<*/
        if (!init){
            throw std::exception();
        }
        answer = prev_ans - answer;
        ++cnt;
        /*>*/
    }
    /*<*/
    if (cnt){
        left_lit = false;
    }
    /*>*/
}

/*
Operand -> letter <set 1 left lit> <save copy of literal> <check and save if inited> |
           digit <set initialisation> <set that not 1 left lit> <save cur value> |
           (Expr) <set initialisation> <set that not 1 left lit>
*/

void
Parser::operand(){
    if (isalpha(c)){
        /*<*/
        left_lit = true;
        lit_copy = c;
        if ((init = (init_var.find(c) != init_var.end()))) {
            answer = values_var[c];
        }
        /*>*/
        gc();
    } else if (isdigit(c)){
        /*<*/
        init = true;
        left_lit = false;
        answer = c - '0';
        /*>*/
        gc();
    } else if (c == '('){
        gc();
        expression();
        if (c != ')'){
            throw std::exception();
        }
        /*<*/
        init = true;
        left_lit = false;
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
            std::cout << prsr.get_answer() << std::endl;
        } else{
            std::cout << "NO" << std::endl;
        }
    }
}
