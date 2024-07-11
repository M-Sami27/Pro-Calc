#ifndef SCIENTIFICCALCULATOR_H
#define SCIENTIFICCALCULATOR_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <cmath>
#include <regex>
#include <tuple>
#include <sstream>
#include <algorithm>
#include <limits>
#include <iomanip>
#include <vector>
#include <cmath>
#include <stack>
#include <queue>
#include <map>

const double M_PI = 3.1415926;
const double M_PI_2 = M_PI / 2.0;
const double M_E =  2.7182818284590452353602874713527;

class Vector {
private:
    std::vector<double> components;
public:
    Vector(const std::vector<double>& values) : components(values) {}
    Vector operator+(const Vector& other) const {
        if (components.size() != other.components.size()) {
            throw std::invalid_argument("Vectors must have the same dimension for addition");
        }
        std::vector<double> result;
        for (size_t i = 0; i < components.size(); ++i) {
            result.push_back(components[i] + other.components[i]);
        }
        return Vector(result);
    }
    double magnitude() {
        double mag = 0;
        for (size_t i = 0; i < components.size(); i++) {
            mag += components[i] * components[i];
        }
        return sqrt(mag);
    }
    Vector operator-(const Vector& other) const {
        if (components.size() != other.components.size()) {
            throw std::invalid_argument("Vectors must have the same dimension for subtraction");
        }

        std::vector<double> result;
        for (size_t i = 0; i < components.size(); ++i) {
            result.push_back(components[i] - other.components[i]);
        }
        return Vector(result);
    }
    double dotProduct(const Vector& other) const {
        if (components.size() != other.components.size()) {
            throw std::invalid_argument("Vectors must have the same dimension for dot product");
        }
        double result = 0;
        for (size_t i = 0; i < components.size(); ++i) {
            result += components[i] * other.components[i];
        }
        return result;
    }
    Vector crossProduct(const Vector& other) const {
        if (components.size() != 3 || other.components.size() != 3) {
            throw std::invalid_argument("Cross product is only defined for 3D vectors");
        }
        std::vector<double> result(3);
        result[0] = components[1] * other.components[2] - components[2] * other.components[1];
        result[1] = components[2] * other.components[0] - components[0] * other.components[2];
        result[2] = components[0] * other.components[1] - components[1] * other.components[0];
        return Vector(result);
    }
    std::string toString() const {
        std::ostringstream oss;
        oss << "(";
        for (size_t i = 0; i < components.size(); ++i) {
            oss << components[i];
            if (i < components.size() - 1) {
                oss << ", ";
            }
        }
        oss << ")";
        return oss.str();
    }
    Vector() {}
};

class Arithmetic {
public:
    double evaluate(const std::string& expression) {
        std::queue<std::string> postfix = infixToPostfix(expression);
        return evaluatePostfix(postfix);
    }

private:
    std::queue<std::string> infixToPostfix(const std::string& expression) {
        std::stack<std::string> operatorStack;
        std::queue<std::string> outputQueue;
        std::istringstream tokens(expression);
        std::string token;

        while (tokens >> token) {
            if (isNumber(token) || isConstant(token)) {
                outputQueue.push(token);
            } else if (isOperator(token)) {
                while (!operatorStack.empty() && precedence(operatorStack.top()) >= precedence(token) && operatorStack.top() != "(") {
                    outputQueue.push(operatorStack.top());
                    operatorStack.pop();
                }
                operatorStack.push(token);
            } else if (token == "(") {
                operatorStack.push(token);
            } else if (token == ")") {
                while (!operatorStack.empty() && operatorStack.top() != "(") {
                    outputQueue.push(operatorStack.top());
                    operatorStack.pop();
                }
                if (!operatorStack.empty() && operatorStack.top() == "(") {
                    operatorStack.pop(); // pop the "("
                }
            }
        }

        while (!operatorStack.empty()) {
            outputQueue.push(operatorStack.top());
            operatorStack.pop();
        }

        return outputQueue;
    }

    bool isNumber(const std::string& token) {
        char* end = nullptr;
        std::strtod(token.c_str(), &end);
        return end != nullptr && *end == '\0';
    }

    bool isConstant(const std::string& token) {
        return token == "e" || token == "pi";
    }

