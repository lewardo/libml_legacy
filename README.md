# libml
## a more fully fledged machine learning library for the c programming language
### current implementations:
+ file structure
+ Network abstact class
+ mlpNet object, without functions implemented yet
### TODOS:
+ Corpus object to import data from files
+ compatibility for training with corpus object for Network inheritors
+ autoencoder template to create an autoencoder from any Network inheritor
+ the NetChain object that chains inputs to outputs to create single comples network objects
### future additions:
+ an RNN, LSTM, GRU 
+ CNN 
+ KNN 
+ k-means training, SGD, BGD 
+ AdaM and various optimisers

---
```bash
.
├── src
│   └── ...     # source files for library
├── libml.h     # header file for library
├── LICENSE     # GPL 3
├── main.cpp    # example file, currently only initialises mlpNet object
└── README.md   # this file :)
```
---
```bash
# compilation
% mkdir build
% g++ -o build/main -std=c++17 -stdlib=libc++ -I . *.cpp src/*.cpp
# run it!
% build/main
```
</> with ❤️ by lewardo 2021