#include <bits/stdc++.h>
using namespace std;

#ifndef NEURON_H
#define NEURON_H

#include "../Value.h"

class Neuron {
   private:
    vector<Value *> w;
    Value *b;
    bool nonlin;

   public:
    Neuron(int nin, bool nonlin);
    vector<Value *> get_parameters();
    Value *forward_prop(vector<Value *> x);
};

#endif
