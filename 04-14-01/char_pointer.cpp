#include <iostream>
using namespace std;

int main() {
    // s là mảng kí tự, mỗi ô nhớ là một số (địa chỉ của kí tự) được mã hóa thành kí tự
    // Khác mảng ở chỗ chuỗi có lưu kí tự kết thúc chuỗi '\0' (null)
    char s[] = "Hello";

    char p[4] = "Hi";
    p[3] = 'k';

    cout << p << endl; // In ra Hi

    char *c[4] = "Hi";
    c[4] = k;

    cout << c << endl; // In ra Hi

    const char *q = "Hi"; // Cho tạo, chỉ đọc, không thay đổi (Read only)
    return 0;
}