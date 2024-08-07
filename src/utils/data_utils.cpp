#include <bits/stdc++.h>
using namespace std;

#include "data_utils.h"
#include "matplotlibcpp.h"
#include "number_utils.h"

namespace plt = matplotlibcpp;

// we will only generate data with x values between L and R as described below;
const double L = -1;
const double R = 1;
const double NOISE_AMPLITUDE = 0.1;

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

vector<pair<double, double>> gen_2d_spiral_data_classification(int num_data_per_class, int num_class) {
    // source: https://cs231n.github.io/neural-networks-case-study/

    // N = 100 # number of points per class
    // D = 2 # dimensionality
    // K = 3 # number of classes
    // X = np.zeros((N*K,D)) # data matrix (each row = single example)
    // y = np.zeros(N*K, dtype='uint8') # class labels
    // for j in range(K):
    //   ix = range(N*j,N*(j+1))
    //   r = np.linspace(0.0,1,N) # radius
    //   t = np.linspace(j*4,(j+1)*4,N) + np.random.randn(N)*0.2 # theta
    //   X[ix] = np.c_[r*np.sin(t), r*np.cos(t)]
    //   y[ix] = j
    // # lets visualize the data:
    // plt.scatter(X[:, 0], X[:, 1], c=y, s=40, cmap=plt.cm.Spectral)
    // plt.show()

    return vector<pair<double, double>>{};
}

void get_statistic(vector<pair<double, double>> data) {}

pair<vector<pair<double, double>>, vector<pair<double, double>>> train_test_split(vector<pair<double, double>>& data, double train_size) {
    vector<pair<double, double>> train;
    vector<pair<double, double>> test;
    random_shuffle(data.begin(), data.end());
    int sep = int(train_size * data.size());
    for (int i = 0; i < sep; i++) {
        train.push_back(data[i]);
    }
    for (int i = sep; i < (int)data.size(); i++) {
        test.push_back(data[i]);
    }
    return make_pair(train, test);
}

vector<vector<vector<Value*>>> prepare_data(string data_type, int num_data) {
    vector<pair<double, double>> data_double;
    if (data_type == "linear_1d") {
        data_double = gen_2d_linear_data_regression(num_data, 2.0, 3.0);  // y = 2x + 3
        // visualize(data_double);
    } else if (data_type == "quadratic_1d") {
        data_double = gen_2d_quadratic_data_regression(num_data, 1.0, 3.0, -1.0);  // y = x^2 + 3x - 1
    }

    pair<vector<pair<double, double>>, vector<pair<double, double>>> data_splitted_double = train_test_split(data_double, 0.8);
    vector<pair<double, double>> train_data_double = data_splitted_double.first;
    vector<pair<double, double>> validation_data_double = data_splitted_double.second;

    vector<vector<Value*>> x_train, y_train, x_test, y_test;
    for (auto d : train_data_double) {
        x_train.push_back(vector<Value*>{new Value(d.first)});
        y_train.push_back(vector<Value*>{new Value(d.second)});
    }
    for (auto d : validation_data_double) {
        x_test.push_back(vector<Value*>{new Value(d.first)});
        y_test.push_back(vector<Value*>{new Value(d.second)});
    }

    return vector<vector<vector<Value*>>>{x_train, y_train, x_test, y_test};
}

// visualize reports (like training performance, data, etc)
void visualize(vector<pair<double, double>> data) {
    int sz = data.size();
    for (int i = 0; i < sz; i++) {
        // plt::plot({data[i].first}, {data[i].second}, "bo");
    }
    save_graphics("lol");
}

void save_graphics(string filename) {
    // plt::title("visualize data 2d");
    // plt::save("./viz/" + filename + ".png");
}

// int main() {
//     vector<pair<double, double>> haha = gen_2d_linear_data_regression(10, 2.0, 1.0);
//     for (auto c : haha) {
//         cout << c.first << ' ' << c.second << '\n';
//     }
// }
