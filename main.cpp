#include "include/raylib.h"
#include "include/differentiation.h"
#include "include/integration.h"
#include "include/Arithmetic.h"
#include "include/Trigonometry.h"
#include "include/Bitwise.h"
#include "include/EquationSolver.h"
#include "include/Hyperbolic.h"
#include "include/NumberSystem.h"
#include "include/combinatorics.h"
#include <iostream>
#include <tuple>
#include <cstring>

//backspace in integration
//no more than 1 decimal point

enum Screen {
    MAINSCREEN,
    BITWISESCREEN,
    ROOTSSCREEN,
    DIFFERENTIALSCREEN,
    INTEGRALSCREEN,
    NUMBERSYSTEMSCREEN
};

enum EquationType {
    NONE,
    LINEAR,
    QUADRATIC,
    CUBIC,
    QUARTIC
};

bool IsMouseOverButton(Rectangle button) {
    return CheckCollisionPointRec(GetMousePosition(), button);
}

void DrawButton(Rectangle button, const char *text) {
    DrawRectangleRec(button, LIGHTGRAY);
    DrawRectangleLinesEx(button, 2, DARKGRAY);
    DrawText(text, button.x + 10, button.y + 10, 20, DARKGRAY);
}

void HandleTextInput(char* buffer, int maxSize, bool active) {
    if (active) {
        int key = GetKeyPressed();
        while (key > 0) {
            if ((key >= 32) && (key <= 125) && (strlen(buffer) < (long long unsigned)maxSize)) {
                int len = strlen(buffer);
                buffer[len] = (char)key;
                buffer[len + 1] = '\0';
            }
            if (key == 259 && strlen(buffer) > 0) { // Handle backspace
                buffer[strlen(buffer) - 1] = '\0';
            }
            key = GetKeyPressed();
        }
    }
}

