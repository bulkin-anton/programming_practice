#include <iostream>
#include <set>
#include <string>

std::set<std::pair<char, std::string>> g();

class NKA{
    public:
        void append_rule(char, std::pair<char, char>);
        char find_rule(char) const;
    private:
        std::map<char, std::vector<std::pair<char, char>> rules;
};

void
NKA::append_rule(char c, std::pair<char, char> x){
    if (rules.find(c) == rules.end()){
        rules.insert({c, x});
    } else{
        rules[c].push_back(x);
    }
}

bool
NKA::find_rule(char c, char key, char &ans) const{
    if (rules.find(c) == rules.end()){
        return false;
    } else{
        for (std::vector::iterator i = rules[c].begin(); i != rules[c].end(); ++i){
            if (key == i -> first){
                ans = i -> second;
                return true;
            }
        }
        return false;
    }
}

class State{
    public:
        virtual State* operator * (char) const = 0;
        virtual ~State();
};

State::~State() {}

class Err: public State{
    public:
        State * operator* (char c) const;
};

State*
Err::operator* (char c) const{
    return new Err;
}

class StateDet: public State{
    public:
        StateDet(char c);
        State* operator* (char c) const;
    private:
        char n;
};

State*
StateDet::operator* (char c) const{
    for (std::set<std::pair<char, char>>::iterator i = arr.begin(); i != arr.end(); ++i){
        if (i -> first == c){
            return new StateDet<i -> second>;
        }
    }
    return new Err;
}

void
create_dka(std::set<std::pair<char, std::string>> const &gr, NKA &x){
    for (std::set<std::pair<char, std::string>>::const_iterator i = gr.begin(); i != gr.end(); ++i){
        switch(i -> second.length()){
            case 2:
                x.append_rule({i -> second[0], {i -> second[1], i -> first});
                break;
            case 1:
                x.append_rule({static_cast<char>(-1), {i -> second[0], i -> first});
                break;
            default:
                x.append_rule({static_cast<char>(-1), static_cast<char>(-1), i -> first});
        }
    }
}

int
main(){
    std::set<std::pair<char, std::string>> grammar = g();
    create_dka(grammar);
}
