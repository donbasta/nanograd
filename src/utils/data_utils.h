#include <bits/stdc++.h>

#ifndef DATA_UTILS_H
#define DATA_UTILS_H

#include "../engines/Value.h"

vector<pair<double, double>> gen_2d_linear_data_regression(int num_data, double a, double b);
vector<pair<double, double>> gen_2d_quadratic_data_regression(int num_data, double a, double b, double c);
vector<pair<double, double>> gen_2d_linear_data_classification(int num_data, double a, double b);
void get_statistic(vector<pair<double, double>> data);
pair<vector<pair<double, double>>, vector<pair<double, double>>> train_test_split(const vector<pair<double, double>>& data, double train_size);
void visualize(vector<pair<double, double>> data);
vector<vector<vector<Value*>>> prepare_data(string data_type, int num_data);

#endif
