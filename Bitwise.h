#ifndef EQUATION_SOLVER_H
#define EQUATION_SOLVER_H

#include <iostream>
#include <tuple>

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
    void display() {
        int choice;
        int num1, num2;   
        std::cout << std::endl;

        std::cout << "1. AND operation" << std::endl;
        std::cout << "2. OR operation" << std::endl;
        std::cout << "3. NOT operation" << std::endl;
        std::cout << "4. XOR operation" << std::endl;
        std::cout << "Enter choice (1 - 4): ";
        std::cin >> choice;
        if (choice > 4 || choice < 1) {
            std::cout << "Invalid choice";
        } else {
            std::cout << "Enter first integer: ";
            std::cin >> num1;
            std::cout << "Enter second integer: ";
            std::cin >> num2;
            switch(choice) {
                case 1:
                   { int andResult = bitwiseAnd(num1, num2);
                    std::cout << "\nResults:\n";
                    std::cout << "Bitwise AND (num1 | num2): " << andResult << std::endl;
                    std::cout << "Binary: ";
                    printBinary(andResult);
                    break;}
                case 2:
                    {int orResult = bitwiseOr(num1, num2);
                    std::cout << "\nResults:\n";
                    std::cout << "Bitwise OR (num1 | num2): " << orResult << std::endl;
                    std::cout << "Binary: ";
                    printBinary(orResult);
                    break;}
                case 3:
                    {int notResult1 = bitwiseNot(num1);
                    int notResult2 = bitwiseNot(num2);
                    std::cout << "Bitwise NOT (~num1): " << notResult1 << std::endl;
                    std::cout << "Binary: ";
                    printBinary(notResult1);

                    std::cout << "Bitwise NOT (~num2): " << notResult2 << std::endl;
                    std::cout << "Binary: ";
                    printBinary(notResult2);
                    break;}
                case 4:
                    {int xorResult = bitwiseXor(num1, num2);
                    std::cout << "Bitwise XOR (num1 ^ num2): " << xorResult << std::endl;
                    std::cout << "Binary: ";
                    printBinary(xorResult);
                    break;}
            }

        }
    }
};


#endif