    bool isOperator(const std::string& token) {
        return token == "+" || token == "-" || token == "*" || token == "/" || token == "^";
    }

    int precedence(const std::string& op) {
        if (op == "+" || op == "-") return 1;
        if (op == "*" || op == "/") return 2;
        if (op == "^") return 3;
        return 0;
    }

    double evaluatePostfix(std::queue<std::string>& postfix) {
        std::stack<double> evalStack;
        while (!postfix.empty()) {
            std::string token = postfix.front();
            postfix.pop();

            if (isNumber(token)) {
                evalStack.push(std::stod(token));
            } else if (isConstant(token)) {
                if (token == "e") {
                    evalStack.push(M_E);
                } else if (token == "pi") {
                    evalStack.push(M_PI);
                }
            } else if (isOperator(token)) {
                double right = evalStack.top(); evalStack.pop();
                double left = evalStack.top(); evalStack.pop();
                if (token == "+") {
                    evalStack.push(left + right);
                } else if (token == "-") {
                    evalStack.push(left - right);
                } else if (token == "*") {
                    evalStack.push(left * right);
                } else if (token == "/") {
                    evalStack.push(left / right);
                } else if (token == "^") {
                    evalStack.push(std::pow(left, right));
                }
            }
        }
        return evalStack.top();
    }
};

class BitwiseOperators {
    public:
    BitwiseOperators() {}
    void printBinary(int n) {
        for (int i = 31; i >= 0; --i) {
            std::cout << ((n >> i) & 1);
            if (i % 4 == 0) std::cout << ' ';
        }
        std::cout << std::endl;
    }
    int bitwiseAnd(int a, int b) {
        return a & b;
    }
    int bitwiseOr(int a, int b) {
        return a | b;
    }
    int bitwiseXor(int a, int b) {
        return a ^ b;
    }
    int bitwiseNot(int a) {
        return ~a;
    }
};

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

