#pragma once

#include <vector>

using datatype_t = enum {
    NONE = 0,
    VECTOR,
    MATRIX,
    VSERIES,
};

using corpusinfo_t = struct {
    std::vector<size_t> dim;
    datatype_t type;
};

template <typename Datatype>
class Corpus {
    private:
        std::vector<Datatype> data;
        corpusinfo_t spec;

    public:
        Corpus(std::vector<Datatype> &initialisor);

        Datatype operator [](int &idx) {
            return data[idx];
        };

        std::vector<Datatype> operator ()() {
            return data;
        }
};