int main() {
    const int screenWidth = 900;
    const int screenHeight = 900;
    Screen currentScreen = Screen::MAINSCREEN;
    InitWindow(screenWidth, screenHeight, "Calculator");

    std::string input = "";
    std::string result = "";
    std::string diffResult = "";
    std::string integResult = "";
    std::string bitwiseresult = "";
    char buffer1[50] = "";
    char buffer2[50] = "";
    char coeff1[128] = "";
    char coeff2[128] = "";
    char coeff3[128] = "";
    char coeff4[128] = "";
    char coeff5[128] = "";
    char numbersysteminput[256] = { 0 };  
    bool numbersysteminputActive = true;
    bool activeTextBox1 = true;
    bool activeTextBox2 = false;
    bool activeTextBox3 = false;
    bool activeTextBox4 = false;
    bool activeTextBox5 = false; 
    std::string numSysResult = "";

    EquationType currentType = NONE;

    Rectangle buttons[16];
    const char *buttonLabels[16] = {
        "7", "8", "9", "/",
        "4", "5", "6", "*",
        "1", "2", "3", "-",
        "0", ".", "=", "+"
    };

    Rectangle sinButton = {400, 100, 140, 40};
    Rectangle cosButton = {400, 150, 140, 40};
    Rectangle tanButton = {400, 200, 140, 40};
    Rectangle cotButton = {400, 250, 140, 40};
    Rectangle cscButton = {400, 300, 140, 40};
    Rectangle secButton = {400, 350, 140, 40};

    Rectangle sinhButton = {600, 100, 140, 40};
    Rectangle coshButton = {600, 150, 140, 40};
    Rectangle tanhButton = {600, 200, 140, 40};
    Rectangle cothButton = {600, 250, 140, 40};
    Rectangle cschButton = {600, 300, 140, 40};
    Rectangle sechButton = {600, 350, 140, 40};

    Rectangle bitwiseButton = {10, 350, 170, 40};
    Rectangle differentiationButton = {10, 400, 170, 40};
    Rectangle integrationButton = {190, 400, 170, 40};
    
    Rectangle rootsButton = {10, 300, 170, 40};
    Rectangle clearButton = {190, 300, 170, 40};

    Rectangle AND = {10, 500, 140, 40};
    Rectangle OR = {165, 500, 140, 40};
    Rectangle NOT = {315, 500, 140, 40};
    Rectangle XOR = {470, 500, 140, 40};

    Rectangle decToBinaryButton = {10, 500, 140, 40};
    Rectangle decToOctalButton = {160, 500, 140, 40};
    Rectangle decToHexaButton = {310, 500, 140, 40};
    Rectangle binaryToOctalButton = {460, 500, 140, 40};
    Rectangle binaryToDecimalButton = {610, 500, 140, 40};
    Rectangle binaryToHexaButton = {760, 500, 140, 40};
    Rectangle octalToBinaryButton = {10, 600, 140, 40};
    Rectangle octalToDecimalButton = {160, 600, 140, 40};
    Rectangle octalToHexaButton = {310, 600, 140, 40};
    Rectangle hexaToBinaryButton = {460, 600, 140, 40};
    Rectangle hexaToOctalButton = {610, 600, 140, 40};
    Rectangle hexaToDecimalButton = {760, 600, 140, 40};

    Rectangle backButton = {10, 10, 140, 40};   

    Rectangle numberSystemButton = {190, 350, 170, 40}; 

    Rectangle factorialButton = {400, 400, 140, 40};
    Rectangle combinationsButton = {600, 400, 140, 40};
    Rectangle permutationsButton = {10, 450, 140, 40};

    float buttonWidth = 80;
    float buttonHeight = 40;

    Trigonometry trig;
    BitwiseOperators bitwise;
    EquationSolver solver;
    NumberSystem numSys;
    Combinatorics comb;
    

    for (int i = 0; i < 16; ++i)
    {
        buttons[i] = {10 + (i % 4) * (buttonWidth + 10), 100 + (i / 4) * (buttonHeight + 10), buttonWidth, buttonHeight};
    }
    while(!WindowShouldClose()) {
        if (currentScreen == Screen::MAINSCREEN) {
            for (int i = 0; i < 16; ++i) {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && IsMouseOverButton(buttons[i])) {
                    const char* label = buttonLabels[i];
                    if ((label[0] >= '0' && label[0] <= '9')) {
                        input += label;
                    } else if (label[0] == '.') {
                        input += ".";
                    } else if (label[0] == '=') {
                        try {

                            if (input.find("C") != std::string::npos) {
                                size_t cPos = input.find("C");
                                int n = std::stoi(input.substr(0, cPos));
                                int r = std::stoi(input.substr(cPos + 1));
                                result = std::to_string(comb.combinations(n, r));
                            } else if (input.find("P") != std::string::npos) {
                                size_t pPos = input.find("P");
                                int n = std::stoi(input.substr(0, pPos));
                                int r = std::stoi(input.substr(pPos + 1));
                                result = std::to_string(comb.permutations(n, r));
                            } else {
                                std::istringstream iss(input);
                                double a, b;
                                char op;
                                iss >> a >> op >> b;
                                Arithmetic<double> calc;
                                double calcResult;
                                switch (op) {
                                    case '+': calcResult = calc.add(a, b); break;
                                    case '-': calcResult = calc.subtract(a, b); break;
                                    case '*': calcResult = calc.multiply(a, b); break;
                                    case '/': calcResult = calc.divide(a, b); break;
                                    default: throw std::invalid_argument("Invalid operator");
                                }
                                result = std::to_string(calcResult);
                            }
                        } catch (const std::exception &e) {
                            result = e.what();
                        }
                    } else {
                        input += " ";
                        input += label;
                        input += " ";
                    }
                }
            }

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mousePoint = GetMousePosition();
                if (CheckCollisionPointRec(mousePoint, combinationsButton)) {
                    input += "C";
                } else if (CheckCollisionPointRec(mousePoint, permutationsButton)) {
                    input += "P";
                }
            }

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && IsMouseOverButton(sinButton)) {
                try {
                    double angle = std::stof(input);
                    result = std::to_string(trig.sine(angle));
                } catch (...) {
                    result = "Invalid input";
                }
            } else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && IsMouseOverButton(cosButton)) {
                try {
                    double angle = std::stof(input);
                    result = std::to_string(trig.cosine(angle));
                } catch (...) {
                    result = "Invalid input";
                }
            } else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && IsMouseOverButton(tanButton)) {
                try {
                    double angle = std::stof(input);
                    result = std::to_string(trig.tangent(angle));
                } catch (...) {
                    result = "Invalid input";
                }
            } else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && IsMouseOverButton(secButton)) {
                try {
                    double angle = std::stof(input);
                    result = std::to_string(trig.secant(angle));
                } catch (...) {
                    result = "Invalid input";
                }
            } else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && IsMouseOverButton(cscButton)) {
                try {
                    double angle = std::stof(input);
                    result = std::to_string(trig.cosecant(angle));
                } catch (...) {
                    result = "Invalid input";
                }
            } else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && IsMouseOverButton(cotButton)) {
                try {
                    double angle = std::stof(input);
                    result = std::to_string(trig.cotangent(angle));
                } catch (...) {
                    result = "Invalid input";
                }
            }

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && IsMouseOverButton(sinhButton)) {
                HyperbolicFunctions hyp(std::stof(input));
                try {
                    result = std::to_string(hyp.sinh());
                } catch (...) {
                    result = "Invalid input";
                }
            } else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && IsMouseOverButton(coshButton)) {
                HyperbolicFunctions hyp(std::stof(input));
                try {
                    result = std::to_string(hyp.cosh());
                } catch (...) {
                    result = "Invalid input";
                }
            } else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && IsMouseOverButton(tanhButton)) {
                HyperbolicFunctions hyp(std::stof(input));
                try {
                    result = std::to_string(hyp.tanh());
                } catch (...) {
                    result = "Invalid input";
                }
            } else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && IsMouseOverButton(sechButton)) {
                HyperbolicFunctions hyp(std::stof(input));
                try {
                    result = std::to_string(hyp.sech());
                } catch (...) {
                    result = "Invalid input";
                }
            } else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && IsMouseOverButton(cschButton)) {
                HyperbolicFunctions hyp(std::stof(input));
                try {
                    result = std::to_string(hyp.csch());
                } catch (...) {
                    result = "Invalid input";
                }
            } else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && IsMouseOverButton(cothButton)) {
                HyperbolicFunctions hyp(std::stof(input));
                try {
                    result = std::to_string(hyp.coth());
                } catch (...) {
                    result = "Invalid input";
                }
            }

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && IsMouseOverButton(clearButton)) {
                input = "";
                result = "";
            }

            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && IsMouseOverButton(factorialButton)) {
                try {
                    int temp = std::stoi(input);
                    result = std::to_string(comb.factorial(temp));
                } catch (...) {
                    result = "Invalid input";
                }
            }

            if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && IsMouseOverButton(bitwiseButton)) {
                currentScreen = Screen::BITWISESCREEN;
            } else if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && IsMouseOverButton(differentiationButton)) {
                currentScreen = Screen::DIFFERENTIALSCREEN;
            } else if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && IsMouseOverButton(integrationButton)) {
                currentScreen = Screen::INTEGRALSCREEN;
            } else if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && IsMouseOverButton(rootsButton)) {
                currentScreen = Screen::ROOTSSCREEN;
            }

        } else if (currentScreen == Screen::BITWISESCREEN) {
            Vector2 mousePoint = GetMousePosition();

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (CheckCollisionPointRec(mousePoint, (Rectangle){50, 100, 300, 50})) {
                    activeTextBox1 = true;
                    activeTextBox2 = false;
                } else if (CheckCollisionPointRec(mousePoint, (Rectangle){400, 100, 300, 50})) {
                    activeTextBox1 = false;
                    activeTextBox2 = true;
                }
            }
            HandleTextInput((activeTextBox1 == true? buffer1 : buffer2), 256, activeTextBox1 == true? activeTextBox1 : activeTextBox2);
            // Handle operations
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                // AND button
                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && IsMouseOverButton(AND)) {
                    int num1 = atoi(buffer1);
                    int num2 = atoi(buffer2);
                    int res = bitwise.bitwiseAnd(num1, num2);
                    bitwiseresult = "AND Result: " + std::to_string(res);
                }

                // OR button
                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && IsMouseOverButton(OR)) {
                    int num1 = atoi(buffer1);
                    int num2 = atoi(buffer2);
                    int res = bitwise.bitwiseOr(num1, num2);
                    bitwiseresult = "OR Result: " + std::to_string(res);
                }

                // NOT button
                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && IsMouseOverButton(NOT)) {
                    int num1 = atoi(buffer1);
                    int num2 = atoi(buffer2);
                    int res = bitwise.bitwiseNot(num1);
                    bitwiseresult = "NOT Result: " + std::to_string(res);
                    res = bitwise.bitwiseNot(num2);
                    bitwiseresult += " / " + std::to_string(res);
                }

                //XOR button
                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && IsMouseOverButton(XOR)) {
                    int num1 = atoi(buffer1);
                    int num2 = atoi(buffer2);
                    int res = bitwise.bitwiseXor(num1, num2);
                    bitwiseresult = "XOR Result: " + std::to_string(res);
                }
            }
        }
        
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && IsMouseOverButton(backButton)) {
            strcpy(buffer1, "");
            strcpy(buffer2, "");
            strcpy(coeff1, "");
            strcpy(coeff2, "");
            strcpy(coeff3, "");
            strcpy(coeff4, "");
            strcpy(coeff5, "");
            for (int i = 0; i < 126; i++) {
                numbersysteminput[i] = 0;
            }
            result = "";
            currentScreen = Screen::MAINSCREEN;
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && IsMouseOverButton(numberSystemButton)) {
            currentScreen = Screen::NUMBERSYSTEMSCREEN;
        }

        if(currentScreen == Screen::DIFFERENTIALSCREEN) {
            Differentiation diff;
            if (IsKeyPressed(KEY_ENTER)) {
                std::string temp = buffer1;
                diffResult = diff.differentiate(temp);
                strcpy(buffer1, "");
            } else {
                int key = GetKeyPressed();
                if (key > 0 && key < 256) {
                    bool shift = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);
                    char keyChar = (char)key;

                    if (shift) {
                        // Map shifted characters
                        if (key >= 'A' && key <= 'Z') {
                            keyChar = key; // Upper case letters
                        } else if (key >= 'a' && key <= 'z') {
                            keyChar = key - 32; // Convert to upper case
                        } else {
                            // Handle special characters
                            switch (key) {
                                case '1': keyChar = '!'; break;
                                case '2': keyChar = '@'; break;
                                case '3': keyChar = '#'; break;
                                case '4': keyChar = '$'; break;
                                case '5': keyChar = '%'; break;
                                case '6': keyChar = '^'; break;
                                case '7': keyChar = '&'; break;
                                case '8': keyChar = '*'; break;
                                case '9': keyChar = '('; break;
                                case '0': keyChar = ')'; break;
                                case '-': keyChar = '_'; break;
                                case '=': keyChar = '+'; break;
                                case '[': keyChar = '{'; break;
                                case ']': keyChar = '}'; break;
                                case ';': keyChar = ':'; break;
                                case '\'': keyChar = '"'; break;
                                case ',': keyChar = '<'; break;
                                case '.': keyChar = '>'; break;
                                case '/': keyChar = '?'; break;
                                case '\\': keyChar = '|'; break;
                                default: keyChar = key; break;
                            }
                        }
                    } else {
                        if (key >= 'A' && key <= 'Z') {
                            keyChar = key + 32; // Convert to lower case
                        }
                    }

                    int length = strlen(buffer1);
                    if (length < 49) { // Ensure buffer1 overflow protection
                        buffer1[length] = keyChar;
                        buffer1[length + 1] = '\0'; // Null-terminate the string
                    }
                }
            }
        }

        if(currentScreen == Screen::INTEGRALSCREEN) {
            Integration integ;
            if (IsKeyPressed(KEY_ENTER)) {
                std::string temp = buffer1;
                integResult = integ.integrate(temp);
                strcpy(buffer1, "");
            } else {
                int key = GetKeyPressed();
                if (key > 0 && key < 256) {
                    bool shift = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);
                    char keyChar = (char)key;

                    if (shift) {
                        // Map shifted characters
                        if (key >= 'A' && key <= 'Z') {
                            keyChar = key; // Upper case letters
                        } else if (key >= 'a' && key <= 'z') {
                            keyChar = key - 32; // Convert to upper case
                        } else {
                            // Handle special characters
                            switch (key) {
                                case '1': keyChar = '!'; break;
                                case '2': keyChar = '@'; break;
                                case '3': keyChar = '#'; break;
                                case '4': keyChar = '$'; break;
                                case '5': keyChar = '%'; break;
                                case '6': keyChar = '^'; break;
                                case '7': keyChar = '&'; break;
                                case '8': keyChar = '*'; break;
                                case '9': keyChar = '('; break;
                                case '0': keyChar = ')'; break;
                                case '-': keyChar = '_'; break;
                                case '=': keyChar = '+'; break;
                                case '[': keyChar = '{'; break;
                                case ']': keyChar = '}'; break;
                                case ';': keyChar = ':'; break;
                                case '\'': keyChar = '"'; break;
                                case ',': keyChar = '<'; break;
                                case '.': keyChar = '>'; break;
                                case '/': keyChar = '?'; break;
                                case '\\': keyChar = '|'; break;
                                default: keyChar = key; break;
                            }
                        }
                    } else {
                        if (key >= 'A' && key <= 'Z') {
                            keyChar = key + 32; // Convert to lower case
                        }
                    }

                    int length = strlen(buffer1);
                    if (length < 49) { // Ensure buffer1 overflow protection
                        buffer1[length] = keyChar;
                        buffer1[length + 1] = '\0'; // Null-terminate the string
                    }
                }
            }
        }

        if (currentScreen == Screen::ROOTSSCREEN) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                Vector2 mousePoint = GetMousePosition();

                if (CheckCollisionPointRec(mousePoint, (Rectangle){50, 100, 100, 50})) {
                    currentType = LINEAR;
                    activeTextBox1 = activeTextBox2 = activeTextBox3 = activeTextBox4 = activeTextBox5 = false;
                    memset(coeff1, 0, sizeof(coeff1));
                    memset(coeff2, 0, sizeof(coeff2));
                    memset(coeff3, 0, sizeof(coeff3));
                    memset(coeff4, 0, sizeof(coeff4));
                    memset(coeff5, 0, sizeof(coeff5));
                } else if (CheckCollisionPointRec(mousePoint, (Rectangle){200, 100, 100, 50})) {
                    currentType = QUADRATIC;
                    activeTextBox1 = activeTextBox2 = activeTextBox3 = activeTextBox4 = activeTextBox5 = false;
                    memset(coeff1, 0, sizeof(coeff1));
                    memset(coeff2, 0, sizeof(coeff2));
                    memset(coeff3, 0, sizeof(coeff3));
                    memset(coeff4, 0, sizeof(coeff4));
                    memset(coeff5, 0, sizeof(coeff5));
                } else if (CheckCollisionPointRec(mousePoint, (Rectangle){350, 100, 100, 50})) {
                    currentType = CUBIC;
                    activeTextBox1 = activeTextBox2 = activeTextBox3 = activeTextBox4 = activeTextBox5 = false;
                    memset(coeff1, 0, sizeof(coeff1));
                    memset(coeff2, 0, sizeof(coeff2));
                    memset(coeff3, 0, sizeof(coeff3));
                    memset(coeff4, 0, sizeof(coeff4));
                    memset(coeff5, 0, sizeof(coeff5));
                } else if (CheckCollisionPointRec(mousePoint, (Rectangle){500, 100, 100, 50})) {
                    currentType = QUARTIC;
                    activeTextBox1 = activeTextBox2 = activeTextBox3 = activeTextBox4 = activeTextBox5 = false;
                    memset(coeff1, 0, sizeof(coeff1));
                    memset(coeff2, 0, sizeof(coeff2));
                    memset(coeff3, 0, sizeof(coeff3));
                    memset(coeff4, 0, sizeof(coeff4));
                    memset(coeff5, 0, sizeof(coeff5));
                } else if (CheckCollisionPointRec(mousePoint, (Rectangle){650, 100, 100, 50})) {
                    // Solve equation based on selected type
                    try {
                        switch (currentType) {
                            case LINEAR: {
                                double a = atof(coeff1);
                                double b = atof(coeff2);
                                double root = solver.solveLinearEquation(a, b);
                                result = "Root: " + std::to_string(root);
                                break;
                            }
                            case QUADRATIC: {
                                double a = atof(coeff1);
                                double b = atof(coeff2);
                                double c = atof(coeff3);
                                auto [root1, root2] = solver.solveQuadraticEquation(a, b, c);
                                result = "Roots: " + std::to_string(root1) + ", " + std::to_string(root2);
                                break;
                            }
                            case CUBIC: {
                                double a = atof(coeff1);
                                double b = atof(coeff2);
                                double c = atof(coeff3);
                                double d = atof(coeff4);
                                auto [root1, root2, root3] = solver.solveCubicEquation(a, b, c, d);
                                result = "Roots: " + std::to_string(root1) + ", " + std::to_string(root2) + ", " + std::to_string(root3);
                                break;
                            }
                            case QUARTIC: {
                                double a = atof(coeff1);
                                double b = atof(coeff2);
                                double c = atof(coeff3);
                                double d = atof(coeff4);
                                double e = atof(coeff5);
                                auto [root1, root2, root3, root4] = solver.solveFourthOrderEquation(a, b, c, d, e);
                                result = "Roots: " + std::to_string(root1) + ", " + std::to_string(root2) + ", " + std::to_string(root3) + ", " + std::to_string(root4);
                                break;
                            }
                            default:
                                result = "Select an equation type.";
                                break;
                        }
                    } catch (const std::exception& e) {
                        result = e.what();
                    }
                } else {
                    // Handle text box activation
                    if (CheckCollisionPointRec(mousePoint, (Rectangle){50, 250, 300, 50})) {
                        activeTextBox1 = true;
                        activeTextBox2 = activeTextBox3 = activeTextBox4 = activeTextBox5 = false;
                    } else if (CheckCollisionPointRec(mousePoint, (Rectangle){50, 320, 300, 50})) {
                        activeTextBox2 = true;
                        activeTextBox1 = activeTextBox3 = activeTextBox4 = activeTextBox5 = false;
                    } else if (CheckCollisionPointRec(mousePoint, (Rectangle){50, 390, 300, 50})) {
                        activeTextBox3 = true;
                        activeTextBox1 = activeTextBox2 = activeTextBox4 = activeTextBox5 = false;
                    } else if (CheckCollisionPointRec(mousePoint, (Rectangle){50, 460, 300, 50})) {
                        activeTextBox4 = true;
                        activeTextBox1 = activeTextBox2 = activeTextBox3 = activeTextBox5 = false;
                    } else if (CheckCollisionPointRec(mousePoint, (Rectangle){50, 530, 300, 50})) {
                        activeTextBox5 = true;
                        activeTextBox1 = activeTextBox2 = activeTextBox3 = activeTextBox4 = false;
                    } else {
                        activeTextBox1 = activeTextBox2 = activeTextBox3 = activeTextBox4 = activeTextBox5 = false;
                    }
                }
            }

            // Handle text input
            HandleTextInput(coeff1, 128, activeTextBox1);
            HandleTextInput(coeff2, 128, activeTextBox2);
            HandleTextInput(coeff3, 128, activeTextBox3);
            HandleTextInput(coeff4, 128, activeTextBox4);
            HandleTextInput(coeff5, 128, activeTextBox5);
        }

        if (currentScreen == Screen::NUMBERSYSTEMSCREEN) {
            HandleTextInput(numbersysteminput, 256, numbersysteminputActive);
            std::string tempInput = numbersysteminput;
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {

                if (IsMouseOverButton(decToBinaryButton))
                {
                    try
                    {
                        int decimalInput = std::stoi(tempInput);
                        numSysResult = numSys.decimalToBinary(decimalInput);
                    }
                    catch (const std::exception &e)
                    {
                        numSysResult = "Invalid input";
                    }
                }
                else if (IsMouseOverButton(decToOctalButton))
                {
                    try
                    {
                        int decimalInput = std::stoi(tempInput);
                        numSysResult = numSys.decimalToOctal(decimalInput);
                    }
                    catch (const std::exception &e)
                    {
                        numSysResult = "Invalid input";
                    }
                }
                else if (IsMouseOverButton(decToHexaButton)) {
                    try {
                        int decimalInput = std::stoi(tempInput);
                        numSysResult = numSys.decimalToHexadecimal(decimalInput);
                    }
                    catch (const std::exception &e) {
                        numSysResult = "Invalid input";
                    }
                }
                else if (IsMouseOverButton(binaryToDecimalButton)) {
                    try {
                        numSysResult = numSys.binaryToDecimal(tempInput);
                    }
                    catch (const std::exception &e) {
                        numSysResult = "Invalid input";
                    }
                }
                else if (IsMouseOverButton(binaryToOctalButton)) {
                    try {
                        numSysResult = numSys.binaryToOctal(tempInput);
                    }
                    catch (const std::exception &e) {
                        numSysResult = "Invalid input";
                    }
                }
                else if (IsMouseOverButton(binaryToHexaButton)) {
                    try {
                        numSysResult = numSys.binaryToHexadecimal(tempInput);
                    }
                    catch (const std::exception &e) {
                        numSysResult = "Invalid input";
                    }
                }
                else if (IsMouseOverButton(octalToBinaryButton)) {
                    try {
                        numSysResult = numSys.octalToBinary(tempInput);
                    }
                    catch (const std::exception &e) {
                        numSysResult = "Invalid input";
                    }
                }
                else if (IsMouseOverButton(octalToDecimalButton)) {
                    try {
                        numSysResult = numSys.octalToDecimal(tempInput);
                    }
                    catch (const std::exception &e) {
                        numSysResult = "Invalid input";
                    }
                }
                else if (IsMouseOverButton(octalToHexaButton)) {
                    try {
                        numSysResult = numSys.octalToHexadecimal(tempInput);
                    }
                    catch (const std::exception &e) {
                        numSysResult = "Invalid input";
                    }
                }
                else if (IsMouseOverButton(hexaToBinaryButton)) {
                    try {
                        numSysResult = numSys.hexadecimalToBinary(tempInput);
                    }
                    catch (const std::exception &e) {
                        numSysResult = "Invalid input";
                    }
                }
                else if (IsMouseOverButton(hexaToOctalButton)) {
                    try {
                        numSysResult = numSys.hexadecimalToOctal(tempInput);
                    }
                    catch (const std::exception &e) {
                        numSysResult = "Invalid input";
                    }
                }
                else if (IsMouseOverButton(hexaToDecimalButton)) {
                    try {
                        numSysResult = numSys.hexadecimalToDecimal(tempInput);
                    }
                    catch (const std::exception &e) {
                        numSysResult = "Invalid input";
                    }
                }
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (currentScreen == Screen::MAINSCREEN) {
            DrawText("Calculator", 10, 10, 20, DARKGRAY);
            DrawText(input.c_str(), 10, 50, 20, DARKGRAY);
            DrawText(result.c_str(), 10, 70, 20, DARKGRAY);
            for (int i = 0; i < 16; ++i) {
                DrawButton(buttons[i], buttonLabels[i]);
            }
            DrawButton(sinButton, "sin");
            DrawButton(cosButton, "cos");
            DrawButton(tanButton, "tan");
            DrawButton(cotButton, "cot");
            DrawButton(cscButton, "csc");
            DrawButton(secButton, "sec");
            DrawButton(sinhButton, "sinh");
            DrawButton(coshButton, "cosh");
            DrawButton(tanhButton, "tanh");
            DrawButton(cothButton, "coth");
            DrawButton(cschButton, "csch");
            DrawButton(sechButton, "sech");
            DrawButton(bitwiseButton, "Bitwise");
            DrawButton(rootsButton, "Roots");
            DrawButton(clearButton, "CLR");
            DrawButton(differentiationButton, "d/dx");
            DrawButton(integrationButton, "Integration");
            DrawButton(numberSystemButton, "Number System");
            DrawButton(factorialButton, "Factorial");
            DrawButton(combinationsButton, "C");
            DrawButton(permutationsButton, "P");
        } else if (currentScreen == Screen::BITWISESCREEN) {
            DrawButton(backButton, "Back");
            DrawRectangle(50, 100, 300, 50, LIGHTGRAY);
            DrawRectangleLines(50, 100, 300, 50, GRAY);
            DrawText(buffer1, 55, 110, 20, DARKGRAY);
            DrawRectangle(400, 100, 300, 50, LIGHTGRAY);
            DrawRectangleLines(400, 100, 300, 50, LIGHTGRAY);
            DrawText(buffer2, 405, 110, 20, DARKGRAY);
            DrawButton(AND, "AND");
            DrawButton(OR, "OR");
            DrawButton(NOT, "NOT");
            DrawButton(XOR, "XOR");
            DrawText(bitwiseresult.c_str(), 50, 350, 20, DARKGRAY);
        } else if (currentScreen == Screen::DIFFERENTIALSCREEN) {
            DrawButton(backButton, "Back");
            DrawRectangle(50, 100, 700, 50, LIGHTGRAY);
            DrawRectangleLines(50, 100, 700, 50, GRAY);
            DrawText(buffer1, 55, 110, 20, DARKGRAY);
            DrawText(diffResult.c_str(), 100, 200, 40, DARKGRAY);
        } else if (currentScreen == Screen::INTEGRALSCREEN) {
            DrawButton(backButton, "Back");
            DrawRectangle(50, 100, 700, 50, LIGHTGRAY);
            DrawRectangleLines(50, 100, 700, 50, GRAY);
            DrawText(buffer1, 55, 110, 20, DARKGRAY);
            DrawText(integResult.c_str(), 100, 200, 40, DARKGRAY);
        } else if (currentScreen == Screen::ROOTSSCREEN) {
            DrawButton(backButton, "Back");
            DrawRectangle(50, 100, 100, 50, currentType == LINEAR ? DARKGRAY : LIGHTGRAY);
            DrawText("Linear", 60, 115, 20, BLACK);
            DrawRectangle(200, 100, 100, 50, currentType == QUADRATIC ? DARKGRAY : LIGHTGRAY);
            DrawText("Quadratic", 210, 115, 20, BLACK);
            DrawRectangle(350, 100, 100, 50, currentType == CUBIC ? DARKGRAY : LIGHTGRAY);
            DrawText("Cubic", 370, 115, 20, BLACK);
            DrawRectangle(500, 100, 100, 50, currentType == QUARTIC ? DARKGRAY : LIGHTGRAY);
            DrawText("Quartic", 520, 115, 20, BLACK);
            DrawRectangle(650, 100, 100, 50, LIGHTGRAY);
            DrawText("Solve", 675, 115, 20, BLACK);
            DrawRectangle(50, 250, 300, 50, activeTextBox1 ? LIGHTGRAY : GRAY);
            DrawText(coeff1, 60, 265, 20, BLACK);
            DrawRectangle(50, 310, 300, 50, activeTextBox2 ? LIGHTGRAY : GRAY);
            DrawText(coeff2, 60, 335, 20, BLACK);
            DrawRectangle(50, 390, 300, 50, activeTextBox3 ? LIGHTGRAY : GRAY);
            DrawText(coeff3, 60, 405, 20, BLACK);
            DrawRectangle(50, 460, 300, 50, activeTextBox4 ? LIGHTGRAY : GRAY);
            DrawText(coeff4, 60, 475, 20, BLACK);
            DrawRectangle(50, 530, 300, 50, activeTextBox5 ? LIGHTGRAY : GRAY);
            DrawText(coeff5, 60, 545, 20, BLACK);
            DrawText(result.c_str(), 50, 600, 20, BLACK);
        } else if (currentScreen == Screen::NUMBERSYSTEMSCREEN) {
            DrawButton(backButton, "Back");
            DrawText("Enter a number:", 50, 100, 20, DARKGRAY);
            DrawRectangle(50, 150, 700, 50, numbersysteminputActive ? LIGHTGRAY : GRAY);
            DrawText(numbersysteminput, 60, 60, 20, BLACK);
            DrawButton(decToBinaryButton, "DTB");
            DrawButton(decToOctalButton, "DTO");
            DrawButton(decToHexaButton, "DTH");
            DrawButton(binaryToDecimalButton, "BTD");
            DrawButton(binaryToOctalButton, "BTO");
            DrawButton(binaryToHexaButton, "BTH");
            DrawButton(octalToBinaryButton, "OTB");
            DrawButton(octalToDecimalButton, "OTD");
            DrawButton(octalToHexaButton, "OTH");
            DrawButton(hexaToBinaryButton, "HTB");
            DrawButton(hexaToOctalButton, "HTO");
            DrawButton(hexaToDecimalButton, "HTD");
            DrawText(numSysResult.c_str(), 50, 200, 40, DARKGRAY);
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}