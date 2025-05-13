#include <iostream>
#include <set>
#include <string>
std::set<std::pair<char, std::string>>
g1(){
    std::set<std::pair<char, std::string>> g;
    g.insert(std::pair<char, std::string>('S', "cA"));
    g.insert(std::pair<char, std::string>('A', "aA"));
    g.insert(std::pair<char, std::string>('A', "bA"));
    g.insert(std::pair<char, std::string>('A', "_"));
    return g;
}

std::set<std::pair<char, std::string>>
g2(){
    std::set<std::pair<char, std::string>> g;
    g.insert(std::pair<char, std::string>('S', "c"));
    g.insert(std::pair<char, std::string>('S', "aS"));
    g.insert(std::pair<char, std::string>('S', "bS"));
    return g;
}
