#include <bits/stdc++.h>

#ifndef GEN_DATA_H
#define GEN_DATA_H

vector<pair<double, double>> gen_2d_linear_data_regression(int num_data, double a, double b);
vector<pair<double, double>> gen_2d_quadratic_data_regression(int num_data, double a, double b, double c);
vector<pair<double, double>> gen_2d_linear_data_classification(int num_data, double a, double b);

#endif
