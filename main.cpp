#include "include/ScientificCalculator.h"
#include "include/raylib.h"
#include <iostream>
#include <tuple>
#include <cstring>
#include <cctype>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>

enum class Screens {
    MAINSCREEN,
    BITWISESCREEN,
    EQUATIONSSCREEN,
    DIFFERENTIALSCREEN,
    INTEGRALSCREEN,
    NUMBERSYSTEMSCREEN,
    TRIGONOMETRYSCREEN,
    HYPERBOLICSCREEN,
    VECTORSCREEN
};

enum class EquationType {
    NONE,
    LINEAR,
    QUADRATIC,
    CUBIC,
    QUARTIC
};

bool IsMouseOverButton(Rectangle button) {
    return CheckCollisionPointRec(GetMousePosition(), button);
}

void DrawButton(Rectangle button, const char *text, const int textSize = 20, Color recColor = LIGHTGRAY, Color textColor = BLACK) {
    DrawRectangleRec(button, recColor);
    DrawRectangleLinesEx(button, 2, BLACK);
    DrawText(text, button.x + 10, button.y + 10, textSize, textColor);
}

void DrawTextBox(Rectangle textBox, const char *text, const int textSize = 20, Color recColor = LIGHTGRAY, Color textColor = BLACK) {
    DrawRectangleRec(textBox, recColor);
    DrawRectangleLinesEx(textBox, 2, BLACK);
    DrawText(text, textBox.x + 10, textBox.y + 10, textSize, textColor);
}

void HandleTextInput(char* buffer, int maxSize, bool active) {
    if (active) {
        int key = GetKeyPressed();
        while (key > 0) {
            if ((key >= 32) && (key <= 125) && (strlen(buffer) < (long long unsigned)maxSize)) {
                bool shiftPressed = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);
                char charToInsert = (char)key;

                // Handle shift for alphabetic characters
                if (shiftPressed && charToInsert >= 'a' && charToInsert <= 'z') {
                    charToInsert = (char)(charToInsert - 'a' + 'A');
                }
                // Handle shift for numeric characters and common symbols
                else if (shiftPressed) {
                    switch (charToInsert) {
                        case '1': charToInsert = '!'; break;
                        case '2': charToInsert = '@'; break;
                        case '3': charToInsert = '#'; break;
                        case '4': charToInsert = '$'; break;
                        case '5': charToInsert = '%'; break;
                        case '6': charToInsert = '^'; break;
                        case '7': charToInsert = '&'; break;
                        case '8': charToInsert = '*'; break;
                        case '9': charToInsert = '('; break;
                        case '0': charToInsert = ')'; break;
                        case '`': charToInsert = '~'; break;
                        case '-': charToInsert = '_'; break;
                        case '=': charToInsert = '+'; break;
                        case '[': charToInsert = '{'; break;
                        case ']': charToInsert = '}'; break;
                        case '\\': charToInsert = '|'; break;
                        case ';': charToInsert = ':'; break;
                        case '\'': charToInsert = '\"'; break;
                        case ',': charToInsert = '<'; break;
                        case '.': charToInsert = '>'; break;
                        case '/': charToInsert = '?'; break;
                    }
                }
                int len = strlen(buffer);
                buffer[len] = charToInsert;
                buffer[len + 1] = '\0';
            }
            if (key == KEY_BACKSPACE && strlen(buffer) > 0) {
                buffer[strlen(buffer) - 1] = '\0';
            }
            key = GetKeyPressed();
        }
    }
}

Vector parseVector(const std::string& input) {
    std::vector<double> components;
    std::stringstream ss(input);
    std::string value;

    while (std::getline(ss, value, ',')) {
        components.push_back(std::stod(value));
    }

    return Vector(components);
}

