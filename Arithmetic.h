#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include <iostream>
#include <stdexcept>

template <typename T>
class Arithmetic {
public:
    T add(T a, T b) {
        return a + b;
    }
    T subtract(T a, T b) {
        return a - b;
    }
    T multiply(T a, T b) {
        return a * b;
    }
    T divide(T a, T b) {
        if (b == 0) {
            throw std::invalid_argument("Division by zero is not allowed.");
        }
        return a / b;
    }
    T percentage(T a) {
        return a / 100;
    }
    T exponential(T x) {
        T result = 1;
        T term = 1;
        const int iterations = 20;
        for (int i = 1; i <= iterations; ++i) {
            term *= x / i;
            result += term;
        }
        return result;
    }
};

#endif // ARITHMETIC_H
