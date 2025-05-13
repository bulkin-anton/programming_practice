#include <climits>
#include <exception>
namespace no_exceptions
{

    enum ErrorCodes
    {
        SUCCESS,
        OVERFLOW,
        DIVBYZERO,
    };

    static const char *errors[] =
    {
        [SUCCESS] = "Success",
        [OVERFLOW] = "Integer overflow",
        [DIVBYZERO] = "Division by zero",
    };

    struct Expression
    {
        virtual int get_value(int &) const = 0;
        virtual ~Expression();
    };

    Expression::~Expression() {};

    struct IntVariable{
        public:
            IntVariable();
            void set_value(int);
            int get_value() const;
        private:
            int val;
    };

    IntVariable::IntVariable(): val(0) {}

    void
    IntVariable::set_value(int i){
        val = i;
    }

    int
    IntVariable::get_value() const{
        return val;
    }

    struct VariableExpression: public Expression{
        public:
            VariableExpression(const IntVariable&);
            int get_value(int&) const;
        private:
            const IntVariable &var;
    };

    VariableExpression::VariableExpression(const IntVariable &x): var(x) {}

    int
    VariableExpression::get_value(int &value) const{
        value = var.get_value();
        return SUCCESS;
    }

    struct LiteralExpression: public Expression{
        public:
            LiteralExpression(int);
            int get_value(int&) const;
        private:
            int var;
    };

    LiteralExpression::LiteralExpression(int i): var(i) {}

    int
    LiteralExpression::get_value(int &value) const{
        value = var;
        return SUCCESS;
    }

    struct BinaryExpression: Expression
    {
        Expression const & left;
        Expression const & right;
        BinaryExpression(Expression const &left_, Expression const &right_);
    };

    BinaryExpression::BinaryExpression(Expression const &left_, Expression const &right_): left(left_), right(right_) {}


    struct SumExpression: BinaryExpression
    {
        SumExpression(Expression const &left_, Expression const &right_);
        int get_value(int &) const;
    };

    SumExpression::SumExpression(Expression const &left_, Expression const &right_): BinaryExpression(left_, right_) {}

    int
    SumExpression::get_value(int &value) const
    {
        int ret;

        int left_value;
        if ((ret = left.get_value(left_value)) != 0) {
            return ret;
        }

        int right_value;
        if ((ret = right.get_value(right_value)) != 0) {
            return ret;
        }

        if (((left_value >= 0) && (right_value > INT_MAX - left_value))
            || ((left_value < 0) && (right_value < INT_MIN - left_value))) {
            return OVERFLOW;
        }

        value = left_value + right_value;
        return SUCCESS;
    }

    struct MultExpression: BinaryExpression
    {
        MultExpression(Expression const &left_, Expression const &right_);
        int get_value(int &) const;
    };

    MultExpression::MultExpression(Expression const &left_, Expression const &right_): BinaryExpression(left_, right_) {}

    int
    MultExpression::get_value(int &value) const
    {
        int ret;

        int left_value;
        if ((ret = left.get_value(left_value)) != 0) {
            return ret;
        }

        int right_value;
        if ((ret = right.get_value(right_value)) != 0) {
            return ret;
        }

        if (((left_value >= 0) && (right_value > INT_MAX - left_value))
            || ((left_value < 0) && (right_value < INT_MIN - left_value))) {
            return OVERFLOW;
        }

        value = left_value * right_value;
        return SUCCESS;
    }

    struct DivExpression: BinaryExpression
    {
        DivExpression(Expression const &left_, Expression const &right_);
        int get_value(int &) const;
    };

    DivExpression::DivExpression(Expression const &left_, Expression const &right_): BinaryExpression(left_, right_) {}

    int
    DivExpression::get_value(int &value) const
    {
        int ret;

        int left_value;
        if ((ret = left.get_value(left_value)) != 0) {
            return ret;
        }

        int right_value;
        if ((ret = right.get_value(right_value)) != 0) {
            return ret;
        }

        if (((left_value >= 0) && (right_value > INT_MAX - left_value))
            || ((left_value < 0) && (right_value < INT_MIN - left_value))) {
            return OVERFLOW;
        }

        if (right_value == 0){
            return DIVBYZERO;
        }
        value = left_value / right_value;
        return SUCCESS;
    }
}

namespace with_exceptions
{
    enum ErrorCodes
    {
        SUCCESS,
        OVERFLOW,
        DIVBYZERO,
    };

    static const char *errors[] =
    {
        [SUCCESS] = "Success",
        [OVERFLOW] = "Integer overflow",
        [DIVBYZERO] = "Division by zero",
    };

    class Except: public std::exception{
        public:
            Except(int);
            int get_except() const;
        private:
            int except;
    };

    Except::Except(int i): except(i) {}

    int
    Except::get_except() const{
        return except;
    }

    struct Expression
    {
        virtual int get_value() const = 0;
        virtual ~Expression();
    };

