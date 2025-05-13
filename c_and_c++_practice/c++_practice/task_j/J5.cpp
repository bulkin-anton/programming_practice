#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <string>

std::set<char>
form_set_x(std::set<std::pair<std::string, std::string>> &x){
    std::set<char> ans;
    for (std::set<std::pair<std::string, std::string>>::iterator i = x.begin();
    i != x.end(); ++i){
        if (i -> second == ""){
            ans.insert((i -> first)[0]);
        }
    }
    if (ans.size() == 0) {
        return ans;
    }
    while(1) {
        bool changed = false;
        for (std::set<std::pair<std::string, std::string>>::iterator i = x.begin();
            i != x.end(); ++i) {
            bool fl = true;
            for (std::string::const_iterator j = (i -> second).begin(); j != (i -> second).end(); ++j) {
                if (ans.find(*j) == ans.end()) {
                    fl = false;
                }
            }
            if (fl && ans.insert(i->first[0]).second) {
                changed = true;
            }
        }
        if (!changed) {
            return ans;
        }
    }
}

std::set<std::pair<std::string, std::string>>
form_set_p(std::set<std::pair<std::string, std::string>> &x){
    std::set<std::pair<std::string, std::string>> ans;
    for (std::set<std::pair<std::string, std::string>>::iterator i = x.begin();
    i != x.end(); ++i){
        if (i -> second != ""){
            ans.insert(*i);
        }
    }
    return ans;
}

bool
check_s_in_x(std::set<char> &x, std::set<std::pair<std::string, std::string>> &g){
    if (x.find('S') != x.end()) {
        g.insert(std::pair<std::string, std::string>("T", ""));
        g.insert(std::pair<std::string, std::string>("T", "S"));
        return true;
    }
    return false;
}

std::vector<size_t>
form_pos_in_str(std::string const &str, std::set<char> &x){
    std::vector<size_t> ans;
    for (size_t i = 0; i < str.length(); ++i){
        if (x.find(str[i]) != x.end()){
            ans.push_back(i);
        }
    }
    return ans;
}

void
add_set_p(std::vector<size_t> &pos, std::set<std::pair<std::string, std::string>> &g,
        size_t cnt, std::set<std::pair<std::string, std::string>>::iterator &i){
    for (size_t l = 0; l < cnt; ++l) {
        std::string s = i -> second;
        for (size_t j = 0; j < pos.size(); ++j) {
            if (((l >> j) % 2) == 0) {
                s.erase(pos[j], 1);
            }
        }
        if ((l != 0) || (s != "")) {
            g.insert(std::pair<std::string, std::string>(i -> first, s));
        }
    }
}

void
add_in_grammar(std::set<std::pair<std::string, std::string>>::iterator &i, std::set<char> &x, std::set<std::pair<std::string, std::string>> &g){
    std::vector<size_t> pos_in_str = form_pos_in_str(i -> second, x);
    size_t cnt = 1 << pos_in_str.size();
    if (cnt == 1) {
        g.insert(*i);
    } else{
        add_set_p(pos_in_str, g, cnt, i);
    }
}

void
del_same(std::set<std::pair<std::string, std::string>> &x){
    std::set<std::pair<std::string, std::string>> g;
    for (std::set<std::pair<std::string, std::string>>::iterator i = x.begin(); i!= x.end(); ++i){
        if (i -> second != i -> first){
            g.insert(*i);
        }
    }
    x = g;
}

void
del_infertile(std::set<std::pair<std::string, std::string>> &x){
    std::set<char> f;
    std::set<char> T;
    for (std::set<std::pair<std::string, std::string>>::iterator i = x.begin(); i != x.end(); ++i){
        for(std::string::const_iterator j = (i -> second).begin(); j != (i -> second).end(); ++j){
            if (!(isupper(*j))){
                T.insert(*j);
            }
        }
    }
    while (1){
        size_t sz = f.size();
        for (std::set<std::pair<std::string, std::string>>::iterator i = x.begin();
            i != x.end(); ++i){
            size_t cnt = 0;
            for (size_t j = 0; j < (i -> second).length(); ++j){
                if ((T.find((i -> second)[j]) != T.end()) || (f.find((i -> second)[j]) != f.end())){
                    cnt++;
                }
            }
            if (cnt == (i -> second).length()){
                f.insert((i -> first)[0]);
            }
        }
        if (sz == f.size()){
            break;
        }
    }
    std::set<std::pair<std::string, std::string>> g;
    for (std::set<std::pair<std::string, std::string>>::iterator i = x.begin(); i != x.end(); ++i){
        if (f.find((i -> first)[0]) != f.end()){
            size_t cnt = 0;
            for (size_t j = 0; j < (i -> second).length(); ++j){
                if ((T.find((i -> second)[j]) != T.end()) || (f.find((i -> second)[j]) != f.end())){
                    cnt++;
                }
            }
            if (cnt == (i -> second).length()){
                g.insert(*i);
            }
        }
    }
    x = g;
}

void
del_unreach(std::set<std::pair<std::string, std::string>> &x, char c){
    std::set<char> V;
    V.insert(c);
    while (1) {
        bool changed = false;
        for (std::set<std::pair<std::string, std::string>>::iterator i = x.begin(); i != x.end(); ++i) {
            if (V.find((i -> first)[0]) != V.end()) {
                for (std::string::const_iterator j = (i -> second).begin(); j != (i -> second).end(); ++j) {
                    if ((*j != ':') && V.insert(*j).second) {
                        changed = true;
                    }
                }
            }
        }
        if (!changed) {
            break;
        }
    }
    std::set<std::pair<std::string, std::string>> g;
    for (std::set<std::pair<std::string, std::string>>::iterator i = x.begin(); i != x.end(); ++i) {
        bool add = true;
        for (std::string::const_iterator j = (i -> first).begin(); j != (i -> first).end(); ++j) {
            if (V.find(*j) == V.end()) {
                add = false;
            }
        }
        if (add) {
            for (std::string::const_iterator j = (i -> second).begin(); j != (i -> second).end(); ++j) {
                if (V.find(*j) == V.end()) {
                    add = false;
                }
            }
        }
        if (add) {
            g.insert(*i);
        }
    }
    x = g;
}

void
process(std::set<std::pair<std::string, std::string>> &x){
    std::set<char> set_x = form_set_x(x);
    std::set<std::pair<std::string, std::string>> g = form_set_p(x);
    bool new_start = check_s_in_x(set_x, g);
    std::set<std::pair<std::string, std::string>> new_g;
    for (std::set<std::pair<std::string, std::string>>::iterator i = g.begin(); i != g.end(); ++i){
        add_in_grammar(i, set_x, new_g);
    }
    del_same(new_g);
    del_infertile(new_g);
    if (new_start) {
        del_unreach(new_g, 'T');
    }
    else {
        del_unreach(new_g, 'S');
    }
    x = new_g;
}

void
out(std::pair<std::string, std::string> const &x){
    std::cout << x.first << ':' << x.second << std::endl;
}

int
main(){
    std::set<std::pair<std::string, std::string>> grammar;
    std::string x;
    while(std::cin >> x){
        grammar.insert(std::pair<std::string, std::string>(x.substr(0, x.find(':')),
        x.substr(x.find(':') + 1)));
    }
    process(grammar);
    for_each(grammar.begin(), grammar.end(), out);
}
