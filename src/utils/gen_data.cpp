#include <bits/stdc++.h>
using namespace std;

#include "double_utils.h"

// we will only generate data with x values between L and R as described below;
const double L = 0;
const double R = 100;
const double NOISE_AMPLITUDE = 2;

// generate noisy data which is modeled by plane y = ax + b
vector<pair<double, double>> gen_2d_linear_data_regression(int num_data, double a, double b) {
    vector<pair<double, double>> data;
    for (int i = 0; i < num_data; i++) {
        double x = random_between_interval(L, R);
        double y = a * x + b;
        double noise = random_between_interval(-1.0, 1.0) * NOISE_AMPLITUDE;
        y += noise;
        data.emplace_back(x, y);
    }
    return data;
}

// generate noisy data which is modeled by plane y = ax^2 + bx + c
vector<pair<double, double>> gen_2d_quadratic_data_regression(int num_data, double a, double b, double c) {
    vector<pair<double, double>> data;
    for (int i = 0; i < num_data; i++) {
        double x = random_between_interval(L, R);
        double y = a * x * x + b * x + c;
        double noise = random_between_interval(-1.0, 1.0) * NOISE_AMPLITUDE;
        y += noise;
        data.emplace_back(x, y);
    }
    return data;
}

// generate noisy data which is separated by the plane y = ax + b
vector<pair<double, double>> gen_2d_linear_data_classification(int num_data, double a, double b) {
    return vector<pair<double, double>>{};
}

void get_statistic(vector<pair<double, double>> data) {}

// int main() {
//     vector<pair<double, double>> haha = gen_2d_linear_data_regression(10, 2.0, 1.0);
//     for (auto c : haha) {
//         cout << c.first << ' ' << c.second << '\n';
//     }
// }
