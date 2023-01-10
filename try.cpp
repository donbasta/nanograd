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
    Value x = Value(2.0, "x");
    Value y = Value(3.0, "y");
    Value w = Value(1.0, "w");

    Value z = x * y + w;
    z.label = "z";

    z.backward();

    cout << x << '\n';
    cout << y << '\n';
    cout << z << '\n';
    cout << w << '\n';
}
