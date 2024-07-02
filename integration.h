#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <regex>

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

#endif // INTEGRATION_H
