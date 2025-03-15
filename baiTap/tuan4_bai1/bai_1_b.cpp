#include <iostream>
using namespace std;

// Tinh to hop khong dung giai thua
unsigned long long C(int n, int k) {
    if (k > n) return 0;
    if (k > n/2) k = n-k;  // Toi uu hoa: C(n,k) = C(n,n-k)
    
    unsigned long long result = 1;
    for(int i = 0; i < k; i++) {
        result = result * (n - i) / (i + 1);
    }
    return result;
}

int main() {
    int n, k;
    cout << "Nhap n, k: ";
    cin >> n >> k;
    cout << "C(" << n << "," << k << ") = " << C(n, k);
    return 0;
}
