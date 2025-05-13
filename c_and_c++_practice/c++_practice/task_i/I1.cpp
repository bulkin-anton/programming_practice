#include <vector>
#include <list>
#include <string>
#include <set>
namespace with_vector{
    int
    fun(std::string const &s1, std::string const &s2){
        std::vector<std::string> arr;
        for (size_t i = 0; i < s1.length() + 1; i++){
            for (size_t j = 0; j < s1.length() - i + 1; j++){
                for (size_t k = 0; k < s2.length() + 1; k++){
                    for (size_t l = 0; l < s2.length() - k + 1; l++){
                        arr.push_back(s1.substr(i, j) + s2.substr(k, l));
                        arr.push_back(s2.substr(k, l) + s1.substr(i, j));
                    }
                }
            }
        }
        std::vector<std::string> set_arr;
        for (std::vector<std::string>::const_iterator c = arr.begin();
             c != arr.end(); ++c){
            int cnt = 0;
            for (std::vector<std::string>::const_iterator s = set_arr.begin();
                 s != set_arr.end(); ++s){
                if (*s == *c){
                    cnt++;
                    break;
                }
            }
            if (cnt == 0){
                set_arr.push_back(*c);
            }
        }
        return set_arr.size();
    }
}

namespace with_list{
    int
    fun(std::string const &s1, std::string const &s2){
        std::list<std::string> arr;
        for (size_t i = 0; i < s1.length() + 1; i++){
            for (size_t j = 0; j < s1.length() - i + 1; j++){
                for (size_t k = 0; k < s2.length() + 1; k++){
                    for (size_t l = 0; l < s2.length() - k + 1; l++){
                        arr.push_back(s1.substr(i, j) + s2.substr(k, l));
                        arr.push_back(s2.substr(k, l) + s1.substr(i, j));
                    }
                }
            }
        }
        std::list<std::string> set_arr;
        for (std::list<std::string>::const_iterator c = arr.begin();
             c != arr.end(); ++c){
            int cnt = 0;
            for (std::list<std::string>::const_iterator s = set_arr.begin();
                 s != set_arr.end(); ++s){
                if (*s == *c){
                    cnt++;
                    break;
                }
            }
            if (cnt == 0){
                set_arr.push_back(*c);
            }
        }
        return set_arr.size();
    }
}

namespace with_best{
    int
    fun(std::string const &s1, std::string const &s2){
        std::set<std::string> arr;
        for (size_t i = 0; i < s1.length() + 1; i++){
            for (size_t j = 0; j < s1.length() - i + 1; j++){
                for (size_t k = 0; k < s2.length() + 1; k++){
                    for (size_t l = 0; l < s2.length() - k + 1; l++){
                        arr.insert(s1.substr(i, j) + s2.substr(k, l));
                        arr.insert(s2.substr(k, l) + s1.substr(i, j));
                    }
                }
            }
        }
        return arr.size();
    }
}
