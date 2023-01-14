#include <bits/stdc++.h>
using namespace std;

#include "../Value.h"
#include "../utils/double_utils.h"

void test_value_1() {
    Value z1 = Value(0, "z1");
    Value a1 = Value(2.0, "a1");
    Value b1 = Value(3.0, "b1");
    z1 = (z1 + a1);
    z1 = (z1 + b1);

    assert(is_equal(z1.get_data(), 5.0));
    cout << "test_value_1 passed!\n";
}

void test_value_2() {
    Value a2 = Value(2.0, "a2");
    Value b2 = Value(3.0, "b2");
    Value z2 = (a2 + b2);
    z2.backward();

    assert(is_equal(z2.get_data(), 5.0));
    assert(is_equal(a2.get_grad(), 1.0));
    assert(is_equal(b2.get_grad(), 1.0));
    cout << "test_value_2 passed!\n";
}

void test_value_3() {
    Value a2 = Value(2.0, "a2");
    Value b2 = Value(3.0, "b2");
    Value z2 = (a2 * b2);
    z2.backward();

    assert(is_equal(z2.get_data(), 6.0));
    assert(is_equal(a2.get_grad(), 3.0));
    assert(is_equal(b2.get_grad(), 2.0));
    cout << "test_value_3 passed!\n";
}

void test_value_4() {
    Value x1 = Value(2.0, "x1");
    Value x2 = Value(5.0, "x2");
    Value x3 = Value(4.0, "x3");

    Value w1 = Value(4.0, "w1");
    Value w2 = Value(3.0, "w2");
    Value w3 = Value(-1.0, "w3");

    Value z = (x1 * w1 + x2 * w2 + x3 * w3).ReLU();
    z.backward();

    assert(is_equal(z.get_data(), 19.0));
    assert(is_equal(w1.get_grad(), 2.0));
    assert(is_equal(w2.get_grad(), 5.0));
    assert(is_equal(w3.get_grad(), 4.0));
    cout << "test_value_4 passed!\n";
}

void test_value_5() {
    Value a2 = Value(2.0, "a2");
    Value b2 = Value(3.0, "b2");
    Value z2 = (a2 - b2);
    z2.backward();

    assert(is_equal(z2.get_data(), -1.0));
    assert(is_equal(a2.get_grad(), 1.0));
    assert(is_equal(b2.get_grad(), -1.0));
    cout << "test_value_5 passed!\n";
}

void test_value_6() {
    Value a2 = Value(2.0, "a2");
    Value b2 = Value(3.0, "b2");
    Value z2 = (a2 / b2);
    z2.backward();

    assert(is_equal(z2.get_data(), 0.66666666666));
    assert(is_equal(a2.get_grad(), 0.33333333333));
    assert(is_equal(b2.get_grad(), -0.22222222222));
    cout << "test_value_6 passed!\n";
}

void test_value_sum() {
    vector<Value*> input_data = {
        new Value(2.0, "x1"),
        new Value(5.0, "x2"),
        new Value(4.0, "x3"),
        new Value(-1.0, "x3"),
        new Value(3.0, "x3"),
    };

    Value* sum_all = sum(input_data);
    sum_all->backward();
    for (auto v : input_data) {
        assert(is_equal(v->get_grad(), 1.0));
    }
    assert(is_equal(sum_all->get_data(), 13.0));
    cout << "test_value_sum passed!\n";
}

void test_relu() {
    Value a = Value(2.0, "a");
    Value b = Value(-2.0, "b");
    Value ar = a.ReLU();
    Value br = b.ReLU();

    assert(is_equal(2.0, ar.get_data()));
    assert(is_equal(0.0, br.get_data()));
    ar.backward();
    br.backward();
    assert(is_equal(1.0, a.get_grad()));
    assert(is_equal(0.0, b.get_grad()));
    cout << "test_relu passed!\n";
}

void test_sigmoid() {
    Value a = Value(0.0, "a");
    Value b = Value(-2.0, "b");
    Value ar = a.Sigmoid();
    Value br = b.Sigmoid();

    assert(is_equal(0.5, ar.get_data()));
    assert(is_equal(0.1192029220221175559403, br.get_data()));
    ar.backward();
    br.backward();
    assert(is_equal(0.25, a.get_grad()));
    assert(is_equal(0.1049935854, b.get_grad()));
    cout << "test_sigmoid passed!\n";
}

void run_all_value_test() {
    test_value_1();
    test_value_2();
    test_value_3();
    test_value_4();
    test_value_5();
    test_value_6();
    test_value_sum();
    test_relu();
    test_sigmoid();
}
