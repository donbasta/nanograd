#include <bits/stdc++.h>
using namespace std;

#include "losses.h"

// assumption: each predict_value and true_value are one-dimensional data;
Value* mean_squared_error(vector<vector<Value*>> predict_value, vector<vector<Value*>> true_value) {
    vector<Value*> operands;
    assert(predict_value.size() == true_value.size());
    int sz = predict_value.size();
    for (int i = 0; i < sz; i++) {
        Value* lol = &((*predict_value[i][0] - *true_value[i][0]) * (*predict_value[i][0] - *true_value[i][0]));
        operands.push_back(lol);
    }
    Value* loss = sum(operands);
    loss->set_data(loss->get_data() / (double)sz);
    return sum(operands);
}
