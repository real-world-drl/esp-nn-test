# esp-nn Test

`esp-nn` is a library that implements the math for `tflitemicro` for ESP32.
It implements basic math functions (elementwise add/multiply) as well as the NN layers (fully connected, convolution, pooling and softmax) and ReLU activation function.

This means that it is possible to build a neural network using the above building blocks without a need for `tflitemicro`.

The downside is that it is purpose-built for `tflitemicro` so the API is a little convoluted and there's no documentation.

This project is based on the esp-nn tests - just simplified. Because my research is in Deep Reinforcement Learning, (at the moment) I only need `fully connected` and `ReLU` to implement TD3, SAC, etc.
