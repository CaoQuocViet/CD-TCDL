#include <iostream>
using namespace std;

// Tinh to hop dung tam giac Pascal
unsigned long long C(int n, int k) {
    if (k > n) return 0;
    unsigned long long C[100][100] = {0};
    
    // Xay dung tam giac Pascal
    for(int i = 0; i <= n; i++) {
        C[i][0] = 1;
        for(int j = 1; j <= i; j++) {
            C[i][j] = C[i-1][j-1] + C[i-1][j];
        }
    }
    return C[n][k];
}

int main() {
    int n, k;
    cout << "Nhap n, k: ";
    cin >> n >> k;
    cout << "C(" << n << "," << k << ") = " << C(n, k);
    return 0;
}