    Expression::~Expression() {};

    struct IntVariable{
        public:
            IntVariable();
            void set_value(int);
            int get_value() const;
        private:
            int val;
    };

    IntVariable::IntVariable(): val(0) {}

    void
    IntVariable::set_value(int i){
        val = i;
    }

    int
    IntVariable::get_value() const{
        return val;
    }

    struct VariableExpression: public Expression{
        public:
            VariableExpression(const IntVariable&);
            int get_value() const;
        private:
            const IntVariable &var;
    };

    VariableExpression::VariableExpression(const IntVariable &x): var(x) {}

    int
    VariableExpression::get_value() const{
        return var.get_value();
    }

    struct LiteralExpression: public Expression{
        public:
            LiteralExpression(int);
            int get_value() const;
        private:
            int var;
    };

    LiteralExpression::LiteralExpression(int i): var(i) {}

    int
    LiteralExpression::get_value() const{
        return var;
    }

    struct BinaryExpression: Expression
    {
        Expression const & left;
        Expression const & right;
        BinaryExpression(Expression const &left_, Expression const &right_);
    };

    BinaryExpression::BinaryExpression(Expression const &left_, Expression const &right_): left(left_), right(right_) {}


    struct SumExpression: BinaryExpression
    {
        SumExpression(Expression const &left_, Expression const &right_);
        int get_value() const;
    };

    SumExpression::SumExpression(Expression const &left_, Expression const &right_): BinaryExpression(left_, right_) {}

    int
    SumExpression::get_value() const
    {
        int left_value = left.get_value();
        int right_value = right.get_value();
        if (((left_value >= 0) && (right_value > INT_MAX - left_value))
            || ((left_value < 0) && (right_value < INT_MIN - left_value))) {
            throw Except(OVERFLOW);
        }
        return left_value + right_value;
    }

    struct MultExpression: BinaryExpression
    {
        MultExpression(Expression const &left_, Expression const &right_);
        int get_value() const;
    };

    MultExpression::MultExpression(Expression const &left_, Expression const &right_): BinaryExpression(left_, right_) {}

    int
    MultExpression::get_value() const
    {
        int left_value = left.get_value();
        int right_value = right.get_value();
        if (((left_value >= 0) && (right_value > INT_MAX - left_value))
            || ((left_value < 0) && (right_value < INT_MIN - left_value))) {
            throw Except(OVERFLOW);
        }
        return left_value * right_value;
    }

    struct DivExpression: BinaryExpression
    {
        DivExpression(Expression const &left_, Expression const &right_);
        int get_value() const;
    };

    DivExpression::DivExpression(Expression const &left_, Expression const &right_): BinaryExpression(left_, right_) {}

    int
    DivExpression::get_value() const
    {
        int left_value = left.get_value();
        int right_value = right.get_value();
        if (((left_value >= 0) && (right_value > INT_MAX - left_value))
            || ((left_value < 0) && (right_value < INT_MIN - left_value))) {
            throw Except(OVERFLOW);
        }
        if (right_value == 0){
            throw Except(DIVBYZERO);
        }
        return left_value / right_value;
    }
}

#include <iostream>

int main()
{
    {
        using namespace no_exceptions;
        IntVariable x, y, z;
        VariableExpression ex(x);
        VariableExpression ey(y);
        VariableExpression ez(z);
        LiteralExpression c(2);
        MultExpression e1(c, ey);
        SumExpression e2(ex, e1);
        DivExpression e3(ez, e2);
        x.set_value(10);
        y.set_value(20);
        z.set_value(130);
        int value, ret;
        if ((ret = e3.get_value(value)) == 0) {
            std::cout << value << std::endl;
        } else {
            std::cout << errors[ret] << std::endl;
        }
    }
    {
        using namespace with_exceptions;
        try{
            IntVariable x, y, z;
            VariableExpression ex(x);
            VariableExpression ey(y);
            VariableExpression ez(z);
            LiteralExpression c(2);
            MultExpression e1(c, ey);
            SumExpression e2(ex, e1);
            DivExpression e3(ez, e2);
            x.set_value(10);
            y.set_value(20);
            z.set_value(130);
            std::cout << e3.get_value() << std::endl;
        }
        catch (const Except &err){
            std::cout << errors[err.get_except()] << std::endl;
        }
        try{
            IntVariable x;
            VariableExpression ex(x);
            LiteralExpression en(INT_MAX);
            MultExpression d(en, ex);
            x.set_value(100);
            std::cout << d.get_value() << std::endl;
        }
        catch (const Except &err){
            std::cout << errors[err.get_except()] << std::endl;
        }
        try{
            IntVariable x;
            VariableExpression ex(x);
            LiteralExpression en(100);
            DivExpression d(en, ex);
            x.set_value(0);
            std::cout << d.get_value() << std::endl;
        }
        catch (const Except &err){
            std::cout << errors[err.get_except()] << std::endl;
        }
    }
}
