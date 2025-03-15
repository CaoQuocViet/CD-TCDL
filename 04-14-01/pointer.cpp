#include <iostream>
using namespace std;

int main() {
    int a;
    a = 10;
    int *p;
    p = &a;
    p = p + 1;
    *p = 20;
    cout << "a = " << a << endl;
    cout << "*p = " << *p << endl;
    cout << "&a = " << &a << endl;
    cout << "p = " << p << endl;
    cout << "&p = " << &p << endl;

    cout << a <<endl;
    cout<< *p <<endl;
    cout<< &(*p) <<endl;
    return 0;
}