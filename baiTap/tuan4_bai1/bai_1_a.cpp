#include <iostream>
using namespace std;

// Tinh giai thua
unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for(int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

// Tinh to hop theo cong thuc giai thua
unsigned long long C(int n, int k) {
    if (k > n) return 0;
    return factorial(n) / (factorial(k) * factorial(n - k));
}

int main() {
    int n, k;
    cout << "Nhap n, k: ";
    cin >> n >> k;
    cout << "C(" << n << "," << k << ") = " << C(n, k);
    return 0;
}
