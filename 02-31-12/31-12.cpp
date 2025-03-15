// Prograam to implement power function
#include <iostream>
using namespace std;

int power(int base, int exponent) {
    int result = 1;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

int main() {
    int base, exponent;
    cout << "Enter base: ";
    cin >> base;
    cout << "Enter exponent: ";
    cin >> exponent;
    cout << base << " raised to the power of " << exponent << " is " << power(base, exponent) << endl;
    return 0;
}