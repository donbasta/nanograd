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
    vector<vector<vector<Value *>>> get_parameters();
    vector<Value *> forward_prop(vector<Value *> data);
};

#endif
