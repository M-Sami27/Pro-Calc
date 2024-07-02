#ifndef DIFFERENTIATION_H
#define DIFFERENTIATION_H

#include <iostream>
#include <stdexcept>
#include <regex>
#include <sstream>
#include <algorithm>
#include <limits>
#include <iomanip>


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
    void display() {
        std::string expression;
        std::cout << "Enter the function to differentiate (terms separated by '+' or '-'): ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, expression);
        try {
            std::string derivative = differentiate(expression);
            std::cout << "The derivative of " << expression << " is " << derivative << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error differentiating expression: " << e.what() << std::endl;
        }
        return;
    }
};

#endif
