#include <iostream>
using namespace std;

void tim_yen_ngua(int a[][100], int m, int n) {
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            bool la_min_hang = true;
            bool la_max_cot = true;
            
            // Kiem tra min hang
            for(int k = 0; k < n; k++) {
                if(a[i][k] < a[i][j]) {
                    la_min_hang = false;
                    break;
                }
            }
            
            // Kiem tra max cot
            for(int k = 0; k < m; k++) {
                if(a[k][j] > a[i][j]) {
                    la_max_cot = false;
                    break;
                }
            }
            
            if(la_min_hang && la_max_cot) {
                cout << "Diem yen ngua tai (" << i << "," << j << "): " << a[i][j] << endl;
            }
        }
    }
}

int main() {
    int m, n;
    cout << "Nhap kich thuoc ma tran (m n): ";
    cin >> m >> n;
    
    int a[100][100];
    cout << "Nhap ma tran:\n";
    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
            cin >> a[i][j];
            
    tim_yen_ngua(a, m, n);
    return 0;
}
