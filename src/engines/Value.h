#include <bits/stdc++.h>

using namespace std;

#ifndef VALUE_H
#define VALUE_H

class Value {
   private:
    double data;
    double grad;
    string label;
    string op;
    vector<Value *> prev;

   public:
    Value();
    Value(double data);
    Value(double data, string label);
    Value(double data, string label, string op);

    double get_grad() const { return this->grad; }
    double get_data() const { return this->data; }
    string get_label() const { return this->label; }
    string get_op() const { return this->op; }
    vector<Value *> get_prev() const { return this->prev; }

    void set_data(double new_data) { this->data = new_data; }
    void set_label(string label) { this->label = label; }
    void set_grad(double g) { this->grad = g; }
    void set_prev(const vector<Value *> &ve) { this->prev = ve; }

    void _backward();
    void backward();

    Value &ReLU();
    Value &Sigmoid();
    Value &operator-();
    Value &inv();
    friend Value &operator*(Value &self, Value &other);
    friend Value &operator+(Value &self, Value &other);
    friend Value &operator-(Value &self, Value &other);
    friend Value &operator/(Value &self, Value &other);
};

Value *sum(vector<Value *> values);

#endif
