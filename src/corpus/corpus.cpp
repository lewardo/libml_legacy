#include <fstream>
#include <iostream>
#include <vector>
#include <initializer_list>
#include <string>
#include <regex>

#include "corpus.h"

template <typename t>
Corpus::base<t>::base(std::string path) {
    std::ifstream src = std::ifstream(path, std::ifstream::in);
    const std::regex title = std::regex("^libml:(set|map)$");

    std::smatch match;
    std::string line;

    std::getline(src, line);

    if(std::regex_search(line, match, title)) {
        switch(match.str(1)[0]){
            case 's': {
                const std::regex header = std::regex("^([vmt])\\s+(?:(?:\\(\\s*(\\d+)\\s*\\)\\s*)|(?:\\(\\s*(\\d+)[, ]\\s*(\\d+)\\s*\\)\\s*))\\[\\s*(\\d+)\\]\\s*$");



                break;
            } 

            case 'm': {
                const std::regex header = std::regex("^([vmt])\\s+(?:(?:\\(\\s*(\\d+)\\s*\\)\\s*)(?:\\(\\s*(\\d+)\\s*\\)\\s*)|(?:\\(\\s*(\\d+)[, ]\\s*(\\d+)\\s*\\)\\s*)(?:\\(\\s*(\\d+)[, ]\\s*(\\d+)\\s*\\)\\s*))\\[\\s*(\\d+)\\]\\s*$");

                std::getline(src, line);

                if(std::regex_search(line, match, header)) {
                    const int ngroups = std::count_if(match.begin(), match.end(), [&](std::ssub_match g) { return g.length() > 0; }) - 1;

                    std::cout << ngroups << std::endl;
                }

                break;
            }
        }
    }

}

template <typename t>
Corpus::base<t>::base(std::initializer_list<t> init) : data(init) {

}

template class Corpus::base<Corpus::f32>;
template class Corpus::base<Corpus::df32>;

