int main() {
    Neuron n = Neuron(3, false);
    for (auto p : n.parameters()) {
        cout << p->data << ' ';
    }
    cout << '\n';

    vector<Value> input_data = {Value(3.0),
                                // Value(0.0),
                                // Value(-1.0),
                                Value(0.5),
                                Value(1.0)};

    Value act = n.forward_prop(input_data);
    act.label = "act";
    cout << act << '\n';
    cout << act.prev.size() << '\n';
    cout << act.prev[0]->data << '\n';
    cout << act.prev[1]->data << '\n';
    cout << "-------------------\n";
    act.backward();
    cout << "-------------------\n";
    for (auto p : n.parameters()) {
        cout << p->grad << '\n';
    }
}

void test1() {
    Value x1 = Value(2.0, "x1");
    Value x2 = Value(5.0, "x2");
    Value x3 = Value(4.0, "x3");

    Value w1 = Value(4.0, "w1");
    Value w2 = Value(3.0, "w2");
    Value w3 = Value(-1.0, "w3");
    Value b = Value(1.0, "b");

    Value z = (x1 * w1 + x2 * w2 + x3 * w3 + b);
    cout << z << '\n';
    z.backward();

    cout << "w1.grad: " << w1.grad << '\n';
    cout << "w2.grad: " << w2.grad << '\n';
    cout << "w3.grad: " << w3.grad << '\n';
    cout << "b.grad: " << b.grad << '\n';
}

void test2() {
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