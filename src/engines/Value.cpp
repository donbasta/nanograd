#include <bits/stdc++.h>
using namespace std;

#include "../utils/double_utils.h"
#include "Value.h"

Value::Value() : data(0.0), grad(0.0) {}
Value::Value(double data) : data(data), grad(0.0), label(""), op("") {}
Value::Value(double data, string label) : data(data), grad(0.0), label(label), op("") {}
Value::Value(double data, string label, string op) : data(data), grad(0.0), label(label), op(op), prev({}) {}

Value &operator+(Value &self, Value &other) {
    double new_data = self.get_data() + other.get_data();
    string new_label = self.get_label() + "+" + other.get_label();
    Value *new_value = new Value(new_data, new_label, "+");
    new_value->set_prev(vector{&self, &other});

    return *new_value;
}

Value &operator*(Value &self, Value &other) {
    double new_data = self.get_data() * other.get_data();
    string new_label = "(" + self.get_label() + "*" + other.get_label() + ")";
    Value *new_value = new Value(new_data, new_label, "*");
    new_value->set_prev(vector{&self, &other});

    return *new_value;
}

Value &operator-(Value &self, Value &other) {
    return self + (-other);
}

Value &operator/(Value &self, Value &other) {
    return self * other.inv();
}

void Value::_backward() {
    if (op == "+") {
        this->prev[0]->grad += this->grad;
        this->prev[1]->grad += this->grad;
    } else if (op == "*") {
        this->prev[0]->grad += this->prev[1]->data * this->grad;
        this->prev[1]->grad += this->prev[0]->data * this->grad;
    } else if (op == "ReLU") {
        this->prev[0]->grad += this->grad * (this->prev[0]->data > 0.0);
    } else if (op == "Sigmoid") {
        this->prev[0]->grad += this->grad * this->data * (1.0 - this->data);
    } else if (op == "neg") {
        this->prev[0]->grad += (-this->grad);
    } else if (op == "inv") {
        this->prev[0]->grad += -(this->grad * this->data * this->data);
    }
}

Value &Value::ReLU() {
    double new_data = max(0.0, this->data);
    string new_label = "ReLU(" + this->label + ")";
    Value *new_value = new Value(new_data, new_label, "ReLU");
    new_value->prev = vector{this};

    return *new_value;
}

Value &Value::Sigmoid() {
    double new_data = (double)1.0 / (1 + exp(-this->data));
    string new_label = "Sigmoid(" + this->label + ")";
    Value *new_value = new Value(new_data, new_label, "Sigmoid");
    new_value->prev = vector{this};

    return *new_value;
}

Value &Value::operator-() {
    double new_data = -this->data;
    string new_label = "neg(" + this->label + ")";
    Value *new_value = new Value(new_data, new_label, "neg");
    new_value->prev = vector{this};

    return *new_value;
}

Value &Value::inv() {
    assert(!is_equal(this->get_data(), 0.0));  // Division by zero error

    double new_data = (double)1.0 / this->data;
    string new_label = "inv(" + this->label + ")";
    Value *new_value = new Value(new_data, new_label, "inv");
    new_value->prev = vector{this};

    return *new_value;
}

void Value::backward() {
    set<Value *> visited;
    vector<Value *> topo;

    function<void(Value *)> build_topo = [&](Value *val) -> void {
        if (visited.find(val) != visited.end()) return;
        visited.insert(val);
        for (auto p : val->get_prev()) {
            build_topo(p);
        }
        topo.push_back(val);
    };
    build_topo(this);

    this->set_grad(1.0);
    reverse(topo.begin(), topo.end());
    for (auto v : topo) {
        v->_backward();
    }
}

ostream &operator<<(ostream &os, const Value &v) {
    os << v.get_label() << ".data:" << v.get_data() << "--" << v.get_label() << ".grad:" << v.get_grad();
    return os;
}

Value *sum(vector<Value *> values) {
    int sz = values.size();
    vector<Value *> temps(sz + 1);
    for (int i = 0; i <= sz; i++) {
        temps[i] = new Value(0.0);
    }
    for (int i = 0; i < sz; i++) {
        *temps[i + 1] = *temps[i] + *values[i];
    }
    return temps[sz];
}
