#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <stack>
#include <vector>
#include <set>
#include <cstdlib>
/*
command ::= seq1
seq1 ::= seq2 { ('&' | ';') (seq2 | ε) }
    + ε is allowed at the end only
seq2 ::= pipeline { ('*' | '+') pipeline }
pipeline ::= redirect { '|' redirect }
redirect ::= simple { ('<' | '>' ) ID }
simple ::= ID { ID } | '(' command ')'

command -> seq1
seq1 -> seq2 { ('&' | ';') (seq2 | ε) }
seq2 -> pipeline { ('*' | '+') pipeline }
pipeline -> redirect { '|' redirect }
redirect -> simple { ('<' | '>' ) ID }
simple -> ID { ID } | '(' command ')'
ID -> lit
*/

class Parser{
    public:
        bool parse(std::istream&, const std::map<char, std::string> &);
        std::vector<char> &get_poliz();
    private:
        void gc();
        void command();
        void seq1();
        void seq2();
        void pipeline();
        void redirect();
        void simple();
        void id();
        std::istream *stream;
        int c;
        std::vector<char> poliz;
        const std::map<char, std::string> *names;

};

std::vector<char>&
Parser::get_poliz(){
    return poliz;
}

bool
Parser::parse(std::istream &strm, const std::map<char, std::string> &x){
    stream = &strm;
    names = &x;
    poliz.clear();
    try{
        gc();
        command();
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

// command -> seq1

void
Parser::command(){
    seq1();
}

// seq1 -> seq2 { ('&' | ';') (seq2 | ε) }

void
Parser::seq1(){
    seq2();
    while ((c == '&') || (c == ';')){
        poliz.push_back(c);
        gc();
        if (!(stream -> eof())){
            seq2();
        }
    }
}

// seq2 -> pipeline { ('*' | '+') pipeline }

void
Parser::seq2(){
    pipeline();
    while ((c == '*') || (c == '+')){
        int op = c;
        gc();
        pipeline();
        poliz.push_back(op);
    }
}

// pipeline -> redirect { '|' redirect }

void
Parser::pipeline(){
    redirect();
    while (c == '|'){
        int op = c;
        gc();
        redirect();
        poliz.push_back(op);
    }
}

// redirect -> simple { ('<' | '>' ) ID }

void
Parser::redirect(){
    simple();
    while ((c == '<') || (c == '>')){
        int op = c;
        gc();
        id();
        poliz.push_back(op);
    }
}

// simple -> ID { ID } | '(' command ')'

void
Parser::simple(){
    if (c == '('){
        poliz.push_back('(');
        gc();
        command();
        if (c != ')'){
            throw std::exception();
        }
        poliz.push_back(')');
        gc();
    } else if (names -> find(c) != names -> end()){
        id();
        while (names -> find(c) != names -> end()){
            id();
        }
    } else{
        throw std::exception();
    }
}

// ID -> lit

void
Parser::id(){
    if (names->find(c) == names->end()) {
        throw std::exception();
    }
    poliz.push_back(c);
    gc();
}

void
interpret(const std::vector<char> &poliz, const std::map<char, std::string> &names){
    std::stack<std::string> stack;
    std::string str, op1, op2;
    std::vector<std::string> arr;
    for (auto i = poliz.begin(); i != poliz.end(); ++i){
        switch(*i){
            case '&':
                op1 = stack.top();
                stack.pop();
                stack.push(op1 + " & ");
                break;
            case ';':
                op1 = stack.top();
                stack.pop();
                stack.push(op1 + " ; ");
                break;
            case '+':
                op2 = stack.top();
                stack.pop();
                op1 = stack.top();
                stack.pop();
                stack.push(op1 + " || " + op2);
                break;
            case '*':
                op2 = stack.top();
                stack.pop();
                op1 = stack.top();
                stack.pop();
                stack.push(op1 + " && " + op2);
                break;
            case '>':
                op2 = stack.top();
                stack.pop();
                op1 = stack.top();
                stack.pop();
                stack.push(op1 + " > " + op2);
                break;
            case '<':
                op2 = stack.top();
                stack.pop();
                op1 = stack.top();
                stack.pop();
                stack.push(op1 + " < " + op2);
                break;
            case ')':
                arr.clear();
                op1 = stack.top();
                while (op1 != "("){
                    stack.pop();
                    arr.push_back(op1);
                    op1 = stack.top();
                }
                stack.pop();
                str = "( ";
                for (auto j = arr.rbegin(); j != arr.rend(); ++j){
                    str = str + *j + " ";
                }
                stack.push(str + ")");
                break;
            case '|':
                op2 = stack.top();
                stack.pop();
                op1 = stack.top();
                stack.pop();
                stack.push(op1 + " | " + op2);
                break;
            case '(':
                stack.push("(");
                break;
            default:
                stack.push(names.at(*i));
                break;
        }
    }
    str = "";
    while (!stack.empty()){
        str = stack.top() + " " + str;
        stack.pop();
    }
    system(str.c_str());
}

int
main(){
    std::map<char, std::string> names;
    std::string str, str1;
    while(getline(std::cin, str)){
        if (str.empty()){
            break;
        }
        else{
            names.insert({str[0], &str[1]});
        }
    }
    while(getline(std::cin, str)){
        std::stringstream stream;
        Parser prsr;
        stream.str(str);
        if (prsr.parse(stream, names)){
            interpret(prsr.get_poliz(), names);
        } else{
            std::cout << "NO" << std::endl;
        }
    }
}
