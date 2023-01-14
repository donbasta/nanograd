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

vector<vector<vector<Value *>>> MLP::get_parameters() {
    vector<vector<vector<Value *>>> ret;
    for (int i = 0; i < (int)this->layers.size(); i++) {
        ret.push_back(this->layers[i]->get_parameters());
    }
    return ret;
}

vector<Value *> MLP::forward_prop(vector<Value *> data) {
    vector<Value *> tot = data;
    for (int i = 0; i < (int)this->layers.size(); i++) {
        tot = this->layers[i]->forward_prop(tot);
    }
    return tot;
}
