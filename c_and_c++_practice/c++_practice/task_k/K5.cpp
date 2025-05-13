#include <iostream>
#include <exception>

enum Tokenkinds{
    OPENING_BRACKET,
    CLOSING_BRACKET,
    ASTERISK,
    PLUS,
    LINE,
    DIGIT,
    TERMINAL,
    END_OF_STREAM
};

class Token{
    public:
        Tokenkinds kind;
        char repr;
};

class TokenStreamIterator{
    public:
        TokenStreamIterator();
        TokenStreamIterator(std::istream&);
        bool operator == (const TokenStreamIterator &) const noexcept;
        bool operator != (const TokenStreamIterator &) const noexcept;
        const Token& operator * () const noexcept;
        const Token* operator -> () const noexcept;
        TokenStreamIterator& operator ++ ();
        TokenStreamIterator operator ++ (int);
    private:
        void read_next();
        std::istream *stream;
        bool end;
        Token token;
};

TokenStreamIterator::TokenStreamIterator(): stream(nullptr), end(true){
    token.kind = END_OF_STREAM;
}

TokenStreamIterator::TokenStreamIterator(std::istream &strm): stream(&strm){
    read_next();
}

bool
TokenStreamIterator::operator == (const TokenStreamIterator &x) const noexcept{
    return ((end && x.end) || (!end && !x.end && (stream == x.stream)));
}

bool
TokenStreamIterator::operator != (const TokenStreamIterator &x) const noexcept{
    return (!((end && x.end) || (!end && !x.end && (stream == x.stream))));
}

const Token&
TokenStreamIterator::operator * () const noexcept{
    return token;
}

const Token*
TokenStreamIterator::operator -> () const noexcept{
    return &token;
}

TokenStreamIterator&
TokenStreamIterator::operator ++ (){
    if (end){
        token.kind = END_OF_STREAM;
        return *this;
    }
    read_next();
    return *this;
}

TokenStreamIterator
TokenStreamIterator::operator ++ (int){
    TokenStreamIterator tmp(*this);
    if (end){
        token.kind = END_OF_STREAM;
        return tmp;
    }
    read_next();
    return tmp;
}

void
TokenStreamIterator::read_next(){
    int c;
    if ((c = stream -> get()) == EOF){
        token.kind = END_OF_STREAM;
        end = true;
        return;
    }
    while (c == ' '){
        if ((c = stream -> get()) == EOF){
            token.kind = END_OF_STREAM;
            end = true;
            return;
        }
    }
    switch(c){
        case '(':
            token.kind = OPENING_BRACKET;
            token.repr = c;
            break;
        case ')':
            token.kind = CLOSING_BRACKET;
            token.repr = c;
            break;
        case '*':
            token.kind = ASTERISK;
            token.repr = c;
            break;
        case '+':
            token.kind = PLUS;
            token.repr = c;
            break;
        case '|':
            token.kind = LINE;
            token.repr = c;
            break;
        case '\\':
            if ((c = stream -> get()) == EOF) {
                throw std::exception();
            }
            switch(c){
                case 'd':
                    token.kind = DIGIT;
                    token.repr = c;
                    break;
                case ' ':
                    token.kind = TERMINAL;
                    token.repr = c;
                    break;
                default:
                    if (!((c == '(') || (c == ')') || (c == '*') || (c == '+') || (c == '|') || (c == '\\'))){
                        throw std::exception();
                    } else{
                        token.kind = TERMINAL;
                        token.repr = c;
                    }
                    break;
            }
            break;
        default:
            token.kind = TERMINAL;
            token.repr = c;
            break;
    }
    end = false;
}
