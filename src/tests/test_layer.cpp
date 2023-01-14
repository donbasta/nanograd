#include <bits/stdc++.h>
using namespace std;

#include "../Layer.h"
#include "../Neuron.h"
#include "../Value.h"
#include "../utils/double_utils.h"

void test_layer_1() {
    Layer l = Layer(5, 2, false);

    vector<Value*> input_data = {
        new Value(2.0, "x1"),
        new Value(5.0, "x2"),
        new Value(4.0, "x3"),
        new Value(-1.0, "x3"),
        new Value(3.0, "x3"),
    };

    vector<Value*> output_data = l.forward_prop(input_data);

    Neuron n = Neuron(3, false);
    n.get_parameters()[0]->set_data(4.0);
    n.get_parameters()[1]->set_data(3.0);
    n.get_parameters()[2]->set_data(-1.0);
    n.get_parameters()[3]->set_data(1.0);

    vector<Value*> input_data = {
        new Value(2.0, "x1"),
        new Value(5.0, "x2"),
        new Value(4.0, "x3"),
    };

    Value* z = n.forward_prop(input_data);
    z->backward();

    assert(is_equal(n.get_parameters()[0]->get_grad(), 2.0));
    assert(is_equal(n.get_parameters()[1]->get_grad(), 5.0));
    assert(is_equal(n.get_parameters()[2]->get_grad(), 4.0));
    assert(is_equal(n.get_parameters()[3]->get_grad(), 1.0));
    cout << "test_neuron_1 passed!\n";
}

void run_all_neuron_test() {
    test_neuron_1();
    // test_neuron_2();
    // test_neuron_3();
    // test_neuron_4();
    // test_neuron_5();
}