class Differentiation {
    public:
    std::string differentiateProduct(const std::string& term) {
        std::regex productPattern(R"((.+)\*(.+))");
        std::smatch match;
        if (std::regex_match(term, match, productPattern)) {
            std::string u = match[1].str();
            std::string v = match[2].str();
            return differentiateTerm(u) + "*" + v + " + " + u + "*" + differentiateTerm(v);
        }
        return "0";
    }
    std::string differentiateQuotient(const std::string& term) {
        std::regex quotientPattern(R"((.+)/(.+))");
        std::smatch match;
        if (std::regex_match(term, match, quotientPattern)) {
            std::string u = match[1].str();
            std::string v = match[2].str();
            return "(" + differentiateTerm(u) + "*" + v + " - " + u + "*" + differentiateTerm(v) + ")/(" + v + "^2)";
        }
        return "0";
    }
    std::string differentiateTerm(const std::string& term) {
        std::regex polynomialPattern(R"(([-+]?\d*\.?\d*)x\^([-+]?\d*\.?\d+))");
        std::regex linearPattern(R"(([-+]?\d*\.?\d*)x)");
        std::regex trigPattern(R"((sin|cos|tan|csc|sec|cot)\((x)\))");
        std::regex logPattern(R"(ln\((x)\))");
        std::regex clogPattern(R"(log\((x)\))");
        std::regex sqrtPattern(R"(sqrt\((x)\))");
        std::regex expPattern(R"((e)\^((x)))");
        std::regex axPattern(R"(([a-zA-Z]+|\d*\.?\d*)\^x)");
        std::regex constantPattern(R"((pi|e|\d+\.?\d*))");
        std::smatch match;
        try {
            if (std::regex_match(term, match, polynomialPattern)) {
                double coefficient = match[1].str().empty() || match[1].str() == "+" ? 1 : (match[1].str() == "-" ? -1 : std::stod(match[1].str()));
                double power = std::stod(match[2].str());
                double newCoefficient = coefficient * power;
                double newPower = power - 1;
                std::ostringstream oss;
                oss << std::fixed << std::setprecision(2);
                if (newPower == 0) {
                    oss << newCoefficient;
                } else if (newPower == 1) {
                    oss << newCoefficient << "x";
                } else {
                    oss << newCoefficient << "x^" << newPower;
                }
                return oss.str();
            } else if (std::regex_match(term, match, linearPattern)) {
                double coefficient = match[1].str().empty() || match[1].str() == "+" ? 1 : (match[1].str() == "-" ? -1 : std::stod(match[1].str()));
                std::ostringstream oss;
                oss << std::fixed << std::setprecision(2) << coefficient;
                return oss.str();
            } else if (std::regex_match(term, match, trigPattern)) {
                std::string trigFunction = match[1].str();
                if (trigFunction == "sin") {
                    return "cos(x)";
                } else if (trigFunction == "cos") {
                    return "-sin(x)";
                } else if (trigFunction == "tan") {
                    return "sec^2(x)";
                } else if (trigFunction == "csc") {
                    return "-csc(x)cot(x)";
                } else if (trigFunction == "sec") {
                    return "sec(x)tan(x)";
                } else if (trigFunction == "cot") {
                    return "-csc^2(x)";
                }
            } else if (std::regex_match(term, match, logPattern)) {
                return "1/x";
            } else if (std::regex_match(term, match, clogPattern)) {
                return "1/(x * log(10))";
            } else if (std::regex_match(term, match, sqrtPattern)) {
                return "1/(2*sqrt(x))";
            } else if (std::regex_match(term, match, expPattern)) {
                return "e^x";
            } else if (std::regex_match(term, match, axPattern)) {
                std::string base = match[1].str();
                std::ostringstream oss;
                oss << std::fixed << std::setprecision(2);
                oss << base << "^x * log(" << base << ")";
                return oss.str();
            } else if (std::regex_match(term, match, constantPattern)) {
                return "0";
            } else if (term.find('*') != std::string::npos) {
                return differentiateProduct(term);
            } else if (term.find('/') != std::string::npos) {
                return differentiateQuotient(term);
            }
        } catch (const std::exception& e) {
            std::cerr << "Error differentiating term '" << term << "': " << e.what() << std::endl;
            return "0";
        }
        return "0";
    }
    std::string differentiate(const std::string& expression) {
        std::string expr = std::regex_replace(expression, std::regex("\\s+"), "");
        std::vector<std::string> terms;
        std::string term;
        std::istringstream stream(expr);
        while (std::getline(stream, term, '+')) {
            size_t pos = 0;
            while ((pos = term.find('-')) != std::string::npos) {
                std::string subTerm = term.substr(0, pos);
                if (!subTerm.empty()) {
                    terms.push_back(subTerm);
                }
                term = term.substr(pos + 1);
                if (!term.empty() && term[0] != '-') {
                    term = "-" + term;
                }
            }
            if (!term.empty()) {
                terms.push_back(term);
            }
        }
        std::vector<std::string> differentiatedTerms;
        for (const auto& term : terms) {
            differentiatedTerms.push_back(differentiateTerm(term));
        }
        std::string result;
        for (size_t i = 0; i < differentiatedTerms.size(); ++i) {
            if (i > 0 && !differentiatedTerms[i].empty() && differentiatedTerms[i][0] != '-') {
                result += " + ";
            } else if (i > 0) {
                result += " ";
            }
            result += differentiatedTerms[i];
        }
        return result;
    }
};

class EquationSolver {
public:
    double solveLinearEquation(double a, double b) {
        if (a == 0) {
            throw std::invalid_argument("Invalid linear equation: coefficient of x is zero.");
        }
        return -b / a;
    }
    std::pair<std::pair<double, double>, std::pair<double, double>> solveQuadraticEquation(double a, double b, double c) {
        if (a == 0) {
            throw std::invalid_argument("Invalid quadratic equation: coefficient of x^2 is zero.");
        }

        double discriminant = b * b - 4 * a * c;
        double realPart = -b / (2 * a);
        double imaginaryPart = 0;

        if (discriminant >= 0) {
            double sqrtDiscriminant = sqrt(discriminant);
            double root1 = (realPart + sqrtDiscriminant / (2 * a));
            double root2 = (realPart - sqrtDiscriminant / (2 * a));
            return std::make_pair(std::make_pair(root1, 0), std::make_pair(root2, 0));
        } else {
            imaginaryPart = sqrt(-discriminant) / (2 * a);
            return std::make_pair(std::make_pair(realPart, imaginaryPart), std::make_pair(realPart, -imaginaryPart));
        }
    }

