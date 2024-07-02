#ifndef HYPERBOLIC_H
#define HYPERBOLIC_H

#include <iostream>
#include <stdexcept>

class HyperbolicFunctions {
private:
    double x;

    double power(double base, int exp) const {
        double result = 1.0;
        bool isNegative = false;

        if (exp < 0) {
            isNegative = true;
            exp = -exp;
        }

        while (exp > 0) {
            if (exp % 2 == 1) {
                result *= base;
            }
            base *= base;
            exp /= 2;
        }

        return isNegative ? 1.0 / result : result;
    }

    double exp(double value) const {
        const int precision = 20;
        double sum = 1.0;
        double term = 1.0;

        for (int i = 1; i <= precision; ++i) {
            term *= value / i;
            sum += term;
        }

        return sum;
    }

public:
    HyperbolicFunctions(double value) : x(value) {}

    double sinh() const {
        return (exp(x) - exp(-x)) / 2;
    }

    double cosh() const {
        return (exp(x) + exp(-x)) / 2;
    }

    double tanh() const {
        return sinh() / cosh();
    }

    double csch() const {
        if (x == 0) throw std::invalid_argument("csch(x) is undefined for x = 0");
        return 1 / sinh();
    }

    double sech() const {
        return 1 / cosh();
    }

    double coth() const {
        if (x == 0) throw std::invalid_argument("coth(x) is undefined for x = 0");
        return cosh() / sinh();
    }
};

#endif