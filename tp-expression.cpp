/*
implement a hierarchy of classes for arithmetic expression manipulations:
    - the classes holds, evaluates and prints arithmetic expressions
    - print in infix, prefix or postfix notation

Additional work:
   - note that the postfix notation is also called Reverse Polish notation (RPN)
   - it is a mathematical notation in which operators follow their operands
   - this notation does not need any parentheses i.e. this notation is non ambiguous
   - => you can read (easily) RPN expressions using a stacks
  implement a code to read RPN expression and store them with your class objects
  RPN arithmetic expression are passed as main command-line arguments

./main 87 12 - + 75 -
*/
#include <iostream>

class Expression {
    virtual void print() = 0;
    virtual int eval() = 0;
};

class Constant : public Expression {
public:
    unsigned int val;
    Constant(unsigned int x) : val(x) {};
    void print() {std::cout << val << " " << std::endl;}
    int eval() {
        return val;
    }
};
class UnaryMinus : public Expression {
    Constant c;
public:
    UnaryMinus(unsigned int x) : c(Constant(x)) {};
    void print() {std::cout << "-" << c.val << " " << std::endl;}
    int eval() {
        return -c.val;
    }
};
class Plus : public Expression {
    Expression exp1;
    Expression exp2;
public:
    Plus(Expression e1, Expression e2) : exp1(e1), exp2(e2) {};
    void print() {std::cout << exp1 << exp2 << "+ ";}
    int eval() {
        return exp1.eval() + exp2.eval();
    }
};
class Minus : public Expression {
    Expression exp1;
    Expression exp2;
public:
    Plus(Expression e1, Expression e2) : exp1(e1), exp2(e2) {};
    void print() {std::cout << exp1 << exp2 << "- ";}
    int eval() {
        return exp1.eval() - exp2.eval();
    }
};
class Times : public Expression {
    Expression exp1;
    Expression exp2;
public:
    Plus(Expression e1, Expression e2) : exp1(e1), exp2(e2) {};
    void print() {std::cout << exp1 << exp2 << "* ";}
    int eval() {
        return exp1.eval() * exp2.eval();
    }
};
class Divide : public Expression {
    Expression exp1;
    Expression exp2;
public:
    Plus(Expression e1, Expression e2) : exp1(e1), exp2(e2) {};
    void print() {std::cout << exp1 << exp2 << "/ ";}
    int eval() {
        return exp1.eval() / exp2.eval();
    }
};



int main()
{
    try
    {
        // Constant c1(12), c2(-87), c3(23); // try it (-87 is not an unsigned int)
        Constant c1(12), c2(87), c3(75);

        c1.print(); // affiche 12
        std::cout << std::endl;
        std::cout << "eval " << c1.eval() << std::endl; // affiche 12

        UnaryMinus u1(c1);
        u1.print(); // affiche 12 -
        std::cout << std::endl;
        std::cout << "eval " << u1.eval() << std::endl; // affiche -12

        Plus p1(c2, u1);
        p1.print(); // affiche 87 12 -+
        std::cout << std::endl;
        std::cout << "eval " << p1.eval() << std::endl; // affiche 75

        // Minus m1(p1, c3);
        // m1.print(); // 87 12 -+75 -
        // std::cout << std::endl;
        // std::cout << "eval " << m1.eval() << std::endl; // affiche 0

        // Divide d1(p1, m1);
        // std::cout << std::endl;
        // std::cout << d1.eval() << std::endl; // throws an instance of 'std::runtime_error'

        // std::vector<Expression*> expr;
        // expr.push_back(&c1);
        // expr.push_back(&u1);
        // // parcourez le vecteur
    }
    catch (std::runtime_error &e)
    {
        // affiche zero divide error
        std::cout << e.what() << std::endl;
    }
    return 0;
}
