#include <iostream>
using namespace std;

unsigned long long to_number(const char* s) {
    unsigned long long num = 0;
    for(int i = 0; s[i] != '\0'; i++) {
        num = num * 10 + (s[i] - '0');
    }
    return num;
}

int main() {
    char s[100];
    cout << "Nhap chuoi so: ";
    cin >> s;
    cout << "So: " << to_number(s);
    return 0;
}
