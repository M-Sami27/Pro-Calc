#ifndef NUMBER_SYSTEM_H
#define NUMBER_SYSTEM_H

#include <iostream>
#include <string>

class NumberSystem {
public:
    int choice;
    NumberSystem(): choice(0) {}
    std::string decimalToBinary(int decimal) const {
        if (decimal == 0)
            return "0";
        std::string binary;
        while (decimal > 0) {
            binary.insert(binary.begin(), (decimal % 2) + '0');
            decimal /= 2;
        }
        return binary;
    }
    int binaryToDecimal(const std::string &binary) const {
        int decimal = 0;
        int power = 0;
        for (int i = binary.size() - 1; i >= 0; --i)
        {
            decimal += (binary[i] - '0') * pow(2, power);
            power++;
        }
        return decimal;
    }
    std::string decimalToOctal(int decimal) const {
        if (decimal == 0)
            return "0";
        std::string octal;
        while (decimal > 0)
        {
            octal.insert(octal.begin(), (decimal % 8) + '0');
            decimal /= 8;
        }
        return octal;
    }
    int octalToDecimal(const std::string &octal) const {
        int decimal = 0;
        int power = 0;
        for (int i = octal.size() - 1; i >= 0; --i)
        {
            decimal += (octal[i] - '0') * pow(8, power);
            power++;
        }
        return decimal;
    }
    std::string decimalToHexadecimal(int decimal) const {
        if (decimal == 0)
            return "0";
        std::string hexadecimal;
        while (decimal > 0)
        {
            int remainder = decimal % 16;
            hexadecimal.insert(hexadecimal.begin(), (remainder < 10) ? (remainder + '0') : (remainder - 10 + 'A'));
            decimal /= 16;
        }
        return hexadecimal;
    }
    int hexadecimalToDecimal(const std::string &hexadecimal) const {
        int decimal = 0;
        int power = 0;
        for (int i = hexadecimal.size() - 1; i >= 0; --i)
        {
            if (hexadecimal[i] >= '0' && hexadecimal[i] <= '9')
            {
                decimal += (hexadecimal[i] - '0') * pow(16, power);
            }
            else if (hexadecimal[i] >= 'A' && hexadecimal[i] <= 'F')
            {
                decimal += (hexadecimal[i] - 'A' + 10) * pow(16, power);
            }
            else if (hexadecimal[i] >= 'a' && hexadecimal[i] <= 'f')
            {
                decimal += (hexadecimal[i] - 'a' + 10) * pow(16, power);
            }
            else
            {
                std::cerr << "Invalid hexadecimal digit: " << hexadecimal[i] << std::endl;
                return 0;
            }
            power++;
        }
        return decimal;
    }
    std::string binaryToOctal(const std::string &binary) const {
        std::string octal;
        int numBits = binary.length();
        int numDigits = (numBits % 3 == 0) ? numBits / 3 : (numBits / 3) + 1;
        std::string paddedBinary = binary;
        if (numBits % 3 != 0)
        {
            paddedBinary = std::string(3 - (numBits % 3), '0') + paddedBinary;
        }
        for (int i = 0; i < numDigits; ++i)
        {
            std::string chunk = paddedBinary.substr(i * 3, 3);
            octal += std::to_string(binaryToDecimal(chunk));
        }
        return octal;
    }
    std::string octalToBinary(const std::string &octal) const {
        std::string binary;
        for (char digit : octal)
        {
            int num = digit - '0';
            binary += decimalToBinary(num);
        }
        return binary;
    }
    std::string binaryToHexadecimal(const std::string &binary) const {
        std::string hexadecimal;
        int numBits = binary.length();
        int numDigits = (numBits % 4 == 0) ? numBits / 4 : (numBits / 4) + 1;
        std::string paddedBinary = binary;
        if (numBits % 4 != 0)
        {
            paddedBinary = std::string(4 - (numBits % 4), '0') + paddedBinary;
        }
        for (int i = 0; i < numDigits; ++i)
        {
            std::string chunk = paddedBinary.substr(i * 4, 4);
            hexadecimal += decimalToHexadecimal(binaryToDecimal(chunk));
        }
        return hexadecimal;
    }
    std::string hexadecimalToBinary(const std::string &hexadecimal) const {
        std::string binary;
        for (char digit : hexadecimal)
        {
            if (digit >= '0' && digit <= '9')
            {
                int num = digit - '0';
                binary += decimalToBinary(num);
            }
            else if (digit >= 'A' && digit <= 'F')
            {
                int num = digit - 'A' + 10;
                binary += decimalToBinary(num);
            }
            else if (digit >= 'a' && digit <= 'f')
            {
                int num = digit - 'a' + 10;
                binary += decimalToBinary(num);
            }
            else
            {
                std::cerr << "Invalid hexadecimal digit: " << digit << std::endl;
                return "";
            }
        }
        return binary;
    }
    std::string octalToHexadecimal(const std::string &octal) const {
        std::string binary = octalToBinary(octal);
        return binaryToHexadecimal(binary);
    }
    std::string hexadecimalToOctal(const std::string &hexadecimal) const {
        std::string binary = hexadecimalToBinary(hexadecimal);
        return binaryToOctal(binary);
    }
    void display() {
        NumberSystem calc;

        std::cout << "Choose the function you want to calculate:\n";
        std::cout << "1. Decimal to Binary\n";
        std::cout << "2. Binary to Decimal\n";
        std::cout << "3. Decimal to Octal\n";
        std::cout << "4. Octal to Decimal\n";
        std::cout << "5. Decimal to Hexadecimal\n";
        std::cout << "6. Hexadecimal to Decimal\n";
        std::cout << "7. Binary to Octal\n";
        std::cout << "8. Octal to Binary\n";
        std::cout << "9. Binary to Hexadecimal\n";
        std::cout << "10. Hexadecimal to Binary\n";
        std::cout << "11. Octal to Hexadecimal\n";
        std::cout << "12. Hexadecimal to Octal\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        std::string number;

        switch (choice) {
            case 1:
                {std::cout << "Enter the decimal number: ";
                int decimal;
                std::cin >> decimal;
                std::cout << "Binary: " << calc.decimalToBinary(decimal) << std::endl;
                break;}
            case 2:
                {std::cout << "Enter the binary number: ";
                std::cin >> number;
                std::cout << "Decimal: " << calc.binaryToDecimal(number) << std::endl;
                break;}
            case 3:
                {int decimal;
                std::cout << "Enter the decimal number: ";
                std::cin >> decimal;
                std::cout << "Octal: " << calc.decimalToOctal(decimal) << std::endl;
                break;}
            case 4:
                {std::cout << "Enter the octal number: ";
                std::cin >> number;
                std::cout << "Decimal: " << calc.octalToDecimal(number) << std::endl;
                break;}
            case 5:
                {std::cout << "Enter the decimal number: ";
                int decimal;
                std::cin >> decimal;
                std::cout << "Hexadecimal: " << calc.decimalToHexadecimal(decimal) << std::endl;
                break;}
            case 6:
                {std::cout << "Enter the hexadecimal number: ";
                std::cin >> number;
                std::cout << "Decimal: " << calc.hexadecimalToDecimal(number) << std::endl;
                break;}
            case 7:
                {std::cout << "Enter the binary number: ";
                std::cin >> number;
                std::cout << "Octal: " << calc.binaryToOctal(number) << std::endl;
                break;}
            case 8:
                {std::cout << "Enter the octal number: ";
                std::cin >> number;
                std::cout << "Binary: " << calc.octalToBinary(number) << std::endl;
                break;}
            case 9:
                {std::cout << "Enter the binary number: ";
                std::cin >> number;
                std::cout << "Hexadecimal: " << calc.binaryToHexadecimal(number) << std::endl;
                break;}
            case 10:
                {std::cout << "Enter the hexadecimal number: ";
                std::cin >> number;
                std::cout << "Binary: " << calc.hexadecimalToBinary(number) << std::endl;
                break;}
            case 11:
                {std::cout << "Enter the octal number: ";
                std::cin >> number;
                std::cout << "Hexadecimal: " << calc.octalToHexadecimal(number) << std::endl;
                break;}
            case 12:
                {std::cout << "Enter the hexadecimal number: ";
                std::cin >> number;
                std::cout << "Octal: " << calc.hexadecimalToOctal(number) << std::endl;
                break;}
            default:
                std::cout << "Invalid choice.\n";
                break;
        }
    }
    std::string performConversion(int choice, int number) const {
        switch (choice) {
            case 1: return decimalToBinary(number);
            case 2: return std::to_string(binaryToDecimal(std::to_string(number)));
            case 3: return decimalToOctal(number);
            case 4: return std::to_string(octalToDecimal(std::to_string(number)));
            case 5: return decimalToHexadecimal(number);
            case 6: return std::to_string(hexadecimalToDecimal(std::to_string(number)));
            case 7: return binaryToOctal(std::to_string(number));
            case 8: return octalToBinary(std::to_string(number));
            case 9: return binaryToHexadecimal(std::to_string(number));
            case 10: return hexadecimalToBinary(std::to_string(number));
            case 11: return octalToHexadecimal(std::to_string(number));
            case 12: return hexadecimalToOctal(std::to_string(number));
            default: return "Invalid choice.";
        }
    }
};

#endif