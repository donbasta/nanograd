#include <bits/stdc++.h>
using namespace std;

struct Value {
    double data, grad;
    function<void(void)> _backward;
    string label, op;
    vector<Value *> prev;

    Value(int data, string label = "", string op = "") : data(data), grad(0.0), label(label), op(op), prev({}) {}

    double get_grad() {
        return this->grad;
    }

    void __backward() {
        if (op == "+") {
            for (auto c : this->prev) {
                c->grad += this->grad;
            }
        } else if (op == "*") {
            this->prev[0]->grad += this->prev[1]->data * this->grad;
            this->prev[1]->grad += this->prev[0]->data * this->grad;
        } else if (op == "ReLU") {
            this->prev[0]->grad += this->grad * (this->prev[0]->data > 0.0);
            // } else if (op == "^") {
            //     this->prev[0]->grad += this->grad *
        }
    }

    friend Value &operator+(Value &self, Value &other) {
        double new_data = self.data + other.data;
        string new_label = self.label + "+" + other.label;
        Value *new_value = new Value(new_data, new_label, "+");
        new_value->prev = vector{&self, &other};

        // function<void(void)> bw = [&]() -> void {
        //     cout << "tai kok ganti alamatnya: " << new_value << '\n';
        //     cout << "tolol " << new_value->get_grad() << ' ' << new_value->grad << '\n';
        //     // cout << "tes: " << ptr->label << " " << ptr->grad << '\n';
        //     self.grad += new_value->get_grad();
        //     other.grad += new_value->get_grad();
        // };
        // new_value->_backward = bw;

        return *new_value;
    }

    friend Value &operator*(Value &self, Value &other) {
        double new_data = self.data * other.data;
        string new_label = self.label + "*" + other.label;
        Value *new_value = new Value(new_data, new_label, "*");
        new_value->prev = vector{&self, &other};

        // function<void(void)> bw = [&]() -> void {
        //     cout << "tai kok ganti alamatnya: " << new_value << '\n';
        //     cout << "tolol " << new_value->get_grad() << ' ' << new_value->grad << '\n';
        //     // cout << "tes: " << ptr->label << " " << ptr->grad << '\n';
        //     self.grad += other.data * new_value->get_grad();
        //     other.grad += self.data * new_value->get_grad();
        // };
        // new_value->_backward = bw;

        return *new_value;
    }

    // Value &pow(double n) {
    //     double new_data = pow(self.data, n);
    //     string new_label = self.label + "^" + to_string(n);
    //     Value *new_value = new Value(new_data, new_label, "^");
    //     new_value->prev = vector{this};

    //     return *new_value;
    // }

    Value &ReLU() {
        double new_data = max(0.0, this->data);
        string new_label = "ReLU(" + this->label + ")";
        Value *new_value = new Value(new_data, new_label, "ReLU");
        new_value->prev = vector{this};

        return *new_value;
    }

    // Value &tanh() {
    //     double new_data = max(0.0, this->data);
    //     string new_label = "ReLU(" + this->label + ")";
    //     Value *new_value = new Value(new_data, new_label, "tanh");
    //     new_value->prev = vector{this};

    //     return *new_value;
    // }

    // Value &sigmoid() {
    //     double new_data = max(0.0, this->data);
    //     string new_label = "ReLU(" + this->label + ")";
    //     Value *new_value = new Value(new_data, new_label, "sigmoid");
    //     new_value->prev = vector{this};

    //     return *new_value;
    // }

    void backward() {
        set<Value *> visited;
        vector<Value *> topo;

        function<void(Value *)> build_topo = [&](Value *val) -> void {
            if (visited.find(val) != visited.end()) return;
            visited.insert(val);
            for (auto p : val->prev) {
                build_topo(p);
            }
            topo.push_back(val);
        };
        build_topo(this);

        this->grad = 1.0;
        reverse(topo.begin(), topo.end());
        topo[0]->grad = 1.0;
        for (auto v : topo) {
            v->__backward();
        }
    }

    friend ostream &operator<<(ostream &os, const Value &v) {
        os << v.label << ".data:" << v.data << "--" << v.label << ".grad:" << v.grad;
        return os;
    }
};

// pair<set<Value *>, vector<pair<Value *, Value *>>> trace(Value *root) {
//     set<Value *> nodes;
//     vector<pair<Value *, Value *>> edges;

//     function<void(Value *)> build = [&](Value *v) -> void {
//         if (nodes.find(v) != nodes.end()) return;
//         nodes.insert(v);
//         for (auto c : v->prev) {
//             // edges.emplace_back(c, v);
//             build(c);
//         }
//     };
//     build(root);
//     return make_pair(nodes, edges);
// }

int main() {
    // Value x = Value(2.0, "x");
    // Value y = Value(3.0, "y");
    // Value w = Value(1.0, "w");

    // Value z = x * y + w;
    // z.label = "z";

    // z.backward();

    // cout << x << '\n';
    // cout << y << '\n';
    // cout << z << '\n';
    // cout << w << '\n';

    Value x1 = Value(2.0);
    Value x2 = Value(5.0);
    Value x3 = Value(4.0);

    Value w1 = Value(4.0);
    Value w2 = Value(3.0);
    Value w3 = Value(-1.0);

    Value z = (x1 * w1 + x2 * w2 + x3 * w3).ReLU();
    z.backward();

    cout << "x1.grad: " << x1.grad << '\n';
    cout << "x2.grad: " << x2.grad << '\n';
    cout << "x3.grad: " << x3.grad << '\n';
    cout << "w1.grad: " << w1.grad << '\n';
    cout << "w2.grad: " << w2.grad << '\n';
    cout << "w3.grad: " << w3.grad << '\n';
}
