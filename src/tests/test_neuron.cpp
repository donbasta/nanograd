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