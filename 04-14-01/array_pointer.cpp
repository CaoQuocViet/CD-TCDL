#include <iostream>
using namespace std;

int main() {
    int a[5];
    a[0] = 10;
    a[1] = 20; // Là cách viết tắt của *(a + 1) = 20;
    *(a + 2) = 30;

    *(a + 4) = 50; // nhảy ra ngoài mảng, không an toàn

    *(a - 1) = 40; // nhảy ra ngoài mảng, không an toàn

    cout<< a <<endl; // Là địa chỉ, bản thân nó là địa chỉ luôn, không là con trỏ
    cout<< &a <<endl; // Thời không có ý nghĩa
    cout<< &a[0] <<endl;
    cout<< a[2] <<endl;
    cout<< a[4] <<endl; // Vẫn in được là do thực chất nó tương đương *(a + 4)
    cout<< a[-1] <<endl; // Vẫn in được là do thực chất nó tương đương *(a - 1)
    return 0;
}