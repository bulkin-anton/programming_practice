#include <iostream>
#include <string>

int
main(){
    std::cout << 0 << std::endl << 2 << std::endl;
    std::string str;
    while(std::getline(std::cin, str)){
        size_t cnt = 0, cnt_c = 0, err = 0;
        for (size_t i = 0; i < str.size(); i += 2){
            if (!((str[i] == 'a') && (str[i + 1]) == 'b')){
                break;
            } else{
                ++cnt;
            }
        }
        for (size_t i = cnt * 2; i < str.size(); ++i){
            if (str[i] == 'c'){
                ++cnt_c;
            } else{
                ++err;
                break;
            }
        }
        if ((err) || (cnt_c != cnt)){
            std::cout << "NO" << std::endl;
        } else{
            std::cout << "YES" << std::endl;
        }
    }
}
