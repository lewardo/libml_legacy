# libml
## a machine learning library for c++20
### current implementations:
+ global ml namespace
+ network abstact class
+ actfunc and lossfunc namespaces
+ vector wrapper
### TODOS:
+ linear algebra framework
+ Corpus object to import data from files
+ compatibility for training with corpus object for Network inheritors
+ autoencoder template to create an autoencoder from any Network inheritor
### future additions:
+ an RNN, LSTM, GRU
+ CNN
+ KNN
+ k-means training, SGD, BGD
+ AdaM and various optimisers

---
```shell
# compile + link
% make build
# build + run
% make run
# clean build directory
% make clean
# clean + build with specific compiler
% make rebuild CPP=/usr/local/Cellar/gcc/11.2.0_3/bin/g++-11
```
</> lewardo 2021
