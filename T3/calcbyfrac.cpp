#include <iostream>
#include <regex>
#include <string>
using namespace std;

// Function to calculate greatest common divisor
long long gcd(long long a, long long b) {
    if (a == 0)
        return b;
    else if (b == 0)
        return a;
    if (a < b)
        return gcd(a, b % a);
    else
        return gcd(b, a % b);
}

// Function to simplify a fraction
void simplifyFraction(long long& numerator, long long& denominator) {
    // Check if negative
    bool isNegative = (numerator < 0) != (denominator < 0);
    // Find the greatest common divisor
    long long commonDivisor = gcd(abs(numerator), denominator);
    // Divide both numerator and denominator by the common divisor
    numerator = abs(numerator) / commonDivisor;
    denominator /= commonDivisor;
    // If the numerator was negative, assign the sign to the numerator
    if (isNegative)
        numerator *= -1;
}

// Function to add two fractions
void addFractions(long long& num1, long long& den1, long long& num2, long long& den2) {
    // cross multiplication
    long long num = num1 * den2 + num2 * den1;
    long long den = den1 * den2;
    // Simplify the result
    simplifyFraction(num, den);
    // Update the numerator and denominator of the first fraction with the result
    num1 = num;
    den1 = den;
}

// Function to subtract two fractions
void subtractFractions(long long& num1, long long& den1, long long& num2, long long& den2) {
    // Perform subtraction of fractions
    long long num = num1 * den2 - num2 * den1;
    long long den = den1 * den2;
    // Simplify the result
    simplifyFraction(num, den);
    // Update the numerator and denominator of the first fraction with the result
    num1 = num;
    den1 = den;
}

// Function to multiply two fractions
void multiplyFractions(long long& num1, long long& den1, long long& num2, long long& den2) {
    // Perform multiplication of fractions
    long long num = num1 * num2;
    long long den = den1 * den2;
    // Simplify the result
    simplifyFraction(num, den);
    // Update the numerator and denominator of the first fraction with the result
    num1 = num;
    den1 = den;
}

// Function to divide two fractions
void divideFractions(long long& num1, long long& den1, long long& num2, long long& den2) {
    // Perform division of fractions
    long long num = num1 * den2;
    long long den = den1 * num2;
    // Ensure denominator is positive
    if (den < 0) {
        num *= -1;
        den *= -1;
    }
    // Simplify the result
    simplifyFraction(num, den);
    // Update the numerator and denominator of the first fraction with the result
    num1 = num;
    den1 = den;
}

// Function to separate a string fraction into numerator and denominator
void separate_fractions(const string& fractionStr, long long& numerator, long long& denominator) {
    size_t pos = fractionStr.find('/');
    if (pos != string::npos) {
        // Extract numerator and denominator from the string
        numerator = stoll(fractionStr.substr(0, pos));
        denominator = stoll(fractionStr.substr(pos + 1));
    } else {
        // If no '/' found, the string represents a whole number
        numerator = stoll(fractionStr);
        denominator = 1; // Denominator defaults to 1
    }
}

int main() {
    while (true) {
        string input;
        cout << "Enter a calculation (or type 'exit' to quit): ";
        getline(cin, input);

        if (input == "exit")
            break;

        // Regular expression pattern to match fractions and operations
        regex pattern("(-?\\d+/\\d+|-?\\d+)\\s*([-+*/])\\s*(-?\\d+/\\d+|-?\\d+)");
        smatch matches;

        // Check if the input matches the pattern
        if (regex_match(input, matches, pattern)) {
            // Variables to store numerators and denominators of fractions
            long long num1, den1, num2, den2;
            // Separate the first fraction from the input
            separate_fractions(matches[1], num1, den1);
            // Separate the second fraction from the input
            separate_fractions(matches[3], num2, den2);
            // Extract the operation from the input
            char operation = matches[2].str()[0];


            switch (operation) {
                case '+':
                    addFractions(num1, den1, num2, den2);
                    break;
                case '-':
                    subtractFractions(num1, den1, num2, den2);
                    break;
                case '*':
                    multiplyFractions(num1, den1, num2, den2);
                    break;
                case '/':
                    divideFractions(num1, den1, num2, den2);
                    break;
                default:
                    cout << "Invalid operation" << endl;
                    continue;
            }

            if (den1 == 1)
                cout << "Result = " << num1 << endl;
            else
                cout << "Result = " << num1 << "/" << den1 << endl;
        } else {
            cout << "Invalid input format" << endl;
        }
    }

    cout << "Thanks for using our program" << endl;
    return 0;
}
