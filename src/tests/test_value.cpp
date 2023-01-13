#include <bits/stdc++.h>
using namespace std;

void test_value_0() {
    Value z1 = Value(0, "z1");
    Value a1 = Value(2.0, "a1");
    Value b1 = Value(3.0, "b1");
    z1 = (z1 + a1);
    for (auto c : z1.prev) {
        cout << c->label << '\n';
    }
    z1 = (z1 + b1);
    for (auto c : z1.prev) {
        cout << c->label << '\n';
    }
    cout << z1 << '\n';
    cout << "-----------------\n";

    Value a2 = Value(2.0, "a2");
    Value b2 = Value(3.0, "b2");
    Value z2 = (a2 + b2);
    for (auto c : z2.prev) {
        cout << c->label << '\n';
    }
    cout << z2 << '\n';
}

void test_value_1() {
    Value x1 = Value(2.0, "x1");
    Value x2 = Value(5.0, "x2");
    Value x3 = Value(4.0, "x3");

    Value w1 = Value(4.0, "w1");
    Value w2 = Value(3.0, "w2");
    Value w3 = Value(-1.0, "w3");

    Value z = (x1 * w1 + x2 * w2 + x3 * w3).ReLU();
    z.backward();

    cout << "x1.grad: " << x1.grad << '\n';
    cout << "x2.grad: " << x2.grad << '\n';
    cout << "x3.grad: " << x3.grad << '\n';
    cout << "w1.grad: " << w1.grad << '\n';
    cout << "w2.grad: " << w2.grad << '\n';
    cout << "w3.grad: " << w3.grad << '\n';
}

void test2() {
    Value x1 = Value(2.0, "x1");
    Value x2 = Value(5.0, "x2");
    Value x3 = Value(4.0, "x3");

    Value w1 = Value(4.0, "w1");
    Value w2 = Value(3.0, "w2");
    Value w3 = Value(-1.0, "w3");

    Value z = Value(0);
    z = (z + x1 * w1);
    z = (z + x2 * w2);
    z = (z + x3 * w3);
    z.backward();
    cout << z.prev[0]->label << ' ' << z.prev[1]->label << '\n';

    cout << "x1.grad: " << x1.grad << '\n';
    cout << "x2.grad: " << x2.grad << '\n';
    cout << "x3.grad: " << x3.grad << '\n';
    cout << "w1.grad: " << w1.grad << '\n';
    cout << "w2.grad: " << w2.grad << '\n';
    cout << "w3.grad: " << w3.grad << '\n';
}

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
