#include <iostream>
using namespace std;

void to_str(unsigned long long num, char* s) {
    // Xu ly truong hop num = 0
    if(num == 0) {
        s[0] = '0';
        s[1] = '\0';
        return;
    }
    
    // Tim so chu so
    int len = 0;
    unsigned long long temp = num;
    while(temp > 0) {
        temp /= 10;
        len++;
    }
    
    // Chuyen doi tung chu so
    s[len] = '\0';
    while(num > 0) {
        s[--len] = num % 10 + '0';
        num /= 10;
    }
}

int main() {
    unsigned long long num;
    char s[100];
    cout << "Nhap so: ";
    cin >> num;
    to_str(num, s);
    cout << "Chuoi: " << s;
    return 0;
}
