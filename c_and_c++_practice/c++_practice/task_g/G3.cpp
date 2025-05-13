#include <string>
#include <exception>
#include <iostream>

class Action{
    public:
        virtual void run() = 0;
        virtual ~Action();
};

Action::~Action() {}

class TokenizedAction: public Action{
    public:
        TokenizedAction(TokenPool&, Action&);
        ~TokenizedAction();
        void run();
        TokenizedAction(const TokenizedAction&) = delete;
        TokenizedAction& operator = (const TokenizedAction&) = delete;
    private:
        std::string token;
        TokenPool &tok;
        Action &act;
};

TokenizedAction::TokenizedAction(TokenPool &a, Action &b): tok(a), act(b) {
    tok.get_token(const_cast<char*>(token.c_str()));
}

TokenizedAction::~TokenizedAction(){
    tok.return_token(token.c_str());
}

void
TokenizedAction::run(){
    act.run();
}
