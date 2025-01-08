#include <iostream>
using namespace std;

// Thuật toán cơ sở: lặp hết n
unsigned long long mod_pow(int base, int exp, int mod) {
    long long result = 1;
    for (int i = 0; i < exp; ++i) {
        result = (result * base) % mod;
    }
    return result;
}

int main() {
    int n = 1000000000;
    int divisor = 54;

    int modResult_n = mod_pow(55, n, divisor);
    int modResult_n1 = mod_pow(55, n + 1, divisor);
    int result = (modResult_n1 - modResult_n + divisor) % divisor;

    if (result == 0) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }

    cout << "55^" << n << " % 54 = " << modResult_n << endl;
    cout << "55^" << (n + 1) << " % 54 = " << modResult_n1 << endl;

    return 0;
}
