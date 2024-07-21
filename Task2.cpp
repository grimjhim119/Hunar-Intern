#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// Function to read number and base from user
void readInput(string& number, int& sourceBase, int& targetBase) {
    cout << "Enter the number to convert: "<<endl;
    cin >> number;
    cout << "Number entered by you: "<<number<<endl;

    cout << "Enter the source base (2, 8, 10, 16): "<<endl;
    cin >> sourceBase;
    cout << "Source base entered by you: "<<sourceBase<<endl;

    cout << "Enter the target base (2, 8, 10, 16): "<<endl;
    cin >> targetBase;
    cout << "Target base entered by you: "<<targetBase<<endl;
}

// Function to convert a number from any base to decimal
int toDecimal(string number, int base) {
    int decimalValue = 0;
    int power = 1;
    int numLength = number.length();
    
    for (int i = numLength - 1; i >= 0; i--) {
        int digitValue = (isdigit(number[i])) ? (number[i] - '0') : (toupper(number[i]) - 'A' + 10);
        decimalValue += digitValue * power;
        power *= base;
    }
    
    return decimalValue;
}

// Function to convert a decimal number to any base
string fromDecimal(int decimalValue, int base) {
    string result = "";
    
    while (decimalValue > 0) {
        int remainder = decimalValue % base;
        char digit = (remainder < 10) ? (remainder + '0') : (remainder - 10 + 'A');
        result = digit + result;
        decimalValue /= base;
    }
    
    return result;
}

// Function to convert a fractional part from any base to decimal
double fractionalToDecimal(string fraction, int base) {
    double decimalValue = 0.0;
    double fractionPower = 1.0;
    
    for (char digit : fraction) {
        int digitValue = (isdigit(digit)) ? (digit - '0') : (toupper(digit) - 'A' + 10);
        fractionPower /= base;
        decimalValue += digitValue * fractionPower;
    }
    
    return decimalValue;
}

// Function to convert a decimal fraction to any base
string fractionalFromDecimal(double decimalFraction, int targetBase, int precision = 10) {
    string result = ".";
    
    while (precision--) {
        decimalFraction *= targetBase;
        int integerPart = static_cast<int>(decimalFraction);
        char digit = (integerPart < 10) ? (integerPart + '0') : (integerPart - 10 + 'A');
        result += digit;
        decimalFraction -= integerPart;
    }
    
    return result;
}

// Function to display the converted number
void displayResult(string integerPart, string fractionalPart = "") {
    cout << "Converted number: " << integerPart;
    if (!fractionalPart.empty()) {
        cout << fractionalPart;
    }
    cout << endl;
}

int main() {
    string number;
    int sourceBase, targetBase;

    // Step 1: Read input
    readInput(number, sourceBase, targetBase);

    // Step 2: Convert integer part (if any)
    size_t dotPos = number.find('.');
    string integerPart = number.substr(0, dotPos);
    string fractionalPart;

    if (dotPos != string::npos) {
        // Fractional part exists
        fractionalPart = number.substr(dotPos);
    }

    // Step 3: Convert integer part
    int decimalValue = toDecimal(integerPart, sourceBase);
    string convertedInteger = fromDecimal(decimalValue, targetBase);

    // Step 4: Convert fractional part (if any)
    if (!fractionalPart.empty()) {
        double decimalFraction = fractionalToDecimal(fractionalPart.substr(1), sourceBase);
        string convertedFractional = fractionalFromDecimal(decimalFraction, targetBase);
        displayResult(convertedInteger, convertedFractional);
    } else {
        displayResult(convertedInteger);
    }

    return 0;
}
