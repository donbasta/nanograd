#include <bits/stdc++.h>
using namespace std;

#include "MLP.h"

MLP::MLP(int nin, vector<int> nouts, vector<bool> nonlins) {
    this->layers.resize(nouts.size());
    this->layers[0] = new Layer(nin, nouts[0], nonlins[0]);
    for (int i = 1; i < (int)nouts.size(); i++) {
        this->layers[i] = new Layer(nouts[i - 1], nouts[i], nonlins[i]);
    }
}

vector<vector<Value *>> MLP::_get_parameters() {
    vector<vector<Value *>> ret;
    for (int i = 0; i < (int)this->layers.size(); i++) {
        ret.push_back(this->layers[i]->get_parameters());
    }
    return ret;
}

vector<Value *> MLP::get_parameters() {
    vector<Value *> ret;
    auto params_by_layers = this->_get_parameters();
    for (auto params_for_a_layer : params_by_layers) {
        for (auto p : params_for_a_layer) {
            ret.push_back(p);
        }
    }
    return ret;
}

void MLP::zero_grad() {
    for (auto p : this->get_parameters()) {
        p->set_grad(0.0);
    }
}

vector<Value *> MLP::_forward_prop(vector<Value *> data) {
    vector<Value *> tot = data;
    for (int i = 0; i < (int)this->layers.size(); i++) {
        tot = this->layers[i]->_forward_prop(tot);
    }
    return tot;
}

vector<vector<Value *>> MLP::forward_prop(vector<vector<Value *>> data) {
    vector<vector<Value *>> ret;
    for (auto d : data) {
        ret.push_back(this->_forward_prop(d));
    }
    return ret;
}
