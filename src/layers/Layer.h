#include <bits/stdc++.h>
using namespace std;

#ifndef LAYER_H
#define LAYER_H

#include "Neuron.h"

class Layer {
   private:
    vector<Neuron *> neurons;
    int nin;
    int nout;
    bool nonlin;

   public:
    Layer(int nin, int nout, bool nonlin);
    vector<vector<Value *>> _get_parameters();
    vector<Value *> get_parameters();
    vector<Value *> _forward_prop(vector<Value *> data);
    vector<vector<Value *>> forward_prop(vector<vector<Value *>> data);
};

#endif
