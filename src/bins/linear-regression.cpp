#include <bits/stdc++.h>
using namespace std;

#include "../engines/Value.h"
#include "../layers/MLP.h"
#include "../losses/losses.h"
#include "../utils/data_utils.h"

int main() {
    // prepare the dataset (randomly generated, 1d for now)
    int num_data = 100000;
    auto data = prepare_data("linear_1d", num_data);
    auto x_train = data[0];
    auto y_train = data[1];
    auto x_test = data[2];
    auto y_test = data[3];

    // architecture: 2 layers, where the hidden layer consists of 3 neurons :D
    // MLP model_linear = MLP(1, vector<int>{3, 1}, vector<bool>{false, false});
    MLP model_linear = MLP(1, vector<int>{1}, vector<bool>{false});
    int epoch = 1;
    double learning_rate = 0.0001;

    // batch the dataset, might move this to data_utils later
    vector<pair<vector<vector<Value*>>, vector<vector<Value*>>>> batches;
    int batch_size = 40;
    int cnt_for_batch = 0;
    vector<vector<Value*>> x_temp;
    vector<vector<Value*>> y_temp;
    for (int i = 0; i < (int)x_train.size(); i++) {
        x_temp.push_back(x_train[i]);
        y_temp.push_back(y_train[i]);
        cnt_for_batch++;
        if (cnt_for_batch == batch_size) {
            cnt_for_batch = 0;
            batches.emplace_back(x_temp, y_temp);
            x_temp.clear();
            y_temp.clear();
        }
    }

    // run the training loop
    for (int ep = 1; ep <= epoch; ep++) {
        int bat = 1;

        for (auto batch : batches) {
            // after each batch, reset the grad to zero
            model_linear.zero_grad();

            auto x = batch.first;
            auto y = batch.second;
            auto predict = model_linear.forward_prop(x);
            Value* loss = mean_squared_error(predict, y);

            if (bat % 30 == 0) {
                cout << setprecision(10) << "loss at epoch " << ep << " and batch " << bat << " is " << loss->get_data() << '\n';
            }

            loss->backward();

            for (Value* p : model_linear.get_parameters()) {
                // learning step; might use some optimizers here...
                double updated_weight = p->get_data() - learning_rate * p->get_grad();
                p->set_data(updated_weight);
            }

            bat++;
        }
    }
}
