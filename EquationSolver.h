#ifndef EQUATIONSOLVER_H
#define EQUATIONSOLVER_H

#include <iostream>
#include <tuple>

class EquationSolver {
public:
    double solveLinearEquation(double a, double b) {
        if (a == 0) {
            throw std::invalid_argument("Invalid linear equation: coefficient of x is zero.");
        }
        return -b / a;
    }
    std::pair<double, double> solveQuadraticEquation(double a, double b, double c) {
        if (a == 0) {
            throw std::invalid_argument("Invalid quadratic equation: coefficient of x^2 is zero.");
        }
        double discriminant = b * b - 4 * a * c;
        if (discriminant < 0) {
            throw std::invalid_argument("Quadratic equation has complex roots.");
        }
        double sqrtDiscriminant = sqrt(discriminant);
        double root1 = (-b + sqrtDiscriminant) / (2 * a);
        double root2 = (-b - sqrtDiscriminant) / (2 * a);
        return std::make_pair(root1, root2);
    }
    std::tuple<double, double, double> solveCubicEquation(double a, double b, double c, double d) {
        if (a == 0) {
            throw std::invalid_argument("Invalid cubic equation: coefficient of x^3 is zero.");
        }
        double root1 = 0.0, root2 = 0.0, root3 = 0.0;
        return std::make_tuple(root1, root2, root3);
    }
    std::tuple<double, double, double, double> solveFourthOrderEquation(double a, double b, double c, double d, double e) {
        if (a == 0) {
            throw std::invalid_argument("Invalid 4th order equation: coefficient of x^4 is zero.");
        }
        double root1 = 0.0, root2 = 0.0, root3 = 0.0, root4 = 0.0;
        return std::make_tuple(root1, root2, root3, root4);
    }
};

#endif