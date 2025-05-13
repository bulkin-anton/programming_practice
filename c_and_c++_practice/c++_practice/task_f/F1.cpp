#include <iostream>
#include <cstring>
namespace equations
{

class Expression{
    public:
        virtual int priority() const = 0;
        virtual ~Expression();
        virtual std::ostream& out(std::ostream&) const = 0;
};

Expression::~Expression() {}

class IntVariable{
    public:
        IntVariable(const char*);
        IntVariable(const IntVariable&);
        ~IntVariable();
        IntVariable& operator = (IntVariable);
        const char* get_var() const;
    private:
        void swap(IntVariable&, IntVariable&);
        char *var;
};


IntVariable::IntVariable(const char *s){
    var = new char[strlen(s) + 1];
    strcpy(var, s);
}

IntVariable::IntVariable(const IntVariable &x){
    var = new char[strlen(x.var) + 1];
    strcpy(var, x.var);
}

IntVariable::~IntVariable() {
    delete []var;
}

const char*
IntVariable::get_var() const{
    return var;
}

void
IntVariable::swap(IntVariable &l, IntVariable &r){
    char *ptr = l.var;
    l.var = r.var;
    r.var = ptr;
}

IntVariable&
IntVariable::operator = (IntVariable x){
    swap(*this, x);
    return *this;
}

class VariableExpression: public Expression{
    public:
        VariableExpression(IntVariable&);
        virtual int priority() const;
        virtual std::ostream& out(std::ostream&) const;
    private:
        IntVariable &var;
};

VariableExpression::VariableExpression(IntVariable &x): var(x) {}

int
VariableExpression::priority() const{
    return 0;
}

std::ostream&
VariableExpression::out(std::ostream &x) const{
    x << var.get_var();
    return x;
}

class LiteralExpression: public Expression{
    public:
        LiteralExpression(int);
        virtual int priority() const;
        virtual std::ostream& out(std::ostream&) const;
    private:
        int num;
};

LiteralExpression::LiteralExpression(int i){
    num = i;
}

int
LiteralExpression::priority() const{
    return 0;
}

std::ostream&
LiteralExpression::out(std::ostream &x) const{
    x << num;
    return x;
}

class Unar: public Expression{
    public:
        Unar(Expression*, const char*);
        virtual std::ostream& out(std::ostream&) const;
        Expression& arg() const;
        ~Unar();
    private:
        const char *op;
        Expression *_arg;
};

Unar::Unar(Expression *a, const char *b){
    op = b;
    _arg = a;
}

Unar::~Unar(){
    delete _arg;
}

Expression&
Unar::arg() const{
    return *_arg;
}

std::ostream&
Unar::out(std::ostream &x) const{
    x << op;
    if (arg().priority() > priority()){
        x << '(';
    }
    arg().out(x);
    if (arg().priority() > priority()){
        x << ')';
    }
    return x;
}

class NegativeExpression: public Unar{
    public:
        NegativeExpression(Expression *);
        virtual int priority() const;
};

NegativeExpression::NegativeExpression(Expression *x): Unar(x, "-") {}

int
NegativeExpression::priority() const{
    return 1;
}

class Binar: public Expression{
    public:
        Binar(Expression*, Expression*, const char*);
        virtual std::ostream& out(std::ostream&) const;
        Expression& arg_l() const;
        Expression& arg_r() const;
        ~Binar();
    private:
        Expression *l;
        Expression *r;
        const char *op;
};

Binar::Binar(Expression *a, Expression *c, const char *b){
    l = a;
    r = c;
    op = b;
}

std::ostream&
Binar::out(std::ostream &x) const{
    if (arg_l().priority() > priority()) {
        x << '(';
    }
    arg_l().out(x);
    if (arg_l().priority() > priority()) {
        x << ')';
    }
    x << ' ' << op << ' ';
    if (arg_r().priority() >= priority()) {
        x << '(';
    }
    arg_r().out(x);
    if (arg_r().priority() >= priority()) {
        x << ')';
    }
    return x;
}

Binar::~Binar(){
    delete r;
    delete l;
}

Expression&
Binar::arg_l() const{
    return *l;
}

Expression&
Binar::arg_r() const{
    return *r;
}

class SumExpression: public Binar{
    public:
        SumExpression(Expression *, Expression *);
        virtual int priority() const;
};

SumExpression::SumExpression(Expression *a, Expression *b): Binar(a, b, "+") {}

int
SumExpression::priority() const{
    return 3;
}

class SubExpression: public Binar{
    public:
        SubExpression(Expression *, Expression *);
        virtual int priority() const;
};

SubExpression::SubExpression(Expression *a, Expression *b): Binar(a, b, "-") {}

int
SubExpression::priority() const{
    return 3;
}

class MultiplyExpression: public Binar{
    public:
        MultiplyExpression(Expression *, Expression *);
        virtual int priority() const;
};

MultiplyExpression::MultiplyExpression(Expression *a, Expression *b): Binar(a, b, "*") {}

int
MultiplyExpression::priority() const{
    return 2;
}

class DivisionExpression: public Binar{
    public:
        DivisionExpression(Expression *, Expression *);
        virtual int priority() const;
};

DivisionExpression::DivisionExpression(Expression *a, Expression *b): Binar(a, b, "/") {}

int
DivisionExpression::priority() const{
    return 2;
}

class Printer{
    public:
        Printer(const Expression&);
        friend std::ostream & operator << (std::ostream &, const Printer&);
    private:
        const Expression *expr;
};

Printer::Printer(const Expression &x){
    expr = &x;
}

std::ostream&
operator << (std::ostream &print, const Printer &t){
    return (*t.expr).out(print);
}

class PrettyPrinter{
    public:
        Printer get_infix(const Expression&) const;
};

Printer
PrettyPrinter::get_infix(const Expression &x) const{
    return Printer(x);
}

}
