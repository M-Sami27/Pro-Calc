#ifndef COMBINATORICS_H
#define COMBINATORICS_H

#include <iostream>
#include <stdexcept>

class Combinatorics {
public:
    int factorial(int n) const {
        if (n == 0 || n == 1)
            return 1;
        int result = 1;
        for (int i = 2; i <= n; ++i) {
            result *= i;
        }
        return result;
    }
    int permutations(int n, int r) const {
        if (r > n) {
            std::cerr << "Error: r cannot be greater than n\n";
            return 0;
        }
        return factorial(n) / factorial(n - r);
    }
    int combinations(int n, int r) const {
        if (r > n) {
            std::cerr << "Error: r cannot be greater than n\n";
            return 0;
        }
        return factorial(n) / (factorial(r) * factorial(n - r));
    }
};

#endif // COMBINATORICS_H
