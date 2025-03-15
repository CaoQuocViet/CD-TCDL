#include <iostream>
using namespace std;

long long combination(int n, int k) {
    if (k > n) return 0;
    
    if (k > n - k) {
        k = n - k;
    }

    long long result = 1;
    
    for (int i = 1; i <= k; i++) {
        result *= n--;
        result /= i;
    }

    return result;
}

int main() {
    int n = 30, k = 2;
    cout << "C(" << n << ", " << k << ") = " << combination(n, k) << endl;
    return 0;
}
