#include <iostream>
#include <cmath>
using namespace std;

double round_num(double x, int pos) {
    double factor = pow(10.0, pos);
    return round(x * factor) / factor;
}

int main() {
    double x;
    int pos;
    cout << "Nhap so thuc x: ";
    cin >> x;
    cout << "Nhap vi tri lam tron pos: ";
    cin >> pos;
    cout << "Ket qua: " << round_num(x, pos);
    return 0;
}
