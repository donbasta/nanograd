#include <bits/stdc++.h>
using namespace std;

#include "Layer.h"

Layer::Layer(int nin, int nout, bool nonlin) : nin(nin), nout(nout), nonlin(nonlin) {
    this->neurons.resize(nout);
    for (int i = 0; i < nout; i++) {
        this->neurons[i] = new Neuron(nin, nonlin);
    }
}

vector<vector<Value *>> Layer::_get_parameters() {
    vector<vector<Value *>> ret;
    for (int i = 0; i < this->nout; i++) {
        ret.push_back(this->neurons[i]->get_parameters());
    }
    return ret;
}

vector<Value *> Layer::get_parameters() {
    auto params_by_neurons = this->_get_parameters();
    vector<Value *> ret;
    for (auto params_for_a_neuron : params_by_neurons) {
        for (auto p : params_for_a_neuron) {
            ret.push_back(p);
        }
    }
    return ret;
}

vector<Value *> Layer::_forward_prop(vector<Value *> data) {
    assert((int)data.size() == this->nin);
    vector<Value *> outs;
    for (int i = 0; i < this->nout; i++) {
        outs.push_back(this->neurons[i]->_forward_prop(data));
    }
    return outs;
}

vector<vector<Value *>> Layer::forward_prop(vector<vector<Value *>> data) {
    vector<vector<Value *>> ret;
    for (auto d : data) {
        ret.push_back(this->_forward_prop(d));
    }
    return ret;
}
