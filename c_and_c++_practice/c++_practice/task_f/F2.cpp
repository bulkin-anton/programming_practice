#include <iostream>
#include <cstring>
namespace equations
{

class HelpExpression{
    public:
        virtual int priority() const = 0;
        virtual ~HelpExpression();
        virtual std::ostream& out(std::ostream&) const = 0;
        virtual HelpExpression* dup() const = 0;
};

HelpExpression::~HelpExpression() {}

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

class VariableExpression: public HelpExpression{
    public:
        VariableExpression(IntVariable&);
        virtual int priority() const;
        virtual std::ostream& out(std::ostream&) const;
        virtual HelpExpression* dup() const;
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

HelpExpression*
VariableExpression::dup() const{
    return new VariableExpression(var);
}

class LiteralExpression: public HelpExpression{
    public:
        LiteralExpression(int);
        virtual int priority() const;
        virtual std::ostream& out(std::ostream&) const;
        virtual HelpExpression* dup() const;
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

HelpExpression*
LiteralExpression::dup() const{
    return new LiteralExpression(num);
}

class Unar: public HelpExpression{
    public:
        Unar(HelpExpression*, const char*);
        virtual std::ostream& out(std::ostream&) const;
        HelpExpression& arg() const;
        ~Unar();
    private:
        const char *op;
        HelpExpression *_arg;
};

Unar::Unar(HelpExpression *a, const char *b){
    op = b;
    _arg = a;
}

Unar::~Unar(){
    delete _arg;
}

HelpExpression&
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
        NegativeExpression(HelpExpression *);
        virtual int priority() const;
        virtual HelpExpression* dup() const;
};

NegativeExpression::NegativeExpression(HelpExpression *x): Unar(x, "-") {}

int
NegativeExpression::priority() const{
    return 1;
}

HelpExpression*
NegativeExpression::dup() const{
    return new NegativeExpression(arg().dup());
}

class Binar: public HelpExpression{
    public:
        Binar(HelpExpression*, HelpExpression*, const char*);
        virtual std::ostream& out(std::ostream&) const;
        HelpExpression& arg_l() const;
        HelpExpression& arg_r() const;
        ~Binar();
    private:
        HelpExpression *l;
        HelpExpression *r;
        const char *op;
};

Binar::Binar(HelpExpression *a, HelpExpression *c, const char *b){
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

HelpExpression&
Binar::arg_l() const{
    return *l;
}

HelpExpression&
Binar::arg_r() const{
    return *r;
}

class SumExpression: public Binar{
    public:
        SumExpression(HelpExpression *, HelpExpression *);
        virtual int priority() const;
        virtual HelpExpression* dup() const;
};

SumExpression::SumExpression(HelpExpression *a, HelpExpression *b): Binar(a, b, "+") {}

int
SumExpression::priority() const{
    return 3;
}

HelpExpression*
SumExpression::dup() const{
    return new SumExpression(arg_l().dup(), arg_r().dup());
}

class SubExpression: public Binar{
    public:
        SubExpression(HelpExpression *, HelpExpression *);
        virtual int priority() const;
        virtual HelpExpression* dup() const;
};

SubExpression::SubExpression(HelpExpression *a, HelpExpression *b): Binar(a, b, "-") {}

int
SubExpression::priority() const{
    return 3;
}

HelpExpression*
SubExpression::dup() const{
    return new SubExpression(arg_l().dup(), arg_r().dup());
}

class MultiplyExpression: public Binar{
    public:
        MultiplyExpression(HelpExpression *, HelpExpression *);
        virtual int priority() const;
        virtual HelpExpression* dup() const;
};

MultiplyExpression::MultiplyExpression(HelpExpression *a, HelpExpression *b): Binar(a, b, "*") {}

int
MultiplyExpression::priority() const{
    return 2;
}

HelpExpression*
MultiplyExpression::dup() const{
    return new MultiplyExpression(arg_l().dup(), arg_r().dup());
}

class DivisionExpression: public Binar{
    public:
        DivisionExpression(HelpExpression *, HelpExpression *);
        virtual int priority() const;
        virtual HelpExpression* dup() const;
};

DivisionExpression::DivisionExpression(HelpExpression *a, HelpExpression *b): Binar(a, b, "/") {}

int
DivisionExpression::priority() const{
    return 2;
}

HelpExpression*
DivisionExpression::dup() const{
    return new DivisionExpression(arg_l().dup(), arg_r().dup());
}


class Expression{
    public:
        Expression(int);
        Expression(IntVariable &);
        Expression(HelpExpression *);
        Expression(const Expression &);
        ~Expression();
        const HelpExpression* get_expr() const;
        Expression & operator = (const Expression &);
    private:
        HelpExpression *expr;
};

Expression::Expression(int t){
    expr = new LiteralExpression(t);
}

Expression::Expression(IntVariable &x){
    expr = new VariableExpression(x);
}

Expression::Expression(HelpExpression *t){
    expr = t;
}

Expression::Expression(const Expression &x){
    expr = x.expr -> dup();
}

Expression::~Expression(){
     delete expr;
}

Expression&
Expression::operator = (const Expression &x){
    if (this == &x){
        return *this;
    }
    delete expr;
    expr = x.expr -> dup();
    return *this;
}

Expression
operator + (Expression y, Expression x){
    return new SumExpression(y.get_expr() -> dup(), x.get_expr() -> dup());
}

Expression
operator - (Expression y, Expression x){
    return new SubExpression(y.get_expr() -> dup(), x.get_expr() -> dup());
}

Expression
operator / (Expression y, Expression x){
    return new DivisionExpression(y.get_expr() -> dup(), x.get_expr() -> dup());
}

Expression
operator * (Expression y, Expression x){
    return new MultiplyExpression(y.get_expr() -> dup(), x.get_expr() -> dup());
}

Expression
operator - (Expression y){
    return new NegativeExpression(y.get_expr() -> dup());
}

const HelpExpression*
Expression::get_expr() const{
    return expr;
}

class Printer{
    public:
        Printer(const HelpExpression&);
        friend std::ostream & operator << (std::ostream &, const Printer&);
    private:
        const HelpExpression *expr;
};

Printer::Printer(const HelpExpression &x){
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
    return Printer(*(x.get_expr()));
}

}
