#include <bits/stdc++.h>
using namespace std;

bool is_equal(double a, double b) {
    return abs(a - b) < 1e-9;
}

double random_between_interval(double l, double r) {
    return ((double)rand() / RAND_MAX) * (r - l) + l;
}
