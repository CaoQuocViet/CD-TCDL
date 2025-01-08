#include <iostream>
using namespace std;

// Thuật toán modular exponentiation
unsigned long long mod_pow(int base, int exp, int mod) {
    unsigned long long result = 1;
    unsigned long long current_base = base % mod;  // Lấy base % mod để giảm kích thước
    while (exp > 0) {
        if (exp % 2 == 1) {  // Nếu exp lẻ, nhân kết quả với current_base
            result = (result * current_base) % mod;
        }
        current_base = (current_base * current_base) % mod;  // Bình phương base
        exp /= 2;  // Chia đôi exp
    }
    return result;
}

int main() {
    unsigned long long n = 10000000000000;  // Ví dụ n = 10^9
    int divisor = 54;

    // Tính 55^n % 54
    unsigned long long modResult_n = mod_pow(55, n, divisor);

    // Tính 55^(n+1) % 54
    unsigned long long modResult_n1 = mod_pow(55, n + 1, divisor);

    // Tính (55^(n+1) - 55^n) % 54
    int result = (modResult_n1 - modResult_n + divisor) % divisor;

    // Kiểm tra kết quả
    if (result == 0) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }

    // In kết quả để kiểm tra
    cout << "55^" << n << " % 54 = " << modResult_n << endl;
    cout << "55^" << (n + 1) << " % 54 = " << modResult_n1 << endl;

    return 0;
}
