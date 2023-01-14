#include <bits/stdc++.h>
using namespace std;

#include "Value.h"

void run() {
    Value x1 = Value(2.0, "x1");
    Value w1 = Value(4.0, "w1");
    Value z = (x1 * w1);
    z.backward();

    cout << "z.grad: " << z.get_grad() << '\n';
    cout << "x1.grad: " << x1.get_grad() << '\n';
    cout << "w1.grad: " << w1.get_grad() << '\n';
}

int main() {
    cout << "HELLOOOO NIBBASSSSSSSSSSSSS!!!!!!!!!\n";
    run();
}
