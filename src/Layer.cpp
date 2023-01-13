#include <bits/stdc++.h>
using namespace std;

#include "Layer.h"

Layer::Layer(int nin, int nout, bool nonlin) : nin(nin), nout(nout), nonlin(nonlin) {
    this->neurons.resize(nout);
    for (int i = 0; i < nout; i++) {
        this->neurons[i] = new Neuron(nin, nonlin);
    }
}

vector<vector<Value *>> Layer::get_parameters() {
    vector<vector<Value *>> ret;
    for (int i = 0; i < this->nout; i++) {
        ret.push_back(this->neurons[i]->get_parameters());
    }
    return ret;
}