    std::tuple<std::pair<double, double>, std::pair<double, double>, std::pair<double, double>> solveCubicEquation(double a, double b, double c, double d) {
        if (a == 0) {
            throw std::invalid_argument("Invalid cubic equation: coefficient of x^3 is zero.");
        }

        // Normalize the coefficients
        b /= a;
        c /= a;
        d /= a;

        double p = (3 * c - b * b) / 3.0;
        double q = (2 * b * b * b - 9 * b * c + 27 * d) / 27.0;
        double delta = q * q / 4 + p * p * p / 27;

        std::pair<double, double> root1, root2, root3;

        if (delta >= 0) {
            double u = std::cbrt(-q / 2 + std::sqrt(delta));
            double v = std::cbrt(-q / 2 - std::sqrt(delta));
            root1 = {u + v - b / 3, 0};
            root2 = {-(u + v) / 2 - b / 3, std::sqrt(3) * (u - v) / 2};
            root3 = {-(u + v) / 2 - b / 3, -std::sqrt(3) * (u - v) / 2};
        } else {
            double r = std::sqrt(-p * p * p / 27);
            double phi = std::acos(-q / (2 * r));
            root1 = {2 * std::cbrt(r) * std::cos(phi / 3) - b / 3, 0};
            root2 = {2 * std::cbrt(r) * std::cos((phi + 2 * M_PI) / 3) - b / 3, 0};
            root3 = {2 * std::cbrt(r) * std::cos((phi + 4 * M_PI) / 3) - b / 3, 0};
        }

        return std::make_tuple(root1, root2, root3);
    }
    std::tuple<std::pair<double, double>, std::pair<double, double>, std::pair<double, double>, std::pair<double, double>> solveFourthOrderEquation(double a, double b, double c, double d, double e) {
        if (a == 0) {
            throw std::invalid_argument("Invalid 4th order equation: coefficient of x^4 is zero.");
        }

        // Normalize the coefficients
        b /= a;
        c /= a;
        d /= a;
        e /= a;

        double alpha = -3 * b * b / 8 + c;
        double beta = b * b * b / 8 - b * c / 2 + d;
        double gamma = -3 * b * b * b * b / 256 + b * b * c / 16 - b * d / 4 + e;

        std::pair<double, double> root1, root2, root3, root4;

        if (beta == 0) {
            double delta0 = alpha * alpha - 4 * gamma;
            if (delta0 >= 0) {
                root1 = {(-alpha + std::sqrt(delta0)) / 2 - b / 4, 0};
                root2 = {(-alpha - std::sqrt(delta0)) / 2 - b / 4, 0};
                root3 = {(alpha + std::sqrt(delta0)) / 2 - b / 4, 0};
                root4 = {(alpha - std::sqrt(delta0)) / 2 - b / 4, 0};
            } else {
                root1 = {(-alpha) / 2 - b / 4, std::sqrt(-delta0) / 2};
                root2 = {(-alpha) / 2 - b / 4, -std::sqrt(-delta0) / 2};
                root3 = {(alpha) / 2 - b / 4, std::sqrt(-delta0) / 2};
                root4 = {(alpha) / 2 - b / 4, -std::sqrt(-delta0) / 2};
            }
        } else {
            double P = -alpha * alpha / 12 - gamma;
            double Q = -alpha * alpha * alpha / 108 + alpha * gamma / 3 - beta * beta / 8;
            double R = -Q / 2 + std::sqrt(Q * Q / 4 + P * P * P / 27);

            double U = std::cbrt(R);
            double y = -5 * alpha / 6 - U;
            if (U != 0) y += P / (3 * U);

            double W = std::sqrt(alpha + 2 * y);

            double delta1 = -3 * alpha - 2 * y + 2 * beta / W;
            double delta2 = -3 * alpha - 2 * y - 2 * beta / W;

            if (delta1 >= 0) {
                root1 = {(-b / 4 + W / 2 + std::sqrt(delta1) / 2), 0};
                root2 = {(-b / 4 + W / 2 - std::sqrt(delta1) / 2), 0};
            } else {
                root1 = {(-b / 4 + W / 2), std::sqrt(-delta1) / 2};
                root2 = {(-b / 4 + W / 2), -std::sqrt(-delta1) / 2};
            }

            if (delta2 >= 0) {
                root3 = {(-b / 4 - W / 2 + std::sqrt(delta2) / 2), 0};
                root4 = {(-b / 4 - W / 2 - std::sqrt(delta2) / 2), 0};
            } else {
                root3 = {(-b / 4 - W / 2), std::sqrt(-delta2) / 2};
                root4 = {(-b / 4 - W / 2), -std::sqrt(-delta2) / 2};
            }
        }

        return std::make_tuple(root1, root2, root3, root4);
    }
};

