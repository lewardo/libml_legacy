#include <vector>
#include <initializer_list>
#include <functional>
#include <numeric>
#include <stdexcept>
#include <execution>
#include <utility>

#include "types.h"
#include "algeb.h"

/*
 *  vector operation definitions
 *  
 */

namespace ml::internal::types {
     
    /*
     *  addition operations, returning new objects
     */

    vector operator+(const vector& lterm, const flt& rterm) {
        vector res(lterm.size()), vec(lterm.size(), rterm);
        std::transform(std::execution::par_unseq, 
            lterm.begin(), lterm.end(), 
            vec.begin(), 
            res.begin(), 
            std::plus<flt>()
        );

        return res;
    };

    vector operator+(const vector& lterm, const vector& rterm) {
        if(lterm.size() != rterm.size()) throw std::length_error("operator+ vector size mismatch");

        vector res(lterm.size());
        std::transform(std::execution::par_unseq, 
            lterm.begin(), lterm.end(), 
            rterm.begin(), 
            res.begin(), 
            std::plus<flt>()
        );

        return res;
    };


    /*
     *  plus-equals operations, returns reference to self after incrementation (elementwise and scalar)
     */

    vector& operator+=(vector& lterm, const flt& rterm) {
        vector res(lterm.size()), vec(lterm.size(), rterm);
        std::transform(
            std::execution::par_unseq, 
            lterm.begin(), lterm.end(), 
            vec.begin(), 
            res.begin(), 
            std::plus<flt>()
        );

        lterm = std::move(res);

        return lterm;
    };

    vector& operator+=(vector& lterm, const vector& rterm) {
        if(lterm.size() != rterm.size()) throw std::length_error("operator+= vector size mismatch");

        vector res(lterm.size());
        std::transform(
            std::execution::par_unseq, 
            lterm.begin(), lterm.end(), 
            rterm.begin(), 
            res.begin(), 
            std::plus<flt>()
        );

        lterm = std::move(res);

        return lterm;
    };


    /*
     *  subtraction operations, returning new objects
     */

    vector operator-(const vector& lterm, const flt& rterm) {
        vector res(lterm.size()), vec(lterm.size(), rterm);
        std::transform(
            std::execution::par_unseq, 
            lterm.begin(), lterm.end(), 
            vec.begin(), 
            res.begin(), 
            std::minus<flt>()
        );

        return res;
    };

    vector operator-(const vector& lterm, const vector& rterm) {
        if(lterm.size() != rterm.size()) throw std::length_error("operator- vector size mismatch");

        vector res(lterm.size());
        std::transform(
            std::execution::par_unseq, 
            lterm.begin(), lterm.end(), 
            rterm.begin(), 
            res.begin(), 
            std::minus<flt>()
        );

        return res;
    };


    /*
     *  minus-equals operations, returns reference to self after decrementation (elementwise and scalar)
     */

    vector& operator-=(vector& lterm, const flt& rterm) {
        vector res(lterm.size()), vec(lterm.size(), rterm);
        std::transform(std::execution::par_unseq, 
            lterm.begin(), lterm.end(), 
            vec.begin(), 
            res.begin(), 
            std::minus<flt>()
        );

        lterm = std::move(res);

        return lterm;
    };

    vector& operator-=(vector& lterm, const vector& rterm) {
        if(lterm.size() != rterm.size()) throw std::length_error("operator-= vector size mismatch");

        vector res(lterm.size());
        std::transform(std::execution::par_unseq, 
            lterm.begin(), lterm.end(), 
            rterm.begin(), 
            res.begin(), 
            std::minus<flt>()
        );

        lterm = std::move(res);

        return lterm;
    };


    /*
     *  multiplication operations: scalar product, dot product and hadamarand (elementwise) product respectively
     */

    flt operator*(const vector& lterm, const vector& rterm) {
        if(lterm.size() != rterm.size()) throw std::length_error("operator* vector size mismatch");

        return std::transform_reduce(
            std::execution::par_unseq, 
            lterm.begin(), lterm.end(), 
            rterm.begin(), 
            0.0f
        );
    };


    vector operator*(const vector& lterm, const flt& rterm) {
        vector res(lterm.size()), vec(lterm.size(), rterm);
        std::transform(
            std::execution::par_unseq,
            lterm.begin(), lterm.end(), 
            vec.begin(), 
            res.begin(), 
            std::multiplies<flt>()
        );

        return res;
    };

    vector operator&(const vector& lterm, const vector& rterm) {
        if(lterm.size() != rterm.size()) throw std::length_error("operator& vector size mismatch");

        vector res(lterm.size());
        std::transform(
            std::execution::par_unseq, 
            lterm.begin(), lterm.end(), 
            rterm.begin(), 
            res.begin(), 
            std::multiplies<flt>()
        );

        return res;
    };

    vector operator&(const vector& lterm, const flt& rterm) {
        return lterm * rterm;
    }


    /*
     *  times-equals operations: scalar product and hadamarand (elementwise) product respectively
     */

    vector& operator*=(vector& lterm, const flt& rterm) {
        vector res(lterm.size()), vec(lterm.size(), rterm);
        std::transform(
            std::execution::par_unseq, 
            lterm.begin(), lterm.end(), 
            vec.begin(), 
            res.begin(), 
            std::multiplies<flt>()
        );

        lterm = std::move(res);

        return lterm;
    };

    vector& operator&=(vector& lterm, const vector& rterm) {
        if(lterm.size() != rterm.size()) throw std::length_error("operator&= vector size mismatch");

        vector res(lterm.size());
        std::transform(
            std::execution::par_unseq, 
            lterm.begin(), lterm.end(), 
            rterm.begin(), 
            res.begin(), 
            std::multiplies<flt>()
        );

        lterm = std::move(res);

        return lterm;
    };
}