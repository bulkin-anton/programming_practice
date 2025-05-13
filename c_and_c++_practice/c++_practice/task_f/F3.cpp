#include <iostream>
#include <cstring>
namespace equations
{

class HelpExpression;
class Binar;
class Unar;
class LiteralExpression;
class VariableExpression;

class Visitor{
    public:
        virtual void visit(const HelpExpression&) const = 0;
        virtual void visit(const Binar&) const = 0;
        virtual void visit(const Unar&) const = 0;
        virtual void visit(const LiteralExpression&) const = 0;
        virtual void visit(const VariableExpression&) const = 0;
        virtual ~Visitor();
};

Visitor::~Visitor() {};

class HelpExpression{
    public:
        virtual int priority() const = 0;
        virtual ~HelpExpression();
        virtual HelpExpression* dup() const = 0;
        virtual void accept(const Visitor&) const = 0;
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
        virtual HelpExpression* dup() const;
        void accept(const Visitor&) const;
        const IntVariable& get_variable() const;
        IntVariable& get_variable();
    private:
        IntVariable &var;
};

VariableExpression::VariableExpression(IntVariable &x): var(x) {}

int
VariableExpression::priority() const{
    return 0;
}

HelpExpression*
VariableExpression::dup() const{
    return new VariableExpression(var);
}

void
VariableExpression::accept(const Visitor &x) const{
    return x.visit(*this);
}

const IntVariable&
VariableExpression::get_variable() const{
    return var;
}

IntVariable&
VariableExpression::get_variable(){
    return var;
}

class LiteralExpression: public HelpExpression{
    public:
        LiteralExpression(int);
        virtual int priority() const;
        virtual HelpExpression* dup() const;
        void accept(const Visitor&) const;
        int get_num() const;
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

int
LiteralExpression::get_num() const{
    return num;
}

void
LiteralExpression::accept(const Visitor &x) const{
    return x.visit(*this);
}

HelpExpression*
LiteralExpression::dup() const{
    return new LiteralExpression(num);
}

class Unar: public HelpExpression{
    public:
        Unar(HelpExpression*, const char*);
        HelpExpression& arg() const;
        ~Unar();
        void accept(const Visitor&) const;
        const char* operation() const;
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

const char*
Unar::operation() const{
    return op;
}

HelpExpression&
Unar::arg() const{
    return *_arg;
}

void
Unar::accept(const Visitor &x) const{
    return x.visit(*this);
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
        HelpExpression& arg_l() const;
        HelpExpression& arg_r() const;
        ~Binar();
        void accept(const Visitor&) const;
        const char* operation() const;
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

Binar::~Binar(){
    delete r;
    delete l;
}

const char*
Binar::operation() const{
    return op;
}

HelpExpression&
Binar::arg_l() const{
    return *l;
}

HelpExpression&
Binar::arg_r() const{
    return *r;
}

void
Binar::accept(const Visitor &x) const{
    return x.visit(*this);
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

class Printer;

class PrettyPrinter: public Visitor{
    public:
        PrettyPrinter();
        PrettyPrinter(const HelpExpression&, std::ostream&);
        Printer get_infix(const Expression&) const;
        void visit(const HelpExpression&) const;
        void visit(const Binar&) const;
        void visit(const Unar&) const;
        void visit(const LiteralExpression&) const;
        void visit(const VariableExpression&) const;
    private:
        std::ostream &x;
};

PrettyPrinter::PrettyPrinter(): x(std::cout) {}

PrettyPrinter::PrettyPrinter(const HelpExpression &expr, std::ostream &out): x(out){
    visit(expr);
}

class Printer{
    public:
        Printer(const HelpExpression&, const PrettyPrinter&);
        friend std::ostream & operator << (std::ostream &, const Printer&);
    private:
        const HelpExpression *expr;
};

Printer::Printer(const HelpExpression &x, const PrettyPrinter &t): expr(&x) {}

std::ostream&
operator << (std::ostream &out, const Printer &t){
    PrettyPrinter((*t.expr), out);
    return out;
}

Printer
PrettyPrinter::get_infix(const Expression &ex) const{
    return Printer(*(ex.get_expr()), *this);
}

void
PrettyPrinter::visit(const HelpExpression &t) const{
    return t.accept(*this);
}

void
PrettyPrinter::visit(const Binar &obj) const{
    if (obj.arg_l().priority() > obj.priority()) {
        x << '(';
    }
    visit(obj.arg_l());
    if (obj.arg_l().priority() > obj.priority()) {
        x << ')';
    }
    x << ' ' << obj.operation() << ' ';
    if (obj.arg_r().priority() >= obj.priority()) {
        x << '(';
    }
    visit(obj.arg_r());
    if (obj.arg_r().priority() >= obj.priority()) {
        x << ')';
    }
}

void
PrettyPrinter::visit(const Unar &obj) const{
    x << obj.operation();
    if (obj.arg().priority() > obj.priority()){
        x << '(';
    }
    visit(obj.arg());
    if (obj.arg().priority() > obj.priority()){
        x << ')';
    }
}

void
PrettyPrinter::visit(const LiteralExpression &obj) const{
    x << obj.get_num();
}

void
PrettyPrinter::visit(const VariableExpression &obj) const{
    x << obj.get_variable().get_var();
}

}
