#include <bits/stdc++.h>
using namespace std;

#include "Neuron.h"

Neuron::Neuron(int nin, bool nonlin) : nonlin(nonlin) {
    srand((unsigned)time(NULL));
    for (int i = 0; i < nin; i++) {
        double rand_weight = (double)rand() / RAND_MAX;
        this->w.push_back(new Value(rand_weight, "w" + to_string(i + 1)));
    }
    double rand_bias = (double)rand() / RAND_MAX;
    this->b = new Value(rand_bias, "b");
}

vector<Value *> Neuron::get_parameters() {
    vector<Value *> ret = this->w;
    ret.push_back(this->b);
    return ret;
}

Value *Neuron::_forward_prop(vector<Value *> data) {
    int sz = data.size();
    assert(sz == (int)this->w.size());
    Value *activation = new Value(0.0);
    vector<Value *> temps(sz + 1);
    for (int i = 0; i <= sz; i++) {
        temps[i] = new Value(0.0);
    }
    for (int i = 0; i < sz; i++) {
        *temps[i + 1] = *temps[i] + *(this->w[i]) * (*data[i]);
    }
    *activation = *temps[sz] + *(this->b);
    for (int i = 0; i <= sz; i++) {
        temps[i]->set_label("temps[" + to_string(i) + "]");
    }
    if (this->nonlin) {
        *activation = activation->ReLU();
    }
    return activation;
}

vector<Value *> Neuron::forward_prop(vector<vector<Value *>> x) {
    vector<Value *> ret;
    for (auto x_i : x) {
        ret.push_back(this->_forward_prop(x_i));
    }
    return ret;
}
