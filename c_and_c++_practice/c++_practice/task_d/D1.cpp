#include <iostream>
namespace equations{

    class IntVariable{
        public:
            IntVariable();
            void set_num(int);
            friend std::ostream& operator << (std::ostream&, const IntVariable&);
        private:
            int num;
    };

    IntVariable::IntVariable(){
        num = 0;
    }

    std::ostream&
    operator << (std::ostream &out, const IntVariable &x){
        out << x.num;
        return out;
    }

    void
    IntVariable::set_num(int i){
        num = i;
    }

    class Expression{
        public:
            Expression();
            Expression(int);
            Expression(IntVariable&);
        private:
            friend Expression operator + (const Expression&, const Expression&);
            friend Expression operator - (const Expression&, const Expression&);
            friend Expression operator * (const Expression&, const Expression&);
            friend Expression operator + (const Expression&);
            friend Expression operator - (const Expression&);
            friend Expression operator == (const Expression&, const Expression&);
            friend int solve(const Expression&);
            IntVariable *x;
            int mult;
            int num;
            int err;
            int eq;
    };

    Expression::Expression(): x(nullptr), mult(0), num(0), err(0), eq(0) {}

    Expression::Expression(int n): x(nullptr), mult(0), num(n), err(0), eq(0) {}

    Expression::Expression(IntVariable &t): mult(1), num(0), err(0), eq(0) {
        x = &t;
    }

    Expression
    operator + (const Expression &obj1, const Expression &obj2){
        Expression tmp;
        tmp.mult = obj1.mult + obj2.mult;
        tmp.num = obj1.num + obj2.num;
        if (obj1.x != nullptr){
            tmp.x = obj1.x;
            if ((obj2.x != nullptr) && (obj1.x != obj2.x)){
                    tmp.err = 1;
            } else {
                tmp.err = 0;
            }
        } else{
            tmp.x = obj2.x;
            tmp.err = 0;
        }
        tmp.err += obj1.err + obj2.err;
        tmp.eq = 0;
        return tmp;
    }

    Expression
    operator - (const Expression &obj1, const Expression &obj2){
        Expression tmp;
        tmp.mult = obj1.mult - obj2.mult;
        tmp.num = obj1.num - obj2.num;
        if (obj1.x != nullptr){
            tmp.x = obj1.x;
            if ((obj2.x != nullptr) && (obj1.x != obj2.x)){
                    tmp.err = 1;
            } else {
                tmp.err = 0;
            }
        } else{
            tmp.x = obj2.x;
            tmp.err = 0;
        }
        tmp.err += obj1.err + obj2.err;
        tmp.eq = 0;
        return tmp;
    }

    Expression
    operator - (const Expression &obj1){
        Expression tmp;
        tmp.mult = -obj1.mult;
        tmp.num = -obj1.num;
        tmp.x = obj1.x;
        tmp.err = obj1.err;
        tmp.eq = 0;
        return tmp;
    }

    Expression
    operator + (const Expression &obj1){
        Expression tmp;
        tmp.mult = obj1.mult;
        tmp.num = obj1.num;
        tmp.x = obj1.x;
        tmp.err = obj1.err;
        tmp.eq = 0;
        return tmp;
    }

    Expression
    operator * (const Expression &obj1, const Expression &obj2){
        Expression tmp;
        if (obj1.x != nullptr){
            tmp.x = obj1.x;
            tmp.mult = obj1.mult * obj2.num;
            tmp.num = obj1.num * obj2.num;
            if (obj2.x != nullptr){
                tmp.err = 1;
            } else {
                tmp.err = 0;
            }
        } else{
            tmp.x = obj2.x;
            tmp.mult = obj1.num * obj2.mult;
            tmp.num = obj1.num * obj2.num;
            tmp.err = 0;
        }
        tmp.err += obj1.err + obj2.err;
        tmp.eq = 0;
        return tmp;
    }

    Expression
    operator == (const Expression &obj1, const Expression &obj2){
        Expression tmp;
        tmp = obj1 - obj2;
        tmp.eq = 1;
        return tmp;
    }

    int
    solve(const Expression &t){
        if ((t.eq == 0) || (t.err) || (t.x == nullptr) || (t.mult == 0)){
            return -1;
        }
        if ((-t.num) % t.mult){
            return 1;
        }
        t.x -> set_num(-(t.num / t.mult));
        return 0;
    }
}
