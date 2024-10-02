# ProCalc

A powerful calculator built using C++ with a simple, intuitive graphical user interface implemented in Raylib. This project covers basic arithmetic operations, number system conversions, and advanced mathematical functions such as permutations, combinations, and quartic equation solving.

## Features
- Basic Arithmetic Operations: Addition, subtraction, multiplication, and division.
- Percentage Calculations: Easily compute percentages.
- Bracket Operations: Support for nested expressions with brackets.
- Permutations & Combinations: Calculate permutations (nPr) and combinations (nCr).
- Roots of Equations: Find roots for up to quartic (4th degree) equations.
- Number System Conversions: Convert numbers between binary, octal, decimal, and hexadecimal systems.
- Calculus: Supports basic differentiation and integration

## Getting Started
Prerequisites
To compile and run this project, you need:

A C++ compiler (GCC, Clang, MSVC, etc.)
Raylib library installed on your system
Installation
Clone the repository:
```
git clone https://github.com/M-Sami27/Pro-Calc
cd calculator-raylib
```
Install [Raylib](https://www.raylib.com/index.html) following the instructions on the official site.

Compile the project:
```
Copy code
g++ main.cpp -o main.exe -lraylib
```
Run the executable:
```
./main
```
## Usage
#### Basic Operations:
- Use the calculator's buttons to perform addition, subtraction, multiplication, division, and percentages.
- Brackets: Use brackets for grouping expressions as needed.
#### Advanced Functions:
- Select the nPr or nCr options to calculate permutations or combinations.
- Use the root function to solve up to quartic equations.
- Number System Conversions: Convert between binary, octal, decimal, and hexadecimal by selecting the appropriate mode.
## User Interface
The UI is designed for ease of use with interactive buttons for each operation. The Raylib library ensures a smooth and responsive interface that makes navigating between features easy and enjoyable.

## File Structure
main.cpp: Contains the main logic for calculator operations and UI interaction.
ScientificCalculator.h: Contains the core calculator functionalities.

## Built With
- C++ - The core programming language used.
- Raylib - For creating the graphical user interface.

## Future Improvements
- History Feature: Store previous calculations for easy reference.
- Complex Number Support: Extend operations to include complex numbers.
- Graphing Feature: Visual representation of functions and equations.
- Calculus: Allow support for complex equations
- UI: Clean up and improve the overall UI

## Contributing
Contributions are welcome! If you have ideas for improvement or encounter any issues, feel free to open an issue or submit a pull request.

## Acknowledgments
Special thanks to Raylib for making game development and graphical UI creation easy in C++.
Inspired by classic calculator designs to provide an easy-to-use interface.
