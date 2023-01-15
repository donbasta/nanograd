#include <bits/stdc++.h>
using namespace std;

#ifndef NEURON_H
#define NEURON_H

#include "../engines/Value.h"

class Neuron {
   private:
    vector<Value *> w;
    Value *b;
    bool nonlin;

   public:
    Neuron(int nin, bool nonlin);
    vector<Value *> get_parameters();
    vector<Value *> forward_prop(vector<vector<Value *>> x);
    Value *_forward_prop(vector<Value *> x);
};

#endif
