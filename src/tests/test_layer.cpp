#include <bits/stdc++.h>
using namespace std;

#include "../engines/Value.h"
#include "../layers/Layer.h"
#include "../utils/number_utils.h"

void test_layer_1() {
    Layer l = Layer(3, 2, false);

    vector<vector<Value*>> input_data = {
        vector<Value*>{
            new Value(2.0, "x1"),
            new Value(-1.0, "x2"),
            new Value(3.0, "x3"),
        },
    };

    vector<vector<Value*>> output_data = l.forward_prop(input_data);
    assert(output_data.size() == input_data.size());
    assert(output_data.size() == 1);
    Value* sum_output = sum(output_data[0]);
    sum_output->backward();

    assert(output_data[0].size() == 2);
    assert(l.get_parameters()[0]->get_grad() == 2.0);
    assert(l.get_parameters()[1]->get_grad() == -1.0);
    assert(l.get_parameters()[2]->get_grad() == 3.0);
    assert(l.get_parameters()[3]->get_grad() == 1.0);

    cout << "test_layer_1 passed!\n";
}

void run_all_layer_test() {
    test_layer_1();
    // test_neuron_2();
    // test_neuron_3();
    // test_neuron_4();
    // test_neuron_5();
}
