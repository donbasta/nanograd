#include <bits/stdc++.h>

using namespace std;

#ifndef VALUE_H
#define VALUE_H
#endif

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

    void set_label(string label) { this->label = label; }
    void set_grad(double g) { this->grad = g; }
    void set_prev(const vector<Value *> &ve) { this->prev = ve; }

    void _backward() {
        if (op == "+") {
            for (auto c : this->prev) {
                c->grad += this->grad;
            }
        } else if (op == "*") {
            this->prev[0]->grad += this->prev[1]->data * this->grad;
            this->prev[1]->grad += this->prev[0]->data * this->grad;
        } else if (op == "ReLU") {
            this->prev[0]->grad += this->grad * (this->prev[0]->data > 0.0);
        }
    }

    Value &ReLU() {
        double new_data = max(0.0, this->data);
        string new_label = "ReLU(" + this->label + ")";
        Value *new_value = new Value(new_data, new_label, "ReLU");
        new_value->prev = vector{this};

        return *new_value;
    }

    friend Value &operator*(Value &self, Value &other);
    friend Value &operator+(Value &self, Value &other);

    void backward();
};
