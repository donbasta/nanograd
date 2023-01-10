#include <bits/stdc++.h>
using namespace std;

struct C {
    function<void(void)> funcC;
    C() {}
};

void test(C& c) {
    int* a;
    a = new int(3);
    // cout << "c di luar " << &c << '\n';
    cout << "a di luar tes 1 " << a << '\n';
    function<void(void)> fu = [&]() -> void {
        // cout << "ngentot\n";
        // cout << "c di dalem " << &c << '\n';
        cout << "a di dalam tes 1 " << a << '\n';
    };
    c.funcC = fu;
}

C& test2() {
    C* testC = new C();
    cout << "testC mulamula test 2 " << testC << "\n";
    int* a;
    a = new int(3);
    cout << "a di luar tes 2 " << a << '\n';

    function<void(void)> fu = [&]() -> void {
        cout << "testC di dalam test 2 " << testC << '\n';
        cout << "a di dalem tes 2 " << a << '\n';
    };
    testC->funcC = fu;
    return *testC;
}

int main() {
    C testC;
    test(testC);
    testC.funcC();

    C test2C = test2();
    cout << "testC akhir test 2 " << &test2C << "\n";
    test2C.funcC();
}