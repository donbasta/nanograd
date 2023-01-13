#include <bits/stdc++.h>
using namespace std;

struct Value {
    double data, grad;
    // function<void(void)> _backward;
    string label, op;
    vector<Value *> prev;

    Value() : data(0.0) {}
    Value(double data, string label = "", string op = "") : data(data), grad(0.0), label(label), op(op), prev({}) {}
    // Value(const Value &other) {
    //     this->data = other.data;
    //     this->grad = other.grad;
    //     this->label = other.label;
    //     this->op = other.op;
    //     this->prev = other.prev;
    // }

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
        // Value *self_cpy = new Value(self);
        // Value *other_cpy = new Value(other);
        // new_value->prev.push_back(self_cpy);
        // new_value->prev.push_back(other_cpy);
        // self = *self_cpy;
        // other = *other_cpy;
        // new_value->prev.push_back(new Value(self));
        // new_value->prev.push_back(new Value(other));
        // new_value->prev.push_back(&self);
        // new_value->prev.push_back(&other);
        // cout << "[" << self.label << " ,,,, " << other.label << "]\n";

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
        // new_value->prev.push_back(&self);
        // new_value->prev.push_back(&other);

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
        for (auto v : topo) {
            cout << "TESTT " << v->label << ' ' << v->data << ' ' << v->grad << ' ' << v << '\n';
            // v->__backward();
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

// class Module {
//     void zero_grad() {
//         for (auto p : this->parameters()) {
//             p.grad = 0.0;
//         }
//     }

//     vector<Value> parameters() {
//         return vector<Value>{};
//     }
// };

class Neuron {
   private:
    vector<Value *> w;
    Value *b;
    bool nonlin;

   public:
    Neuron(int nin, bool nonlin = true) : nonlin(nonlin) {
        srand((unsigned)time(NULL));
        for (int i = 0; i < nin; i++) {
            double rand_weight = (double)rand() / RAND_MAX;
            this->w.push_back(new Value(rand_weight, "w" + to_string(i + 1)));
        }
        double rand_bias = (double)rand() / RAND_MAX;
        this->b = new Value(rand_bias, "b");
    }

    vector<Value *> parameters() {
        vector<Value *> ret = this->w;
        ret.push_back(this->b);
        return ret;
    }
    Value &forward_prop(vector<Value *> x) {
        assert(x.size() == this->w.size());
        Value *activation = new Value(0.0);
        vector<Value *> temps(x.size() + 1);
        for (int i = 0; i <= x.size(); i++) {
            temps[i] = new Value(0.0);
        }
        for (int i = 0; i < x.size(); i++) {
            *temps[i + 1] = *temps[i] + *(this->w[i]) * (*x[i]);
        }
        *activation = *temps[x.size()] + *(this->b);
        for (int i = 0; i <= x.size(); i++) {
            temps[i]->label = "temps[" + to_string(i) + "]";
        }
        if (this->nonlin) {
            *activation = activation->ReLU();
        }
        return *activation;
    }
};

void test1() {
    Value x1 = Value(2.0, "x1");
    // Value x2 = Value(5.0, "x2");
    // Value x3 = Value(4.0, "x3");

    Value w1 = Value(4.0, "w1");
    // Value w2 = Value(3.0, "w2");
    // Value w3 = Value(-1.0, "w3");
    // Value b = Value(1.0, "b");

    Value z = (x1 * w1);
    cout << z << '\n';
    z.backward();

    cout << "z.grad: " << z.grad << '\n';
    cout << "x1.grad: " << x1.grad << '\n';
    cout << "w1.grad: " << w1.grad << '\n';
    // cout << "w2.grad: " << w2.grad << '\n';
    // cout << "w3.grad: " << w3.grad << '\n';
    // cout << "b.grad: " << b.grad << '\n';
}

void test2() {
    Neuron n = Neuron(3, false);
    n.parameters()[0]->data = 4.0;
    n.parameters()[1]->data = 3.0;
    n.parameters()[2]->data = -1.0;
    n.parameters()[3]->data = 1.0;

    vector<Value *> input_data = {
        new Value(2.0, "x1"),
        new Value(5.0, "x2"),
        new Value(4.0, "x3")};

    Value z = n.forward_prop(input_data);
    cout << z << '\n';
    for (auto c : z.prev) {
        cout << c->label << ' ';
    }
    cout << '\n';
    z.backward();
    cout << "--------------------------------------------------\n";

    for (auto p : n.parameters()) {
        cout << p->label << ' ' << p->data << ' ' << p->grad << '\n';
    }
}

int main() {
    // test1();
    // cout << "----------------\n";
    test2();
}
