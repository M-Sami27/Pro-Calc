#ifndef TRIGONOMETRY_H
#define TRIGONOMETRY_H

#include <iostream>
#include <cmath>

const double M_PI = 3.1415926;
const double M_PI_2 = M_PI / 2.0;

class Trigonometry {
public:
    double sine(double degrees) const {
        double radians = degreesToRadians(degrees);
        if (radians < -M_PI || radians > M_PI) {
            std::cerr << "Error: Angle should be in the range [-π, π]\n";
            return NAN;
        }
        double result = 0;
        double term = radians;
        int n = 1;
        for (int i = 1; i <= 10; ++i) {
            result += term;
            n += 2;
            term = -term * radians * radians / (n * (n - 1));
        }
        return result;
    }

    double cosine(double degrees) const {
        double radians = degreesToRadians(degrees);
        if (radians < -M_PI || radians > M_PI) {
            std::cerr << "Error: Angle should be in the range [-π, π]\n";
            return NAN;
        }
        double result = 1;
        double term = 1;
        int n = 0;
        for (int i = 1; i <= 10; ++i) {
            n += 2;
            term = -term * radians * radians / (n * (n - 1));
            result += term;
        }
        return result;
    }

    double tangent(double degrees) const {
        double radians = degreesToRadians(degrees);
        if (degrees == 90.0 || radians == M_PI_2) {
            throw std::invalid_argument("Error: Tangent is undefined at 90 degrees.");
        }
        return sine(degrees) / cosine(degrees);
    }

    double cotangent(double degrees) const {
        return 1.0 / tangent(degrees);
    }

    double cosecant(double degrees) const {
        return 1.0 / sine(degrees);
    }

    double secant(double degrees) const {
        return 1.0 / cosine(degrees);
    }
    double arcsine(double y) const {
        if (y < -1 || y > 1) {
            std::cerr << "Error: arcsin is undefined for |y| > 1\n";
            return NAN;
        }
        if (y == 0.0) {
            throw std::invalid_argument("Error: Arcsine is undefined at zero.");
        }
        double x = y;
        for (int i = 0; i < 10; ++i) {
            x = x - (sine(x) - y) / cosine(x);
        }
        return x;
    }
    double arccosine(double y) const {
        if (y < -1 || y > 1) {
            std::cerr << "Error: arccos is undefined for |y| > 1\n";
            return NAN;
        }
        double angle = M_PI / 2 - arcsine(y);
        if (angle == M_PI / 2 || angle == 3 * M_PI / 2 || angle == 5 * M_PI / 2 ) {
            throw std::invalid_argument("Error: Arccosine is undefined at 90 degrees or its multiples.");
        }
        return angle;
    }
    double arctangent(double x) const {
        if (x == 0.0) {
            throw std::invalid_argument("Error: Arctangent is undefined at zero.");
        }
        double result = 0;
        double term = x;
        for (int n = 0; n < 10; ++n) {
            result += term / (2 * n + 1);
            term = -term * x * x;
        }
        return result;
    }

private:
    double degreesToRadians(double degrees) const {
        return degrees * M_PI / 180.0;
    }
};

#endif // TRIGONOMETRY_H
