#include <bits/stdc++.h>
using namespace std;

#ifndef LAYER_H
#define LAYER_H
#endif

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
};