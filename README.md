# Nanograd

An implementation of autograd engine in c++ from scratch. Inspired by andrej karpathys's first lecture in neural network from zero to hero (micrograd).
DISCLAIMER: this is highly unoptimized and for educational purposes only!! (e.g. n)

Autograd, which stands for automatic gradient or automatic differentiation, is a concept used in Neural Network for the backpropagation step.
Basically, a neural network tries to locate the minimum point in a surface defined by a loss function and the net's weight.
The surfaces's global behavior is really a mystery (if not, this world wouldn't be a mystery lol), so we try to locate the minima step by step (by performing a gradient).
Calculus gives us a way to find a direction which is directed toward a local minima, by using differentiation.
Hence we move toward that direction, and how big we move is ruled by a hyperparameter called learning rate.
The value of the learning rate will affect our training duration, and there is a trade-off between large and small learning rate.
To make training faster, there are some optimizers available to customize the learning rate (like SGD, adam, etc.) which is mostly based on physics.

# Running

There are several main programs in src/bin folder, and there is a makefile rule for each main program.
For example, to run linear regression, just run `make linear-regression`

## Update 1 : Simple linear MLP for a linear regression problem works!

![lin-reg](./assets/train-linear-regression.png)
