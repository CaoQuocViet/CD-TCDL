#include <iostream>
#include <algorithm>
using namespace std;

double median(double x[], int n) {
    // Sap xep mang
    sort(x, x + n);
    
    // Neu so phan tu chan
    if (n % 2 == 0) {
        return (x[n/2 - 1] + x[n/2]) / 2;
    }
    // Neu so phan tu le
    return x[n/2];
}

int main() {
    int n;
    cout << "Nhap so phan tu: ";
    cin >> n;
    
    double x[1000];
    cout << "Nhap day so: ";
    for(int i = 0; i < n; i++) {
        cin >> x[i];
    }
    
    cout << "Trung vi: " << median(x, n);
    return 0;
}