class HyperbolicFunctions {
private:
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
    HyperbolicFunctions() {}
    
    void precompute_factorials(std::vector<long double>& factorials, int limit) {
        factorials[0] = 1;
        for (int i = 1; i <= limit; ++i) {
            factorials[i] = factorials[i - 1] * i;
        }
    }

    // Function to compute arsinh using the Taylor series
    long double arcsinh(long double z, int terms = 850) {
        std::vector<long double> factorials(2 * terms);
        precompute_factorials(factorials, 2 * terms - 1);

        long double result = 0;
        long double z_pow = z; // z^(2n+1)
        for (int n = 0; n < terms; ++n) {
            long double numerator = std::pow(-1, n) * factorials[2 * n];
            long double denominator = std::pow(4, n) * std::pow(factorials[n], 2) * (2 * n + 1);
            long double term = (numerator / denominator) * z_pow;
            result += term;
            z_pow *= z * z; // Update z^(2n+1) to z^(2(n+1)+1)
        }
        return result;
    }

    // Function to compute arcosh using the logarithmic definition
    long double arccosh(long double z) {
        return std::log(z + std::sqrt(z * z - 1));
    }

    // Function to compute artanh using the Taylor series
    long double arctanh(long double z, int terms = 850) {
        long double result = 0;
        long double z_pow = z; // z^(2n+1)
        for (int n = 0; n < terms; ++n) {
            long double term = z_pow / (2 * n + 1);
            result += term;
            z_pow *= z * z; // Update z^(2n+1) to z^(2(n+1)+1)
        }
        return result;
    }

    // Function to compute arsech using the logarithmic definition
    long double arcsech(long double z) {
        return std::log((1 + std::sqrt(1 - z * z)) / z);
    }

    // Function to compute arcsch using the logarithmic definition
    long double arccsch(long double z) {
        return std::log(1 / z + std::sqrt(1 / (z * z) + 1));
    }

    // Function to compute arcoth using the logarithmic definition
    long double arccoth(long double z) {
        return 0.5 * std::log((z + 1) / (z - 1));
    }

    double sinh(double x) const {
        return (exp(x) - exp(-x)) / 2;
    }

    double cosh(double x) const {
        return (exp(x) + exp(-x)) / 2;
    }

    double tanh(double x) const {
        return sinh(x) / cosh(x);
    }

    double csch(double x) const {
        if (x == 0) throw std::invalid_argument("csch(x) is undefined for x = 0");
        return 1 / sinh(x);
    }

    double sech(double x) const {
        return 1 / cosh(x);
    }

    double coth(double x) const {
        if (x == 0) throw std::invalid_argument("coth(x) is undefined for x = 0");
        return cosh(x) / sinh(x);
    }
};

class Integration {
public:
    struct Term {
        std::string expression;
        std::string integral;
    };