int main() {
    //constants
    const int screenWidth = 900;
    const int screenHeight = 900;
    const int buttonWidth = 80;
    const int buttonHeight = 40;
    Screens currentScreen = Screens::MAINSCREEN;
    const char *buttonLabels[18] = {
        "7", "8", "9", "/",
        "4", "5", "6", "*",
        "1", "2", "3", "-",
        "0", ".", "=", "+",
        "%", "^"
    };

    //Variable declarations
    std::string input = "";
    std::string result = "";
    EquationType currentEquationType = EquationType::NONE;
    char text1[50] = "";
    char text2[50] = "";
    char coeff1[50] = "";
    char coeff2[50] = "";
    char coeff3[50] = "";
    char coeff4[50] = "";
    char coeff5[50] = "";
    bool coeff1_active = false, coeff2_active = false;
    bool coeff3_active = false, coeff4_active = false, coeff5_active = false;
    bool isTextBox1Active = false, isTextBox2Active = false;

    //Button declarations
    Rectangle buttons[18];
    for (int i = 0; i < 18; ++i) {
        buttons[i] = {50.0f + (i % 4) * (buttonWidth + 10), 180.0f + (i / 4) * (buttonHeight + 10), buttonWidth, buttonHeight};
    }
    Rectangle trigonometryButton = {450, 180, 160, 40};
    Rectangle sinButton = {100, 250, 140, 40};
    Rectangle cosButton = {100, 300, 140, 40};
    Rectangle tanButton = {100, 350, 140, 40};
    Rectangle cotButton = {100, 400, 140, 40};
    Rectangle cscButton = {100, 450, 140, 40};
    Rectangle secButton = {100, 500, 140, 40};
    Rectangle arcsinButton = {400, 250, 140, 40};
    Rectangle arccosButton = {400, 300, 140, 40};
    Rectangle arctanButton = {400, 350, 140, 40};
    Rectangle arccotButton = {400, 400, 140, 40};
    Rectangle arccscButton = {400, 450, 140, 40};
    Rectangle arcsecButton = {400, 500, 140, 40};

    Rectangle hyperbolicButton = {660, 180, 140, 40};
    Rectangle sinhButton = {100, 250, 140, 40};
    Rectangle coshButton = {100, 300, 140, 40};
    Rectangle tanhButton = {100, 350, 140, 40};
    Rectangle cothButton = {100, 400, 140, 40};
    Rectangle cschButton = {100, 450, 140, 40};
    Rectangle sechButton = {100, 500, 140, 40};
    Rectangle arcsinhButton = {400, 250, 140, 40};
    Rectangle arccoshButton = {400, 300, 140, 40};
    Rectangle arctanhButton = {400, 350, 140, 40};
    Rectangle arccothButton = {400, 400, 140, 40};
    Rectangle arccschButton = {400, 450, 140, 40};
    Rectangle arcsechButton = {400, 500, 140, 40};

    Rectangle equationsButton        = {50, 430, 170, 40};
    Rectangle bitwiseButton          = {50, 480, 170, 40};
    Rectangle differentiationButton  = {50, 530, 170, 40};

    Rectangle permutationsButton     = {50, 580, 170, 40};
    Rectangle combinationsButton     = {230, 530, 170, 40};

    Rectangle clearButton            = {230, 380, 170, 40};
    Rectangle numberSystemButton     = {230, 430, 170, 40}; 
    Rectangle integrationButton      = {230, 480, 170, 40};

    Rectangle factorialButton        = {450, 230, 160, 40};
    Rectangle naturalLogarithmButton = {450, 280, 160, 40};
    
    Rectangle squareRootButton       = {660, 230, 140, 40};
    Rectangle commonLogarithmButton  = {660, 280, 140, 40};

    Rectangle leftParenthesisButton = {450, 330, 160, 40};
    Rectangle rightParenthesisButton = {660, 330, 140, 40};

    Rectangle piButton = {450, 380, 160, 40};
    Rectangle eButton = {660, 380, 140, 40};

    Rectangle vectorButton = {230, 580, 170, 40};
    Rectangle dotproductButton = {100, 550, 140, 40};
    Rectangle crossproductButton = {270, 550, 170, 40};
    Rectangle addVectorButton = {100, 610, 140, 40};
    Rectangle subtractVectorButton = {270, 610, 170, 40};
    Rectangle magnitudeButton = {100, 670, 140, 40};

    Rectangle backButton      = {10, 10, 140, 40};  
    Rectangle linearButton    = {50, 100, 100, 50};
    Rectangle quadraticButton = {200, 100, 115, 50};
    Rectangle cubicButton     = {350, 100, 100, 50};
    Rectangle quarticButton   = {500, 100, 100, 50};
    Rectangle solveButton     = {650, 100, 100, 50};

    Rectangle firstcoeff  = {50, 250, 300, 50};
    Rectangle secondcoeff = {50, 350, 300, 50};
    Rectangle thirdcoeff  = {50, 450, 300, 50};
    Rectangle fourthcoeff = {50, 550, 300, 50};
    Rectangle fifthcoeff  = {50, 650, 300, 50};

    Rectangle textBox1 = {50, 150, 750, 50};
    Rectangle textBox2 = {50, 265, 750, 50};

    Rectangle andButton = {50,  525, 150, 40};
    Rectangle orButton  = {250, 525, 150, 40};
    Rectangle notButton = {450, 525, 150, 40};
    Rectangle xorButton = {650, 525, 150, 40};

    Rectangle decToBinaryButton     = {50,    500, 200, 40};
    Rectangle decToOctalButton      = {300,   500, 200, 40};
    Rectangle decToHexaButton       = {550,   500, 200, 40};
    Rectangle binaryToOctalButton   = {50,    550, 200, 40};
    Rectangle binaryToDecimalButton = {300,   550, 200, 40};
    Rectangle binaryToHexaButton    = {550,   550, 200, 40};
    Rectangle octalToBinaryButton   = {50,    600, 200, 40};
    Rectangle octalToDecimalButton  = {300,   600, 200, 40};
    Rectangle octalToHexaButton     = {550,   600, 200, 40};
    Rectangle hexaToBinaryButton    = {50,    650, 200, 40};
    Rectangle hexaToOctalButton     = {300,   650, 200, 40};
    Rectangle hexaToDecimalButton   = {550,   650, 200, 40};
    
    Rectangle calculateButton = {50, 410, 230, 50};
        
    //Object Instantiation
    Arithmetic calc;
    Trigonometry trig;
    HyperbolicFunctions hyp;
    Combinatorics comb;
    EquationSolver solver;
    LogarithmCalculator mylog;
    Roots roots;
    BitwiseOperators bitwise;
    NumberSystem numSys;
    Differentiation diff;
    Integration integ;

    InitWindow(screenWidth, screenHeight, "Calculator");
    // Main Logic
    while (!WindowShouldClose()) {
        // Back Button
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && IsMouseOverButton(backButton) && currentScreen != Screens::MAINSCREEN) {
            currentScreen = Screens::MAINSCREEN;
            result = "";
            input = "";
            strcpy(coeff1, "");
            strcpy(coeff2, "");
            strcpy(coeff3, "");
            strcpy(coeff4, "");
            strcpy(coeff5, "");
            strcpy(text1, "");
            strcpy(text2, "");
        }
        // MAINSCREEN logic
        if (currentScreen == Screens::MAINSCREEN) {
            // Arithmetic functions
            for (int i = 0; i < 18; i++) {
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
                                if (input != "") {
                                    try{
                                        result = std::to_string(calc.evaluate(input));
                                    } catch (...) {
                                        result = "Invalid Operation!";
                                    }
                                } else {
                                    result = "Invalid Operations!";
                                }
                            }
                        }catch (const std::exception &e) {
                            result = "Invalid Operations!";
                        } catch (...) {
                            result = "Invalid Operations!";
                        }
                        input = "";
                    } else {
                        input += " " + std::string(label) + " ";
                    }
                }
            }

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                if(IsMouseOverButton(factorialButton)) {
                    try {
                        input += "!";
                        int temp = std::stoi(input);
                        result = std::to_string(comb.factorial(temp));
                    } catch (...) {
                        result = "Invalid input";
                    }
                } else if (IsMouseOverButton(combinationsButton)) {
                    input += "C";
                } else if (IsMouseOverButton(permutationsButton)) {
                    input += "P";
                } else if (IsMouseOverButton(leftParenthesisButton)) {
                    input += " ( ";
                } else if (IsMouseOverButton(rightParenthesisButton)) {
                    input += " ) ";
                } else if (IsMouseOverButton(piButton)) {
                    input += "pi ";
                } else if (IsMouseOverButton(eButton)) {
                    input += "e";
                } else if (IsMouseOverButton(naturalLogarithmButton)) {
                    try {
                        result = std::to_string(mylog.calculateLog(std::stod(input)));
                        input.insert(0, "ln(");
                    } catch (...) {
                        result = "Invalid Operation!";
                    }
                } else if (IsMouseOverButton(commonLogarithmButton)) {
                    try {
                        result = std::to_string(mylog.calculateLog10(std::stod(input)));
                        input.insert(0, "log(");
                    } catch (...) {
                        result = "Invalid Operation!";
                    }
                } else if (IsMouseOverButton(squareRootButton)) {
                    try {
                        result = std::to_string(roots.squareRoot(std::stod(input)));
                    } catch (...) {
                        result = "Invalid Operation!";
                    }
                }

                //Clear Button
                if (IsMouseOverButton(clearButton)) {
                    if (result != "" || input != "") {
                        input = "";
                        result = "";
                    }
                }
                //Screen Changes
                if (IsMouseOverButton(equationsButton)) {
                    currentScreen = Screens::EQUATIONSSCREEN;
                    strcpy(coeff1, "");
                    strcpy(coeff2, "");
                    strcpy(coeff3, "");
                    strcpy(coeff4, "");
                    strcpy(coeff5, "");
                    result = "";
                } else if (IsMouseOverButton(differentiationButton)) {
                    currentScreen = Screens::DIFFERENTIALSCREEN;
                    strcpy(text1, "");
                    result = "";
                } else if (IsMouseOverButton(integrationButton)) {
                    currentScreen = Screens::INTEGRALSCREEN;
                    strcpy(text1, "");
                    result = "";
                } else if (IsMouseOverButton(bitwiseButton)) {
                    currentScreen = Screens::BITWISESCREEN;
                    strcpy(text1, "");
                    strcpy(text2, "");
                    result = "";
                } else if (IsMouseOverButton(numberSystemButton)) {
                    currentScreen = Screens::NUMBERSYSTEMSCREEN;
                    strcpy(text1, "");
                    result = "";
                } else if (IsMouseOverButton(trigonometryButton)) {
                    currentScreen = Screens::TRIGONOMETRYSCREEN;
                    strcpy(text1, "");
                    result = "";
                } else if (IsMouseOverButton(hyperbolicButton)) {
                    currentScreen = Screens::HYPERBOLICSCREEN;
                    strcpy(text1, "");
                    result = "";
                } else if (IsMouseOverButton(vectorButton)) {
                    currentScreen = Screens::VECTORSCREEN;
                    strcpy(text1, "");
                    strcpy(text2, "");
                    isTextBox1Active = isTextBox2Active = false;
                }
            } // Mouse Checks Ends
        } // MAINSCREEN logic ends

        //EQUATIONSSCREEN logic starts
        else if (currentScreen == Screens::EQUATIONSSCREEN) {
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                if (IsMouseOverButton(linearButton)) {
                    currentEquationType = EquationType::LINEAR;
                    coeff1_active = coeff2_active = coeff3_active = coeff4_active = coeff5_active = false;
                    strcpy(coeff1, "");
                    strcpy(coeff2, "");
                    result = "";
                } else if (IsMouseOverButton(quadraticButton)) {
                    currentEquationType = EquationType::QUADRATIC;
                    coeff1_active = coeff2_active = coeff3_active = coeff4_active = coeff5_active = false;
                    strcpy(coeff1, "");
                    strcpy(coeff2, "");
                    strcpy(coeff3, "");
                    result = "";
                } else if (IsMouseOverButton(cubicButton)) {
                    currentEquationType = EquationType::CUBIC;
                    coeff1_active = coeff2_active = coeff3_active = coeff4_active = coeff5_active = false;
                    strcpy(coeff1, "");
                    strcpy(coeff2, "");
                    strcpy(coeff3, "");
                    strcpy(coeff4, "");
                    result = "";
                } else if (IsMouseOverButton(quarticButton)) {
                    currentEquationType = EquationType::QUARTIC;
                    coeff1_active = coeff2_active = coeff3_active = coeff4_active = coeff5_active = false;
                    strcpy(coeff1, "");
                    strcpy(coeff2, "");
                    strcpy(coeff3, "");
                    strcpy(coeff4, "");
                    strcpy(coeff5, "");
                    result = "";
                } else if (IsMouseOverButton(solveButton)) {
                    try {
                        switch (currentEquationType) {
                            case EquationType::LINEAR: {
                                double a = atof(coeff1);
                                double b = atof(coeff2);
                                double root = solver.solveLinearEquation(a, b);
                                result = std::to_string(root);
                                break;
                            }
                            case EquationType::QUADRATIC: {
                                double a = atof(coeff1);
                                double b = atof(coeff2);
                                double c = atof(coeff3);
                                auto [root1, root2] = solver.solveQuadraticEquation(a, b, c);
                                result = std::to_string(root1.first);
                                if (root1.second != 0) {
                                    result += " + " + std::to_string(root1.second) + "i";
                                }
                                result += "\n\n" + std::to_string(root2.first);
                                if (root2.second != 0) {
                                    result += " + " + std::to_string(root2.second) + "i";
                                }
                                break;
                            }
                            case EquationType::CUBIC: {
                                double a = atof(coeff1);
                                double b = atof(coeff2);
                                double c = atof(coeff3);
                                double d = atof(coeff4);
                                auto [root1, root2, root3] = solver.solveCubicEquation(a, b, c, d);
                                result = std::to_string(root1.first);
                                if (root1.second != 0) {
                                    result += " + " + std::to_string(root1.second) + "i";
                                }
                                result += "\n\n" + std::to_string(root2.first);
                                if (root2.second != 0) {
                                    result += " + " + std::to_string(root2.second) + "i";
                                }
                                result += "\n\n" + std::to_string(root3.first);
                                if (root3.second != 0) {
                                    result += " + " + std::to_string(root3.second) + "i";
                                } 
                                break;
                            }
                            case EquationType::QUARTIC: {
                                double a = atof(coeff1);
                                double b = atof(coeff2);
                                double c = atof(coeff3);
                                double d = atof(coeff4);
                                double e = atof(coeff5);
                                auto [root1, root2, root3, root4] = solver.solveFourthOrderEquation(a, b, c, d, e);
                                result = std::to_string(root1.first);
                                if (root1.second != 0) {
                                    result += " + " + std::to_string(root1.second) + "i";
                                }
                                result += "\n\n" + std::to_string(root2.first);
                                if (root2.second != 0) {
                                    result += " + " + std::to_string(root2.second) + "i";
                                }
                                result += "\n\n" + std::to_string(root3.first);
                                if (root3.second != 0) {
                                    result += " + " + std::to_string(root3.second) + "i";
                                }
                                result += "\n\n" + std::to_string(root4.first);
                                if (root4.second != 0) {
                                    result += " + " + std::to_string(root4.second) + "i";
                                }
                                break;
                            }
                            default:
                                result = "Select an equation type.";
                                break;
                        }
                    } catch (const std::exception& e) {
                        result = e.what();
                    }
                }

                if (IsMouseOverButton(firstcoeff)) {
                    coeff1_active = true;
                    coeff2_active = coeff3_active = coeff4_active = coeff5_active = false;
                } else if (IsMouseOverButton(secondcoeff)) {
                    coeff2_active = true;
                    coeff1_active = coeff3_active = coeff4_active = coeff5_active = false;
                } else if (IsMouseOverButton(thirdcoeff)) {
                    coeff3_active = true;
                    coeff1_active = coeff2_active = coeff4_active = coeff5_active = false;
                } else if (IsMouseOverButton(fourthcoeff)) {
                    coeff4_active = true;
                    coeff1_active = coeff2_active = coeff3_active = coeff5_active = false;
                } else if (IsMouseOverButton(fifthcoeff)) {
                    coeff5_active = true;
                    coeff1_active = coeff2_active = coeff3_active = coeff4_active = false;
                }
            }
            HandleTextInput(coeff1, 50, coeff1_active);
            HandleTextInput(coeff2, 50, coeff2_active);
            HandleTextInput(coeff3, 50, coeff3_active);
            HandleTextInput(coeff4, 50, coeff4_active);
            HandleTextInput(coeff5, 50, coeff5_active);
        }// EQUATIONSSCREEN logic ends

        //BITWISECREEN logic starts
        else if (currentScreen == Screens::BITWISESCREEN) {
            HandleTextInput(text1, 50, isTextBox1Active);
            HandleTextInput(text2, 50, isTextBox2Active);
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                if (IsMouseOverButton(textBox1)) {
                    isTextBox1Active = true;
                    isTextBox2Active = false;
                } else if (IsMouseOverButton(textBox2)) {
                    isTextBox1Active = false;
                    isTextBox2Active = true;
                } else if (IsMouseOverButton(andButton)) {
                    try {
                        result = "AND = " + std::to_string(bitwise.bitwiseAnd(atoi(text1), atoi(text2)));
                    } catch (...) {
                        result = "Invalid Operation!";
                    }
                } else if (IsMouseOverButton(orButton)) {
                    try {
                        result = "OR = " + std::to_string(bitwise.bitwiseOr(atoi(text1), atoi(text2)));
                    } catch (...) {
                        result = "Invalid Operation!";
                    }
                } else if (IsMouseOverButton(notButton)) {
                    try {
                        result = "NOT of first number = " + std::to_string(bitwise.bitwiseNot(atoi(text1)));
                        result += "\n\nNOT of second number = " + std::to_string(bitwise.bitwiseNot(atoi(text2)));
                    } catch (...) {
                        result = "Invalid Operation!";
                    }
                } else if (IsMouseOverButton(xorButton)) {
                    try {
                        result = "XOR = " + std::to_string(bitwise.bitwiseXor(atoi(text1), atoi(text2)));
                    } catch (...) {
                        result = "Invalid Operation!";
                    }
                }
            }
        }// BITWISESCREEN logic ends

        //NUMBERSYSTEMCREEN logic starts
        else if (currentScreen == Screens::NUMBERSYSTEMSCREEN) {
            HandleTextInput(text1, 50, isTextBox1Active = true);
            try {
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                    if (IsMouseOverButton(decToBinaryButton)) {
                        result = numSys.decimalToBinary(std::stod(text1));
                    } else if (IsMouseOverButton(decToOctalButton)) {
                        result = numSys.decimalToOctal(std::stod(text1));
                    } else if (IsMouseOverButton(decToHexaButton)) {
                        result = numSys.decimalToHexadecimal(std::stod(text1));
                    } else if (IsMouseOverButton(binaryToOctalButton)) {
                        result = numSys.binaryToOctal(text1);
                    } else if (IsMouseOverButton(binaryToDecimalButton)) {
                        result = numSys.binaryToDecimal(text1);
                    } else if (IsMouseOverButton(binaryToHexaButton)) {
                        result = numSys.binaryToHexadecimal(text1);
                    } else if (IsMouseOverButton(octalToBinaryButton)) {
                        result = numSys.octalToBinary(text1);
                    } else if (IsMouseOverButton(octalToDecimalButton)) {
                        result = numSys.octalToDecimal(text1);
                    } else if (IsMouseOverButton(octalToHexaButton)) {
                        result = numSys.octalToHexadecimal(text1);
                    } else if (IsMouseOverButton(hexaToBinaryButton)) {
                        result = numSys.hexadecimalToBinary(text1);
                    } else if (IsMouseOverButton(hexaToOctalButton)) {
                        result = numSys.hexadecimalToOctal(text1);
                    } else if (IsMouseOverButton(hexaToDecimalButton)) {
                        result = numSys.hexadecimalToDecimal(text1);
                    }
                }
            } catch (...) {
                result = "Invalid Input!";
            }
        }// NUMBERSYSTEMCREEN logic ends
        
        //DIFFERENTIALCREEN logic starts
        else if (currentScreen == Screens::DIFFERENTIALSCREEN) {
            HandleTextInput(text1, 50, isTextBox1Active = true);
            try{
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && IsMouseOverButton(calculateButton)) {
                    std::string temp = text1;
                    for (size_t i = 0; i < temp.length(); i++) {
                        temp[i] = tolower(temp[i]);
                    }
                    result = diff.differentiate(temp);
                }
            } catch (...) {
                result = "Invalid Operation!";
            }
        }// DIFFERENTIALSCREEN logic ends

        //INTEGRALSCREEN logic starts
        else if (currentScreen == Screens::INTEGRALSCREEN) {
            HandleTextInput(text1, 50, isTextBox1Active = true);
            try{
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && IsMouseOverButton(calculateButton)) {
                    std::string temp = text1;
                    for (size_t i = 0; i < temp.length(); i++) {
                        temp[i] = tolower(temp[i]);
                    }
                    result = integ.integrate(temp);
                }
            } catch (...) {
                result = "Invalid Operation!";
            }
        }// INTEGRALSCREEN logic ends
        //TRIGONOMETRYSCREEN starts
        else if (currentScreen == Screens::TRIGONOMETRYSCREEN) {
            HandleTextInput(text1, 50, isTextBox1Active = true);
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                if (IsMouseOverButton(sinButton)) {
                    try {
                        double angle = atof(text1);
                        result = std::to_string(trig.sine(angle));
                    } catch (...) {
                        result = "Invalid input";
                    }
                } else if (IsMouseOverButton(cosButton)) {
                    try {
                        double angle = atof(text1);
                        result = std::to_string(trig.cosine(angle));
                    } catch (...) {
                        result = "Invalid input";
                    }
                } else if (IsMouseOverButton(tanButton)) {
                    try {
                        double angle = atof(text1);
                        result = std::to_string(trig.tangent(angle));
                    } catch (...) {
                        result = "Invalid input";
                    }
                } else if (IsMouseOverButton(cscButton)) {
                    try {
                        double angle = atof(text1);
                        result = std::to_string(trig.cosecant(angle));
                    } catch (...) {
                        result = "Invalid input";
                    }
                } else if (IsMouseOverButton(secButton)) {
                    try {
                        double angle = atof(text1);
                        result = std::to_string(trig.secant(angle));
                    } catch (...) {
                        result = "Invalid input";
                    }
                } else if (IsMouseOverButton(cotButton)) {
                    try {
                        double angle = atof(text1);
                        result = std::to_string(trig.cotangent(angle));
                    } catch (...) {
                        result = "Invalid input";
                    }
                } else if (IsMouseOverButton(arcsinButton)) {
                    try {
                        double angle = atof(text1);
                        result = std::to_string(trig.arcsine(angle));
                    } catch (...) {
                        result = "Invalid input";
                    }
                } else if (IsMouseOverButton(arccosButton)) {
                    try {
                        double angle = atof(text1);
                        result = std::to_string(trig.arccosine(angle));
                    } catch (...) {
                        result = "Invalid input";
                    }
                } else if (IsMouseOverButton(arctanButton)) {
                    try {
                        double angle = atof(text1);
                        result = std::to_string(trig.arctangent(angle));
                    } catch (...) {
                        result = "Invalid input";
                    }
                } else if (IsMouseOverButton(arccscButton)) {
                    try {
                        double angle = atof(text1);
                        result = std::to_string(trig.arccosecant(angle));
                    } catch (...) {
                        result = "Invalid input";
                    }
                } else if (IsMouseOverButton(arcsecButton)) {
                    try {
                        double angle = atof(text1);
                        result = std::to_string(trig.arcsecant(angle));
                    } catch (...) {
                        result = "Invalid input";
                    }
                } else if (IsMouseOverButton(cotButton)) {
                    try {
                        double angle = atof(text1);
                        result = std::to_string(trig.arccotangent(angle));
                    } catch (...) {
                        result = "Invalid input";
                    }
                }
            }
        } 
        //TRIGONOMETRYSCREEN ends
        //HYPERBOLICSCREEN starts
        else if (currentScreen == Screens::HYPERBOLICSCREEN) {
            HandleTextInput(text1, 50, isTextBox1Active = true);
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                if (IsMouseOverButton(sinhButton)) {
                    try {
                        double angle = atof(text1);
                        result = std::to_string(hyp.sinh(angle));
                    } catch (...) {
                        result = "Invalid input";
                    }
                } else if (IsMouseOverButton(coshButton)) {
                    try {
                        double angle = atof(text1);
                        result = std::to_string(hyp.cosh(angle));
                    } catch (...) {
                        result = "Invalid input";
                    }
                } else if (IsMouseOverButton(tanhButton)) {
                    try {
                        double angle = atof(text1);
                        result = std::to_string(hyp.tanh(angle));
                    } catch (...) {
                        result = "Invalid input";
                    }
                } else if (IsMouseOverButton(cschButton)) {
                    try {
                        double angle = atof(text1);
                        result = std::to_string(hyp.csch(angle));
                    } catch (...) {
                        result = "Invalid input";
                    }
                } else if (IsMouseOverButton(sechButton)) {
                    try {
                        double angle = atof(text1);
                        result = std::to_string(hyp.sech(angle));
                    } catch (...) {
                        result = "Invalid input";
                    }
                } else if (IsMouseOverButton(cothButton)) {
                    try {
                        double angle = atof(text1);
                        result = std::to_string(hyp.coth(angle));
                    } catch (...) {
                        result = "Invalid input";
                    }
                } else if (IsMouseOverButton(arcsinhButton)) {
                    try {
                        double angle = atof(text1);
                        result = std::to_string(hyp.arcsinh(angle));
                    } catch (...) {
                        result = "Invalid input";
                    }
                } else if (IsMouseOverButton(arccoshButton)) {
                    try {
                        double angle = atof(text1);
                        result = std::to_string(hyp.arccosh(angle));
                    } catch (...) {
                        result = "Invalid input";
                    }
                } else if (IsMouseOverButton(arctanhButton)) {
                    try {
                        double angle = atof(text1);
                        result = std::to_string(hyp.arctanh(angle));
                    } catch (...) {
                        result = "Invalid input";
                    }
                } else if (IsMouseOverButton(arccschButton)) {
                    try {
                        double angle = atof(text1);
                        result = std::to_string(hyp.arccsch(angle));
                    } catch (...) {
                        result = "Invalid input";
                    }
                } else if (IsMouseOverButton(arcsechButton)) {
                    try {
                        double angle = atof(text1);
                        result = std::to_string(hyp.arcsech(angle));
                    } catch (...) {
                        result = "Invalid input";
                    }
                } else if (IsMouseOverButton(arccothButton)) {
                    try {
                        double angle = atof(text1);
                        result = std::to_string(hyp.arccoth(angle));
                    } catch (...) {
                        result = "Invalid input";
                    }
                }
            }
        } 
        //HYPERBOLICSCREEN ends
        //VECTORSCREEN starts
        else if (currentScreen == Screens::VECTORSCREEN) {
            HandleTextInput(text1, 50, isTextBox1Active);
            HandleTextInput(text2, 50, isTextBox2Active);
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                if (IsMouseOverButton(textBox1)) {
                    isTextBox1Active = true;
                    isTextBox2Active = false;
                } else if (IsMouseOverButton(textBox2)) {
                    isTextBox1Active = false;
                    isTextBox2Active = true;
                } else if (IsMouseOverButton(dotproductButton)) {
                    Vector v1 = parseVector(std::string(text1));
                    Vector v2 = parseVector(std::string(text2));
                    result = std::to_string(v1.dotProduct(v1));
                } else if (IsMouseOverButton(crossproductButton)) {
                    Vector v1 = parseVector(std::string(text1));
                    Vector v2 = parseVector(std::string(text2));
                    Vector res = v1.crossProduct(v2);
                    result = res.toString();
                } else if (IsMouseOverButton(addVectorButton)) {
                    Vector v1 = parseVector(std::string(text1));
                    Vector v2 = parseVector(std::string(text2));
                    Vector res = v1 + v2;
                    result = res.toString();
                } else if (IsMouseOverButton(subtractVectorButton)) {
                    Vector v1 = parseVector(std::string(text1));
                    Vector v2 = parseVector(std::string(text2));
                    Vector res = v1 - v2;
                    result = res.toString();
                } else if (IsMouseOverButton(magnitudeButton)) {
                    Vector v1 = parseVector(std::string(text1));
                    Vector v2 = parseVector(std::string(text2));
                    result = "Magnitude of first = " + std::to_string(v1.magnitude()) + "\n\n";
                    result += "Magnitude of second = " + std::to_string(v2.magnitude());
                } 
            }
        }
        //VECTORSCREEN starts
        // Drawing Buttons
        BeginDrawing();
        ClearBackground(RAYWHITE);
        if (currentScreen == Screens::MAINSCREEN) {
            DrawText("Calculator", 10, 10, 20, DARKGRAY);
            DrawRectangleLinesEx((Rectangle){50, 40, 750, 100}, 5, DARKGRAY);
            DrawText(input.c_str(), 60, 60, 25, DARKGRAY);
            DrawText(result.c_str(), 60, 100, 25, DARKGRAY);
            for (int i = 0; i < 18; ++i) {
                DrawButton(buttons[i], buttonLabels[i], 20, IsMouseOverButton(buttons[i])? GRAY : LIGHTGRAY);
            }
            DrawButton(trigonometryButton, "Trigonometry", 20, (IsMouseOverButton(trigonometryButton))? GRAY : LIGHTGRAY);
            DrawButton(hyperbolicButton, "Hyperbolic", 20, (IsMouseOverButton(hyperbolicButton))? GRAY : LIGHTGRAY);
            DrawButton(clearButton, "CLR", 20, IsMouseOverButton(clearButton)? GRAY : LIGHTGRAY);
            DrawButton(equationsButton,          "Equations", 20, IsMouseOverButton(equationsButton)? GRAY : LIGHTGRAY);
            DrawButton(combinationsButton,               "C", 20, IsMouseOverButton(combinationsButton)? GRAY : LIGHTGRAY);
            DrawButton(permutationsButton,               "P", 20, IsMouseOverButton(permutationsButton)? GRAY : LIGHTGRAY);
            DrawButton(numberSystemButton,  "Number Systems", 18, IsMouseOverButton(numberSystemButton)? GRAY : LIGHTGRAY);
            DrawButton(factorialButton,          "Factorial", 20, IsMouseOverButton(factorialButton)? GRAY : LIGHTGRAY);
            DrawButton(bitwiseButton,              "Bitwise", 20, IsMouseOverButton(bitwiseButton)? GRAY : LIGHTGRAY);
            DrawButton(integrationButton,      "Integration", 20, IsMouseOverButton(integrationButton)? GRAY : LIGHTGRAY);
            DrawButton(differentiationButton, "Differential", 20, IsMouseOverButton(differentiationButton)? GRAY : LIGHTGRAY);
            DrawButton(naturalLogarithmButton,          "ln", 20, IsMouseOverButton(naturalLogarithmButton)? GRAY : LIGHTGRAY);
            DrawButton(commonLogarithmButton,          "log", 20, IsMouseOverButton(commonLogarithmButton)? GRAY : LIGHTGRAY);
            DrawButton(squareRootButton,              "sqrt", 20, IsMouseOverButton(squareRootButton)? GRAY : LIGHTGRAY);
            DrawButton(leftParenthesisButton, "(", 20, IsMouseOverButton(leftParenthesisButton)? GRAY : LIGHTGRAY);
            DrawButton(rightParenthesisButton, ")", 20, IsMouseOverButton(rightParenthesisButton)? GRAY : LIGHTGRAY);
            DrawButton(piButton, "pi", 20, IsMouseOverButton(piButton)? GRAY : LIGHTGRAY);
            DrawButton(eButton, "e", 20, IsMouseOverButton(eButton)? GRAY : LIGHTGRAY);
            DrawButton(vectorButton, "Vector", 20, IsMouseOverButton(vectorButton)? GRAY : LIGHTGRAY);
        } else if (currentScreen == Screens::EQUATIONSSCREEN) {
            DrawButton(backButton, "BACK", 20, IsMouseOverButton(backButton)? GRAY : LIGHTGRAY) ;
            DrawButton(linearButton, "Linear", 20, currentEquationType == EquationType::LINEAR? DARKGRAY : (IsMouseOverButton(linearButton)? GRAY : LIGHTGRAY));
            DrawButton(quadraticButton, "Quadratic", 20, currentEquationType == EquationType::QUADRATIC? DARKGRAY : (IsMouseOverButton(quadraticButton)? GRAY : LIGHTGRAY));
            DrawButton(cubicButton, "Cubic", 20, currentEquationType == EquationType::CUBIC? DARKGRAY :(IsMouseOverButton(cubicButton)? GRAY : LIGHTGRAY));
            DrawButton(quarticButton, "Quartic", 20, currentEquationType == EquationType::QUARTIC? DARKGRAY : (IsMouseOverButton(quarticButton)? GRAY : LIGHTGRAY));
            DrawButton(solveButton, "Solve", 20, (IsMouseOverButton(solveButton)? GRAY : LIGHTGRAY));
            if (currentEquationType == EquationType::LINEAR) {
                DrawText("Enter coefficient for x:", 50, 215, 20, BLACK);
                DrawTextBox(firstcoeff, coeff1, 20, coeff1_active? LIGHTGRAY : GRAY);
                DrawText("Enter constant:", 50, 315, 20, BLACK);
                DrawTextBox(secondcoeff, coeff2, 20, coeff2_active? LIGHTGRAY : GRAY);
                DrawText("Result:", 50, 415, 30, BLACK);
                DrawText(result.c_str(), 50, 445, 27, BLACK);
            } else if (currentEquationType == EquationType::QUADRATIC) {
                DrawText("Enter coefficient for x^2:", 50, 215, 20, BLACK);
                DrawTextBox(firstcoeff, coeff1, 20, coeff1_active? LIGHTGRAY : GRAY);
                DrawText("Enter coefficient for x:", 50, 315, 20, BLACK);
                DrawTextBox(secondcoeff, coeff2, 20, coeff2_active? LIGHTGRAY : GRAY);
                DrawText("Enter constant:", 50, 415, 20, BLACK);
                DrawTextBox(thirdcoeff, coeff3, 20, coeff3_active? LIGHTGRAY : GRAY);
                DrawText("Result:", 50, 515, 30, BLACK);
                DrawText(result.c_str(), 50, 545, 27, BLACK);
            } else if (currentEquationType == EquationType::CUBIC) {
                DrawText("Enter coefficient for x^3:", 50, 215, 20, BLACK);
                DrawTextBox(firstcoeff, coeff1, 20, coeff1_active? LIGHTGRAY : GRAY);
                DrawText("Enter coefficient for x^2:", 50, 315, 20, BLACK);
                DrawTextBox(secondcoeff, coeff2, 20, coeff2_active? LIGHTGRAY : GRAY);
                DrawText("Enter coefficient for x:", 50, 415, 20, BLACK);
                DrawTextBox(thirdcoeff, coeff3, 20, coeff3_active? LIGHTGRAY : GRAY);
                DrawText("Enter constant:", 50, 515, 20, BLACK);
                DrawTextBox(fourthcoeff, coeff4, 20, coeff4_active? LIGHTGRAY : GRAY);
                DrawText("Result:", 50, 615, 30, BLACK);
                DrawText(result.c_str(), 50, 645, 27, BLACK);
            } else if (currentEquationType == EquationType::QUARTIC) {
                DrawText("Enter coefficient for x^4:", 50, 215, 20, BLACK);
                DrawTextBox(firstcoeff, coeff1, 20, coeff1_active? LIGHTGRAY : GRAY);
                DrawText("Enter coefficient for x^3:", 50, 315, 20, BLACK);
                DrawTextBox(secondcoeff, coeff2, 20, coeff2_active? LIGHTGRAY : GRAY);
                DrawText("Enter coefficient for x^2:", 50, 415, 20, BLACK);
                DrawTextBox(thirdcoeff, coeff3, 20, coeff3_active? LIGHTGRAY : GRAY);
                DrawText("Enter coefficient for x:", 50, 515, 20, BLACK);
                DrawTextBox(fourthcoeff, coeff4, 20, coeff4_active? LIGHTGRAY : GRAY);
                DrawText("Enter constant:", 50, 615, 20, BLACK);
                DrawTextBox(fifthcoeff, coeff5, 20, coeff5_active? LIGHTGRAY : GRAY);
                DrawText("Result:", 50, 715, 30, BLACK);
                DrawText(result.c_str(), 50, 745, 27, BLACK);
            } else {
                DrawText("Please Select an equation type!", 50, 450, 40, BLACK);
            }
        } else if (currentScreen == Screens::BITWISESCREEN) {
            DrawButton(backButton, "BACK", 20, IsMouseOverButton(backButton)? GRAY : LIGHTGRAY);
            DrawText("Please input first number:", 50, 110, 25, BLACK);
            DrawTextBox(textBox1, text1, 20, isTextBox1Active? LIGHTGRAY : GRAY);
            DrawText("Please input second number:", 50, 225, 25, BLACK);
            DrawTextBox(textBox2, text2, 20, isTextBox2Active? LIGHTGRAY : GRAY);
            DrawText("Result:", 50, 400, 30, BLACK);
            DrawText(result.c_str(), 50, 450, 25, BLACK);
            DrawButton(andButton, "AND", 20, IsMouseOverButton(andButton)? GRAY : LIGHTGRAY);
            DrawButton(orButton,  "OR" , 20, IsMouseOverButton(orButton)? GRAY : LIGHTGRAY);
            DrawButton(notButton, "NOT", 20, IsMouseOverButton(notButton)? GRAY : LIGHTGRAY);
            DrawButton(xorButton, "XOR", 20, IsMouseOverButton(xorButton)? GRAY : LIGHTGRAY);
        } else if (currentScreen == Screens::NUMBERSYSTEMSCREEN) {
            DrawButton(backButton, "BACK", 20, IsMouseOverButton(backButton)? GRAY : LIGHTGRAY);
            DrawText("Enter a number:", 50, 100, 25, BLACK);
            DrawTextBox(textBox1, text1, 20, isTextBox1Active? LIGHTGRAY : GRAY);
            DrawText("Result:", 50, 250, 30, BLACK);
            DrawText(result.c_str(), 50, 300, 25, BLACK);
            DrawButton(decToBinaryButton, "Decimal to Binary"    , 20, IsMouseOverButton(decToBinaryButton)? GRAY : LIGHTGRAY);
            DrawButton(decToOctalButton,  "Decimal to Octal"     , 20, IsMouseOverButton(decToOctalButton)? GRAY : LIGHTGRAY);
            DrawButton(decToHexaButton,   "Decimal to Hexa"      , 20, IsMouseOverButton(decToHexaButton)? GRAY : LIGHTGRAY);
            DrawButton(binaryToDecimalButton, "Binary to Decimal", 20, IsMouseOverButton(binaryToDecimalButton)? GRAY : LIGHTGRAY);
            DrawButton(binaryToOctalButton,   "Binary to Octal"  , 20, IsMouseOverButton(binaryToOctalButton)? GRAY : LIGHTGRAY);
            DrawButton(binaryToHexaButton,    "Binary to Hexa"   , 20, IsMouseOverButton(binaryToHexaButton)? GRAY : LIGHTGRAY);
            DrawButton(octalToBinaryButton,   "Octal to Binary"  , 20, IsMouseOverButton(octalToBinaryButton)? GRAY : LIGHTGRAY);
            DrawButton(octalToDecimalButton,  "Octal to Decimal" , 20, IsMouseOverButton(octalToDecimalButton)? GRAY : LIGHTGRAY);
            DrawButton(octalToHexaButton,     "Octal to Hexa"    , 20, IsMouseOverButton(octalToHexaButton)? GRAY : LIGHTGRAY);
            DrawButton(hexaToBinaryButton,  "Hexa to Binary"     , 20, IsMouseOverButton(hexaToBinaryButton)? GRAY : LIGHTGRAY);
            DrawButton(hexaToOctalButton,   "Hexa to Octal"      , 20, IsMouseOverButton(hexaToOctalButton)? GRAY : LIGHTGRAY);
            DrawButton(hexaToDecimalButton, "Hexa to Decimal"    , 20, IsMouseOverButton(hexaToDecimalButton)? GRAY : LIGHTGRAY);
        } else if (currentScreen == Screens::DIFFERENTIALSCREEN) {
            DrawButton(backButton, "BACK", 20, IsMouseOverButton(backButton)? GRAY : LIGHTGRAY);
            DrawText("Please enter expression:",  50, 100, 25, BLACK);
            DrawTextBox(textBox1, text1, 20, isTextBox1Active? LIGHTGRAY : GRAY);
            DrawText("Differential:", 50, 250, 30, BLACK);
            DrawText(result.c_str(), 50, 300, 25, BLACK);
            DrawButton(calculateButton, "Differentiate", 30, IsMouseOverButton(calculateButton)? GRAY : LIGHTGRAY);
        } else if (currentScreen == Screens::INTEGRALSCREEN) {
            DrawButton(backButton, "BACK", 20, IsMouseOverButton(backButton)? GRAY : LIGHTGRAY);
            DrawText("Please enter expression:",  50, 100, 25, BLACK);
            DrawTextBox(textBox1, text1, 20, isTextBox1Active? LIGHTGRAY : GRAY);
            DrawText("Integral:", 50, 250, 30, BLACK);
            DrawText(result.c_str(), 50, 300, 25, BLACK);
            DrawButton(calculateButton, "Integrate", 30, IsMouseOverButton(calculateButton)? GRAY : LIGHTGRAY);
        } else if (currentScreen == Screens::TRIGONOMETRYSCREEN) {
            DrawText("Please input a number:", 50, 110, 25, BLACK);
            DrawTextBox(textBox1, text1, 20, isTextBox1Active? LIGHTGRAY : GRAY);
            DrawButton(backButton, "BACK", 20, IsMouseOverButton(backButton)? GRAY : LIGHTGRAY);
            DrawButton(sinButton,  "sin", 20, (IsMouseOverButton(sinButton))? GRAY : LIGHTGRAY);
            DrawButton(cosButton,  "cos", 20, (IsMouseOverButton(cosButton))? GRAY : LIGHTGRAY);
            DrawButton(tanButton,  "tan", 20, (IsMouseOverButton(tanButton))? GRAY : LIGHTGRAY);
            DrawButton(cotButton,  "cot", 20, (IsMouseOverButton(cotButton))? GRAY : LIGHTGRAY);
            DrawButton(cscButton,  "csc", 20, (IsMouseOverButton(cscButton))? GRAY : LIGHTGRAY);
            DrawButton(secButton,  "sec", 20, (IsMouseOverButton(secButton))? GRAY : LIGHTGRAY);
            DrawButton(arcsinButton,  "asin", 20, (IsMouseOverButton(arcsinButton))? GRAY : LIGHTGRAY);
            DrawButton(arccosButton,  "acos", 20, (IsMouseOverButton(arccosButton))? GRAY : LIGHTGRAY);
            DrawButton(arctanButton,  "atan", 20, (IsMouseOverButton(arctanButton))? GRAY : LIGHTGRAY);
            DrawButton(arccotButton,  "acot", 20, (IsMouseOverButton(arccotButton))? GRAY : LIGHTGRAY);
            DrawButton(arccscButton,  "acsc", 20, (IsMouseOverButton(arccscButton))? GRAY : LIGHTGRAY);
            DrawButton(arcsecButton,  "asec", 20, (IsMouseOverButton(arcsecButton))? GRAY : LIGHTGRAY);
            DrawText("Result:", 50, 600, 30, BLACK);
            DrawText(result.c_str(), 50, 650, 27, BLACK);
        } else if (currentScreen == Screens::HYPERBOLICSCREEN) {
            DrawText("Please input a number:", 50, 110, 25, BLACK);
            DrawTextBox(textBox1, text1, 20, isTextBox1Active? LIGHTGRAY : GRAY);
            DrawButton(backButton, "BACK", 20, IsMouseOverButton(backButton)? GRAY : LIGHTGRAY);
            DrawButton(sinhButton, "sinh", 20, IsMouseOverButton(sinhButton)? GRAY : LIGHTGRAY);
            DrawButton(coshButton, "cosh", 20, IsMouseOverButton(coshButton)? GRAY : LIGHTGRAY);
            DrawButton(tanhButton, "tanh", 20, IsMouseOverButton(tanhButton)? GRAY : LIGHTGRAY);
            DrawButton(cothButton, "coth", 20, IsMouseOverButton(cothButton)? GRAY : LIGHTGRAY);
            DrawButton(cschButton, "csch", 20, IsMouseOverButton(cschButton)? GRAY : LIGHTGRAY);
            DrawButton(sechButton, "sech", 20, IsMouseOverButton(sechButton)? GRAY : LIGHTGRAY);
            DrawButton(arcsinhButton,  "asinh", 20, (IsMouseOverButton(arcsinhButton))? GRAY : LIGHTGRAY);
            DrawButton(arccoshButton,  "acosh", 20, (IsMouseOverButton(arccoshButton))? GRAY : LIGHTGRAY);
            DrawButton(arctanhButton,  "atanh", 20, (IsMouseOverButton(arctanhButton))? GRAY : LIGHTGRAY);
            DrawButton(arccothButton,  "acoth", 20, (IsMouseOverButton(arccothButton))? GRAY : LIGHTGRAY);
            DrawButton(arccschButton,  "acsch", 20, (IsMouseOverButton(arccschButton))? GRAY : LIGHTGRAY);
            DrawButton(arcsechButton,  "asech", 20, (IsMouseOverButton(arcsechButton))? GRAY : LIGHTGRAY);
            DrawText("Result:", 50, 600, 30, BLACK);
            DrawText(result.c_str(), 50, 650, 27, BLACK);
        } else if (currentScreen == Screens::VECTORSCREEN) {
            DrawButton(backButton, "Back", 20, IsMouseOverButton(backButton)? GRAY : LIGHTGRAY);
            DrawText("Please input first number:", 50, 110, 25, BLACK);
            DrawTextBox(textBox1, text1, 25, isTextBox1Active? LIGHTGRAY : GRAY);
            DrawText("Please input second number:", 50, 225, 25, BLACK);
            DrawTextBox(textBox2, text2, 25, isTextBox2Active? LIGHTGRAY : GRAY);
            DrawText("Result:", 50, 400, 30, BLACK);
            DrawText(result.c_str(), 50, 450, 25, BLACK);
            DrawButton(dotproductButton,   "Dot product", 20, (IsMouseOverButton(dotproductButton))? GRAY : LIGHTGRAY);
            DrawButton(crossproductButton, "Cross product", 20, (IsMouseOverButton(crossproductButton))? GRAY : LIGHTGRAY);
            DrawButton(magnitudeButton, "Magnitude", 20, (IsMouseOverButton(magnitudeButton))? GRAY : LIGHTGRAY);
            DrawButton(addVectorButton, "Add", 20, (IsMouseOverButton(addVectorButton))? GRAY : LIGHTGRAY);
            DrawButton(subtractVectorButton, "Subtract", 20, (IsMouseOverButton(subtractVectorButton))? GRAY : LIGHTGRAY);
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}