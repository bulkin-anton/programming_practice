#include <iostream>
#include <set>
#include <string>

std::set<std::pair<char, std::string>>
g3(){
    std::set<std::pair<char, std::string>> g;
    g.insert(std::pair<char, std::string>('S', "Ha"));
    g.insert(std::pair<char, std::string>('S', "Sa"));
    g.insert(std::pair<char, std::string>('S', "a"));
    g.insert(std::pair<char, std::string>('H', "Sb"));
    g.insert(std::pair<char, std::string>('H', "Hb"));
    g.insert(std::pair<char, std::string>('H', "b"));
    return g;
}

std::set<std::pair<char, std::string>>
g4(){
    std::set<std::pair<char, std::string>> g;
    g.insert(std::pair<char, std::string>('S', "c"));
    g.insert(std::pair<char, std::string>('S', "aS"));
    g.insert(std::pair<char, std::string>('S', "bS"));
    return g;
}
