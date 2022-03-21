#include <vector>
#include <initializer_list>
#include <functional>
#include <numeric>
#include <stdexcept>
#include <execution>
#include <utility>

#include "types.h"
#include "algeb.h"

using namespace ml::types;


/*
 *  addition operations, returning new objects
 */

vector operator+(const vector& first, const flt& x) {
    vector merged(first.size()), second(first.size(), x);
    std::transform(std::execution::par, first.begin(), first.end(), second.begin(), merged.begin(), std::plus<flt>());

    return merged;
};

vector operator+(const vector& first, const vector& second) {
    if(first.size() != second.size()) throw std::length_error("operator+ vector size mismatch");
    
    vector merged(first.size());
    std::transform(std::execution::par, first.begin(), first.end(), second.begin(), merged.begin(), std::plus<flt>());

    return merged;
};


/*
 *  plus-equals operations, returns reference to self after incrementation (elementwise and scalar)
 */

vector& operator+=(vector& first, const flt& x) {
    vector merged(first.size()), second(first.size(), x);
    std::transform(std::execution::par, first.begin(), first.end(), second.begin(), merged.begin(), std::plus<flt>());
    
    first = std::move(merged);

    return first;
};

vector& operator+=(vector& first, const vector& second) {
    if(first.size() != second.size()) throw std::length_error("operator+= vector size mismatch");

    vector merged(first.size());
    std::transform(std::execution::par, first.begin(), first.end(), second.begin(), merged.begin(), std::plus<flt>());
    
    first = std::move(merged);

    return first;
};


/*
 *  subtraction operations, returning new objects
 */

vector operator-(const vector& first, const flt& x) {
    vector merged(first.size()), second(first.size(), x);
    std::transform(std::execution::par, first.begin(), first.end(), second.begin(), merged.begin(), std::minus<flt>());

    return merged;
};

vector operator-(const vector& first, const vector& second) {
    if(first.size() != second.size()) throw std::length_error("operator- vector size mismatch");
    
    vector merged(first.size());
    std::transform(std::execution::par, first.begin(), first.end(), second.begin(), merged.begin(), std::minus<flt>());

    return merged;
};


/*
 *  minus-equals operations, returns reference to self after decrementation (elementwise and scalar)
 */

vector& operator-=(vector& first, const flt& x) {
    vector merged(first.size()), second(first.size(), x);
    std::transform(std::execution::par, first.begin(), first.end(), second.begin(), merged.begin(), std::minus<flt>());
    
    first = std::move(merged);

    return first;
};

vector& operator-=(vector& first, const vector& second) {
    if(first.size() != second.size()) throw std::length_error("operator-= vector size mismatch");

    vector merged(first.size());
    std::transform(std::execution::par, first.begin(), first.end(),second.begin(), merged.begin(), std::minus<flt>());
    
    first = std::move(merged);
    
    return first;
};


/*
 *  multiplication operations: scalar product, dot product and hadamarand (elementwise) product respectively
 */

flt operator*(const vector& first, const vector& second) {
    if(first.size() != second.size()) throw std::length_error("operator* vector size mismatch");
    
    return std::transform_reduce(std::execution::par, first.begin(), first.end(), second.begin(), 0.0f);
};


vector operator*(const vector& first, const flt& x) {
    vector merged(first.size()), second(first.size(), x);
    std::transform(std::execution::par, first.begin(), first.end(), second.begin(), merged.begin(), std::multiplies<flt>());

    return merged;
};

vector operator&(const vector& first, const vector& second) {
    if(first.size() != second.size()) throw std::length_error("operator& vector size mismatch");

    vector merged(first.size());
    std::transform(std::execution::par, first.begin(), first.end(), second.begin(), merged.begin(), std::multiplies<flt>());

    return merged;
};

vector operator&(const vector& first, const flt& x) {
    return first * x;
}


/*
 *  times-equals operations: scalar product and hadamarand (elementwise) product respectively
 */

 vector& operator*=(vector& first, const flt& x) {
     vector merged(first.size()), second(first.size(), x);
     std::transform(std::execution::par, first.begin(), first.end(), second.begin(), merged.begin(), std::multiplies<flt>());
     
     first = std::move(merged);

     return first;
 };

 vector& operator&=(vector& first, const vector& second) {
     if(first.size() != second.size()) throw std::length_error("operator&= vector size mismatch");

     vector merged(first.size());
     std::transform(std::execution::par, first.begin(), first.end(), second.begin(), merged.begin(), std::multiplies<flt>());
     
     first = std::move(merged);

     return first;
 };