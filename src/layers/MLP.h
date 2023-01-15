#include <bits/stdc++.h>
using namespace std;

#ifndef MLP_H
#define MLP_H

#include "Layer.h"

class MLP {
   private:
    vector<Layer *> layers;

   public:
    MLP(int nin, vector<int> nouts, vector<bool> nonlins);
    vector<vector<Value *>> _get_parameters();
    vector<Value *> get_parameters();
    vector<Value *> _forward_prop(vector<Value *> data);
    vector<vector<Value *>> forward_prop(vector<vector<Value *>> data);
    void zero_grad();
};

#endif
