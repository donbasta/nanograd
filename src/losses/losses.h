#include <bits/stdc++.h>
using namespace std;

#ifndef LOSSES_H
#define LOSSES_H

#include "../engines/Value.h"

Value* mean_squared_error(vector<vector<Value*>> predict_value, vector<vector<Value*>> true_value);

#endif
