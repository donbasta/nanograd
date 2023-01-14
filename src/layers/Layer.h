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
    vector<vector<Value *>> get_parameters();
    vector<Value *> forward_prop(vector<Value *> data);
};

#endif
