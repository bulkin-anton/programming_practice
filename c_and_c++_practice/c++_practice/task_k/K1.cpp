#include <iostream>
#include <set>
#include <string>
std::set<std::pair<char, std::string>>
g3(){
    std::set<std::pair<char, std::string>> g;
    g.insert(std::pair<char, std::string>('S', "Ac"));
    g.insert(std::pair<char, std::string>('A', "Bb"));
    g.insert(std::pair<char, std::string>('B', "Sa"));
    g.insert(std::pair<char, std::string>('S', "d"));
    return g;
}

std::set<std::pair<char, std::string>>
g4(){
    std::set<std::pair<char, std::string>> g;
    g.insert(std::pair<char, std::string>('S', "A_"));
    g.insert(std::pair<char, std::string>('S', "B_"));
    g.insert(std::pair<char, std::string>('A', "a"));
    g.insert(std::pair<char, std::string>('A', "Aa"));
    g.insert(std::pair<char, std::string>('B', "Bb"));
    g.insert(std::pair<char, std::string>('B', "Ab"));
    return g;
}
