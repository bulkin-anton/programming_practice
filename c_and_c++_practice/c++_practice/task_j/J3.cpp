#include <set>
#include <iostream>
std::set<std::pair<std::string, std::string>>
g(){
    std::set<std::pair<std::string, std::string>> grammar;
    grammar.insert(std::pair<std::string, std::string>("S", "xx"));
    grammar.insert(std::pair<std::string, std::string>("S", "xSx"));
    grammar.insert(std::pair<std::string, std::string>("S", "yy"));
    grammar.insert(std::pair<std::string, std::string>("S", "ySy"));
    return grammar;
}
