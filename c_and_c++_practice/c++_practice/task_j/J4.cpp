#include <iostream>
#include <set>
std::set<std::pair<std::string, std::string>>
g(){
    std::set<std::pair<std::string, std::string>> grammar;
    grammar.insert(std::pair<std::string, std::string>("S", "aAB"));
    grammar.insert(std::pair<std::string, std::string>("S", "E"));
    grammar.insert(std::pair<std::string, std::string>("A", "dDA"));
    grammar.insert(std::pair<std::string, std::string>("A", ""));
    grammar.insert(std::pair<std::string, std::string>("B", "bE"));
    grammar.insert(std::pair<std::string, std::string>("B", "f"));
    grammar.insert(std::pair<std::string, std::string>("D", "eA"));
    grammar.insert(std::pair<std::string, std::string>("E", "fA"));
    grammar.insert(std::pair<std::string, std::string>("E", "g"));
    return grammar;
}
