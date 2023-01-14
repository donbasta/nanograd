# Nanograd

An implementation of autograd engine in c++. Inspired by andrej karpathys's first lecture in neural network from zero to hero (micrograd).

Autograd, which stands for automatic gradient or automatic differentiation, is a concept used in Neural Network for the backpropagation step.
Basically, a neural network tries to locate the minimum point in a surface defined by a loss function and the net's weight.
The surfaces's global behavior is really a mystery (if not, this world wouldn't be a mystery lol), so we try to locate the minima step by step (by performing a gradient).
Calculus gives us a way to find a direction which is directed toward a local minima, by using differentiation.
Hence we move toward that direction, and how big we move is ruled by a hyperparameter called learning rate.
The value of the learning rate will affect our training duration, and there is a trade-off between large and small learning rate.
To make training faster, there are some optimizers available to customize the learning rate (like SGD, adam, etc.) which is mostly based on physics.

## Todolist

- [ ] benerin makefilenya biar ga cluttered
- [ ] test MultiLayerPerceptron
- [ ] implement optimizers and loss functions
- [ ] create training pipeline with a generated data
- [ ] visualize training process and accuracy
- [ ] create abstract class Layer
- [ ] create abstarct class Model
- [ ] allow model to read weights from external file
- [ ] give proper documentation to the code
- [ ] structure the code yg baik dan benar lol (unit test, etc)
- [ ] kaidah cpp programming yg baik dan benar (not using bits/stdc++.h, not using namespace std lgsg)
- [ ] change double_utils to number_utils, and gen_data to data_utils

## Cool to have

- [ ] implement convolutional layer and simple convnet based model
- [ ] train mnist digit
- [ ] implement recurrent layer and RNN, LSTM, GRU
- [ ] train tweet sentiment
- [ ] implement attention layer and transformer, and GPT maybe
- [ ] simple text generator using transformer
