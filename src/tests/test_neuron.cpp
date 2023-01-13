#include <bits/stdc++.h>
using namespace std;

void test_neuron_1() {
    Neuron n = Neuron(3, false);
    n.parameters()[0]->data = 4.0;
    n.parameters()[1]->data = 3.0;
    n.parameters()[2]->data = -1.0;
    n.parameters()[3]->data = 1.0;

    vector<Value> input_data = {Value(2.0, "x1"),
                                Value(5.0, "x2"),
                                Value(4.0, "x3")};

    Value z = n.forward_prop(input_data);
    cout << z << '\n';
    z.backward();

    for (auto p : n.parameters()) {
        cout << p->label << ' ' << p->data << ' ' << p->grad << '\n';
    }
}
