#include <bits/stdc++.h>
using namespace std;

#include "Value.h"

void test1() {
    Value x1 = Value(2.0, "x1");
    Value w1 = Value(4.0, "w1");
    Value z = (x1 * w1);
    z.backward();

    cout << "z.grad: " << z.get_grad() << '\n';
    cout << "x1.grad: " << x1.get_grad() << '\n';
    cout << "w1.grad: " << w1.get_grad() << '\n';
}

void test2() {
    // Neuron n = Neuron(3, false);
    // n.parameters()[0]->data = 4.0;
    // n.parameters()[1]->data = 3.0;
    // n.parameters()[2]->data = -1.0;
    // n.parameters()[3]->data = 1.0;

    // vector<Value *> input_data = {
    //     new Value(2.0, "x1"),
    //     new Value(5.0, "x2"),
    //     new Value(4.0, "x3")};

    // Value z = n.forward_prop(input_data);
    // z.backward();
    // cout << "--------------------------------------------------\n";

    // for (auto p : n.parameters()) {
    //     cout << p->get_label() << ' ' << p->get_data() << ' ' << p->get_grad() << '\n';
    // }
}

int main() {
    cout << "HELLOOOO NIBBASSSSSSSSSSSSS!!!!!!!!!\n";
    test1();
}