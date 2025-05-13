#include <iostream>
#include <cstring>
#include <exception>

class Except: public std::exception{
    public:
        Except(const char*);
        const char *get_str() const;
    private:
        const char* except;
};

Except::Except(const char *i): except(i) {}

const char*
Except::get_str() const{
    return except;
}

class TokenPool{
    public:
        TokenPool(size_t);
        ~TokenPool();
        size_t token_length() const;
        void get_token(char *addr);
        void return_token(const char *addr);
        TokenPool(const TokenPool&) = delete;
        TokenPool& operator = (const TokenPool&) = delete;
    private:
        size_t len;
        size_t size;
        bool *usage;
        std::string *tokens;
};

TokenPool::TokenPool(size_t i){
    try{
        tokens = new std::string[i];
    }
    catch(std::exception &except){
        throw;
    }
    try{
        usage = new bool[i];
    }
    catch(std::exception &except){
        delete []tokens;
        throw;
    }
    len = i;
    size = 1;
    while (i != 0){
        size++;
        i /= 26;
    }
    for (size_t j = 0; j < len; j++){
        usage[j] = false;
    }
    try{
        fill_by_different_strings(tokens, len, size);
    }
    catch(std::exception &except){
        delete []tokens;
        delete []usage;
        throw;
    }
}

TokenPool::~TokenPool(){
    delete []tokens;
    delete []usage;
}

size_t
TokenPool::token_length() const{
    return size;
}

void
TokenPool::get_token(char *addr){
    size_t i = 0;
    while (i < len){
        if (usage[i] == false){
            usage[i] = true;
            break;
        }
        i++;
    }
    if (i == len){
        throw Except("NO UNUSED TOKENS");
    } else{
        strcpy(addr, tokens[i].c_str());
    }
}

void
TokenPool::return_token(const char *addr){
    size_t i = 0;
    while (i < len){
        if ((strcmp(addr, tokens[i].c_str()) == 0) && (usage[i])){
            break;
        }
        i++;
    }
    if (i == len){
        throw Except("NO ONE OF GIVEN TOKENS");
    } else{
        usage[i] = false;
    }
}
