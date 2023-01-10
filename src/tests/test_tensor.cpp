#include <bits/stdc++.h>
using namespace std;

int main() {
    // Value x = Value(2.0, "x");
    // Value y = Value(3.0, "y");
    // Value w = Value(1.0, "w");

    // Value z = x * y + w;
    // z.label = "z";

    // z.backward();

    // cout << x << '\n';
    // cout << y << '\n';
    // cout << z << '\n';
    // cout << w << '\n';

    Value x1 = Value(2.0);
    Value x2 = Value(5.0);
    Value x3 = Value(4.0);

    Value w1 = Value(4.0);
    Value w2 = Value(3.0);
    Value w3 = Value(-1.0);

    Value z = (x1 * w1 + x2 * w2 + x3 * w3).ReLU();
    z.backward();

    cout << "x1.grad: " << x1.grad << '\n';
    cout << "x2.grad: " << x2.grad << '\n';
    cout << "x3.grad: " << x3.grad << '\n';
    cout << "w1.grad: " << w1.grad << '\n';
    cout << "w2.grad: " << w2.grad << '\n';
    cout << "w3.grad: " << w3.grad << '\n';
}
