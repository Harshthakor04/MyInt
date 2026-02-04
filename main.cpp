#include <iostream>
#include "myint.h"
using namespace std;

int main() {
    MyInt a("123456789012345678901234567890");
    MyInt b("987654321098765432109876543210");

    cout << "a = " << a << "\n";
    cout << "b = " << b << "\n";
    cout << "a + b = " << (a + b) << "\n";
    cout << "a * b = " << (a * b) << "\n";

    MyInt x(999);
    cout << "x = " << x << "\n";
    cout << "x++ = " << x++ << "\n";
    cout << "after x++: " << x << "\n";
    cout << "++x = " << ++x << "\n";

    return 0;
}