    static std::string integrate(const std::string &expression) {
        std::regex term_regex(R"((\-?\d*\.?\d*\*?x\^\-?\d*\.?\d+|\-?\d*\.?\d*\*?x|\-?\d*\.?\d+|sin\(x\)|cos\(x\)|tan\(x\)|sec\(x\)|csc\(x\)|cot\(x\)|e\^x|log\(x\)|ln\(x\)|sqrt\(x\)))");
        std::smatch match;
        std::vector<Term> terms;
        std::string::const_iterator searchStart(expression.cbegin());

        while (std::regex_search(searchStart, expression.cend(), match, term_regex)) {
            std::string term = match[0];
            terms.push_back({term, integrate_term(term)});
            searchStart = match.suffix().first;
        }

        std::string result;
        for (const auto &term : terms) {
            if (!result.empty() && term.integral[0] != '-')
                result += " + ";
            result += term.integral;
        }

        return result + " + C";
    }

private:
    static std::string integrate_term(const std::string &expression) {
        std::regex power_regex(R"((\-?\d*\.?\d*)\*?x\^(\-?\d*\.?\d+))");
        std::regex x_regex(R"((\-?\d*\.?\d*)\*?x)");
        std::regex constant_regex(R"((\-?\d*\.?\d+))");
        std::regex trig_regex(R"((sin|cos|tan|sec|csc|cot)\(x\))");
        std::regex exp_regex(R"(e\^x)");
        std::regex log_regex(R"(log\(x\))");
        std::regex ln_regex(R"(ln\(x\))");
        std::regex sqrt_regex(R"(sqrt\(x\))");
        std::smatch match;

        if (std::regex_match(expression, match, power_regex)) {
            double coefficient = match[1].str().empty() ? 1 : std::stod(match[1].str());
            double exponent = std::stod(match[2].str());
            double new_exponent = exponent + 1;
            double new_coefficient = coefficient / new_exponent;
            return std::to_string(new_coefficient) + "x^" + std::to_string(new_exponent);
        }
        if (std::regex_match(expression, match, x_regex)) {
            double coefficient = match[1].str().empty() ? 1 : std::stod(match[1].str());
            return std::to_string(coefficient / 2) + "x^2";
        }
        if (std::regex_match(expression, match, constant_regex)) {
            double constant = std::stod(match[0].str());
            return std::to_string(constant) + "x";
        }
        if (std::regex_match(expression, match, trig_regex)) {
            std::string trig_function = match[1].str();
            if (trig_function == "sin") {
                return "-cos(x)";
            } else if (trig_function == "cos") {
                return "sin(x)";
            } else if (trig_function == "tan") {
                return "-log|cos(x)|";
            } else if (trig_function == "sec") {
                return "log|sec(x) + tan(x)|";
            } else if (trig_function == "csc") {
                return "-log|csc(x) + cot(x)|";
            } else if (trig_function == "cot") {
                return "log|sin(x)|";
            }
        }
        if (std::regex_match(expression, match, exp_regex)) {
            return "e^x";
        }
        if (std::regex_match(expression, match, log_regex)) {
            return "x*log(x) - x";
        }
        if (std::regex_match(expression, match, ln_regex)) {
            return "x*ln(x) - x";
        }
        if (std::regex_match(expression, match, sqrt_regex)) {
            return "2/3*x^(3/2)";
        }
        return "Unable to integrate the expression.";
    }
};

class LogarithmCalculator {
public:
    double calculateLog(double x) {
        if (x <= 0) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        if (x == 1) {
            return 0.0;
        }
        bool isFractional = false;
        if (x < 1) {
            isFractional = true;
            x = 1 / x;
        }
        double result = 0.0;
        double term = (x - 1) / (x + 1);
        double term_squared = term * term;
        double current_term = term;
        for (int n = 1; n <= 10000; n += 2) {
            result += current_term / n;
            current_term *= term_squared;
        }
        result *= 2.0;
        return isFractional ? -result : result;
    }
    double calculateLog10(double x) {
        double ln_x = calculateLog(x);
        double ln_10 = 2.302585092994045684017991454684364207601101488628772976033;
        return ln_x / ln_10;
    }
};

class NumberSystem {
public:
    std::string decimalToBinary(int decimal) const {
        if (decimal == 0) return "0";
        std::string binary;
        while (decimal > 0) {
            binary.insert(binary.begin(), (decimal % 2) + '0');
            decimal /= 2;
        }
        return binary;
    }

    std::string decimalToOctal(int decimal) const {
        if (decimal == 0) return "0";
        std::string octal;
        while (decimal > 0) {
            octal.insert(octal.begin(), (decimal % 8) + '0');
            decimal /= 8;
        }
        return octal;
    }

    std::string decimalToHexadecimal(int decimal) const {
        if (decimal == 0) return "0";
        std::string hexadecimal;
        while (decimal > 0) {
            int remainder = decimal % 16;
            hexadecimal.insert(hexadecimal.begin(), (remainder < 10) ? (remainder + '0') : (remainder - 10 + 'A'));
            decimal /= 16;
        }
        return hexadecimal;
    }

