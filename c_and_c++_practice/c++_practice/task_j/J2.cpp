#include <iostream>
#include <string>
#include <set>
#include <algorithm>

bool
nonterm_left(std::pair<std::string, std::string> const &g){
    for (size_t i = 0; i < g.first.size(); i++){
        if (isupper(g.first[i])){
            return true;
        }
    }
    return false;
}

bool
type_1_no_right(std::pair<std::string, std::string> const &x){
    if ((x.first == "S") && (x.second == "")){
        return true;
    }
    if (x.first.size() > x.second.size()){
        return false;
    }
    return true;
}

bool
type_1_right(std::pair<std::string, std::string> const &x){
    if (x.first.size() > x.second.size()){
        return false;
    }
    return true;
}

bool
str_check_s(std::pair<std::string, std::string> const &x){
    if (x.second.find('S') != std::string::npos){
        return true;
    }
    return false;
}

bool
s_in_right(std::set<std::pair<std::string, std::string>> const &x){
    return any_of(x.begin(), x.end(), str_check_s);
}

bool
nonterm_left_one(std::pair<std::string, std::string> const &x) {
    if (x.first.size() != 1){
        return false;
    }
    if (isupper(x.first[0])) return true;
    return false;
}

bool
left_gr(std::pair<std::string, std::string> const &x){
    size_t cnt = 0;
    for (size_t i = 0; i < x.second.size(); ++i) {
        if (isupper(x.second[i])) {
            ++cnt;
        }
    }
    if (cnt == 0) {
        return true;
    }
    if ((cnt == 1) && (isupper(x.second[0]))) {
        return true;
    }
    return false;
}

bool
right_gr(std::pair<std::string, std::string> const &x){
    size_t cnt = 0;
    for (size_t i = 0; i < x.second.size(); ++i) {
        if (isupper(x.second[i])) {
            ++cnt;
        }
    }
    if (cnt == 0) {
        return true;
    }
    if ((cnt == 1) && (isupper(x.second[x.second.size() - 1]))) {
        return true;
    }
    return false;
}

bool
type_0(std::set<std::pair<std::string, std::string>> const &x){
    return all_of(x.begin(), x.end(), nonterm_left);
}

bool
type_1(std::set<std::pair<std::string, std::string>> const &x){
    if (s_in_right(x)){
        return all_of(x.begin(), x.end(), type_1_right);
    } else return all_of(x.begin(), x.end(), type_1_no_right);
}

bool
type_2(std::set<std::pair<std::string, std::string>> const &x){
    return all_of(x.begin(), x.end(), nonterm_left_one);
}

bool
type_3(std::set<std::pair<std::string, std::string>> const &x){
    return (all_of(x.begin(), x.end(), left_gr) || all_of(x.begin(), x.end(), right_gr));
}

int
grammar_type(std::set<std::pair<std::string, std::string>> const &g){
    if (!type_0(g)) {
        return -1;
    }
    int type = 0;
    if (type_1(g)) type = 1;
    if (type_2(g)) type = 2;
    if (type_2(g) && type_3(g)) type = 3;
    return type;
}
