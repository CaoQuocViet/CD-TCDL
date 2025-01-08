// all about pointers on C++
#include <iostream>
using namespace std;

int main() {
    int a = 10;
    int *p = &a;
    cout << "a = " << a << endl;
    cout << "*p = " << *p << endl;
    cout << "&a = " << &a << endl;
    cout << "p = " << p << endl;
    cout << "&p = " << &p << endl;

    cout << "sizeof(a) = " << sizeof(a) << endl;
    cout << "sizeof(&a) = " << sizeof(&a) << endl;
    cout << "sizeof(p) = " << sizeof(p) << endl;
    cout << "sizeof(*p) = " << sizeof(*p) << endl;
    cout << "sizeof(&p) = " << sizeof(&p) << endl;
    return 0;
}

// a = 10
//*p = 10
//&a = 0x7ffeea3c4b8c
//p = 0x7ffeea3c4b8c
//&p = 0x7ffeea3c4b80

// sizeof(a) = 4
// sizeof(&a) = 8
// sizeof(p) = 8
// sizeof(*p) = 4
// sizeof(&p) = 8