    std::string binaryToDecimal(const std::string& binary) const {
        int decimal = 0;
        int power = 0;
        for (int i = binary.size() - 1; i >= 0; --i) {
            if (binary[i] == '1') {
                decimal += std::pow(2, power);
            }
            power++;
        }
        return std::to_string(decimal);
    }

    std::string binaryToOctal(const std::string& binary) const {
        std::string paddedBinary = binary;
        while (paddedBinary.size() % 3 != 0) {
            paddedBinary.insert(paddedBinary.begin(), '0');
        }
        std::string octal;
        for (size_t i = 0; i < paddedBinary.size(); i += 3) {
            std::string chunk = paddedBinary.substr(i, 3);
            int value = std::stoi(binaryToDecimal(chunk));
            octal += std::to_string(value);
        }
        return octal;
    }

    std::string binaryToHexadecimal(const std::string& binary) const {
        std::string paddedBinary = binary;
        while (paddedBinary.size() % 4 != 0) {
            paddedBinary.insert(paddedBinary.begin(), '0');
        }
        std::string hexadecimal;
        for (size_t i = 0; i < paddedBinary.size(); i += 4) {
            std::string chunk = paddedBinary.substr(i, 4);
            int value = std::stoi(binaryToDecimal(chunk));
            hexadecimal += (value < 10) ? (value + '0') : (value - 10 + 'A');
        }
        return hexadecimal;
    }

    std::string octalToBinary(const std::string& octal) const {
        std::string binary;
        for (char digit : octal) {
            int num = digit - '0';
            std::string binPart = decimalToBinary(num);
            while (binPart.size() < 3) {
                binPart.insert(binPart.begin(), '0');
            }
            binary += binPart;
        }
        size_t firstNonZero = binary.find_first_not_of('0');
        return firstNonZero != std::string::npos ? binary.substr(firstNonZero) : "0";
    }

    std::string octalToDecimal(const std::string& octal) const {
        int decimal = 0;
        int power = 0;
        for (int i = octal.size() - 1; i >= 0; --i) {
            decimal += (octal[i] - '0') * std::pow(8, power);
            power++;
        }
        return std::to_string(decimal);
    }
    std::string octalToHexadecimal(const std::string& octal) const {
        std::string binary = octalToBinary(octal);
        return binaryToHexadecimal(binary);
    }

    std::string hexadecimalToBinary(const std::string& hexadecimal) const {
        std::string binary;
        for (char digit : hexadecimal) {
            int num = 0;
            if (digit >= '0' && digit <= '9') {
                num = digit - '0';
            } else if (digit >= 'A' && digit <= 'F') {
                num = digit - 'A' + 10;
            } else if (digit >= 'a' && digit <= 'f') {
                num = digit - 'a' + 10;
            } else {
                return "Invalid hexadecimal digit: " + std::to_string(digit);
            }
            std::string binPart = decimalToBinary(num);
            while (binPart.size() < 4) {
                binPart.insert(binPart.begin(), '0');
            }
            binary += binPart;
        }
        size_t firstNonZero = binary.find_first_not_of('0');
        return firstNonZero != std::string::npos ? binary.substr(firstNonZero) : "0";
    }

    std::string hexadecimalToDecimal(const std::string& hexadecimal) const {
        int decimal = 0;
        int power = 0;
        for (int i = hexadecimal.size() - 1; i >= 0; --i) {
            int value = 0;
            if (hexadecimal[i] >= '0' && hexadecimal[i] <= '9') {
                value = hexadecimal[i] - '0';
            } else if (hexadecimal[i] >= 'A' && hexadecimal[i] <= 'F') {
                value = hexadecimal[i] - 'A' + 10;
            } else if (hexadecimal[i] >= 'a' && hexadecimal[i] <= 'f') {
                value = hexadecimal[i] - 'a' + 10;
            } else {
                return "Invalid hexadecimal digit: " + std::to_string(hexadecimal[i]);
            }
            decimal += value * std::pow(16, power);
            power++;
        }
        return std::to_string(decimal);
    }
    std::string hexadecimalToOctal(const std::string& hexadecimal) const {
        std::string binary = hexadecimalToBinary(hexadecimal);
        return binaryToOctal(binary);
    }
};

class Trigonometry {
public:
   double sine(double x) {
        x = degreesToRadians(x);
        double term = x;
        double sum = 0;
        for (int n = 0; n < 10; ++n) {
            sum += term;
            term *= -x * x / (2 * n + 2) / (2 * n + 3);
        }
        return sum;
    }

    double cosine(double x) {
        x = degreesToRadians(x);
        double term = 1;
        double sum = 0;
        for (int n = 0; n < 10; ++n) {
            sum += term;
            term *= -x * x / (2 * n + 1) / (2 * n + 2);
        }
        return sum;
    }

    double tangent(double x) {
        return sine(x) / cosine(x);
    }

    double secant(double x) {
        return 1.0/ cosine(x);
    }

    double cosecant(double x) {
        return 1.0/sine(x);
    }

    double cotangent(double x) {
        return 1.0/tangent(x);
    }
    // Function to compute arcsin using the Taylor series
    long double arcsine(long double z, int terms = 850) {
        std::vector<long double> factorials(2 * terms);
        precompute_factorials(factorials, 2 * terms - 1);
        long double result = 0;
        long double z_pow = z;
        for (int n = 0; n < terms; ++n) {
            long double numerator = factorials[2 * n];
            long double denominator = std::pow(2, 2 * n) * std::pow(factorials[n], 2) * (2 * n + 1);
            long double term = (numerator / denominator) * z_pow;
            result += term;
            z_pow *= z * z;
        }
        return result;
    }

    // Function to compute arccos using the Taylor series
    long double arccosine(long double z, int terms = 850) {
        return (M_PI / 2) - arcsine(z, terms);
    }

    // Function to compute arctan using the Taylor series
    long double arctangent(long double z, int terms = 850) {
        long double result = 0;
        long double z_pow = z; // z^(2n+1)
        for (int n = 0; n < terms; ++n) {
            long double term = (std::pow(-1, n) * z_pow) / (2 * n + 1);
            result += term;
            z_pow *= z * z; // Update z^(2n+1) to z^(2(n+1)+1)
        }
        return result;
    }

    // Function to compute arcsec using the Taylor series
    long double arcsecant(long double z, int terms = 850) {
        std::vector<long double> factorials(2 * terms);
        precompute_factorials(factorials, 2 * terms - 1);

        long double result = 0;
        long double z_pow = 1 / z; // (1/z)^(2n+1)
        for (int n = 0; n < terms; ++n) {
            long double numerator = factorials[2 * n];
            long double denominator = std::pow(2, 2 * n) * std::pow(factorials[n], 2) * (2 * n + 1);
            long double term = (numerator / denominator) * z_pow;
            result += term;
            z_pow /= z * z; // Update (1/z)^(2n+1) to (1/z)^(2(n+1)+1)
        }
        return result;
    }

    // Function to compute arccsc using the Taylor series
    long double arccosecant(long double z, int terms = 850) {
        return (M_PI / 2) - arcsecant(z, terms);
    }

    // Function to compute arccot using the Taylor series
    long double arccotangent(long double z, int terms = 850) {
        return (M_PI / 2) - arctangent(z, terms);
    }
private:
    double degreesToRadians(double degrees) const {
        return degrees * M_PI / 180.0;
    }
    void precompute_factorials(std::vector<long double>& factorials, int limit) {
        factorials[0] = 1;
        for (int i = 1; i <= limit; ++i) {
            factorials[i] = factorials[i - 1] * i;
        }
    }
};

class Roots {
public:
    double customAbs(double num) {
        if (num < 0) {
            return -num;
        }
        return num;
    }
    double power(double base, double exponent) {
        double result = 1;
        for (int i = 0; i < exponent; ++i) {
            result *= base;
        }
        return result;
    }
    double squareRoot(double num) {
        double x = num;
        double root;
        while (true) {
            root = 0.5 * (x + num / x);
            if (customAbs(root - x) < 0.0001) {
                break;
            }
            x = root;
        }
        return root;
    }
    double cubeRoot(double num) {
        double x = num;
        double root;
        while (true) {
            root = (2 * x + num / (x * x)) / 3;
            if (customAbs(root - x) < 0.0001) {
                break;
            }
            x = root;
        }
        return root;
    }
};


#endif