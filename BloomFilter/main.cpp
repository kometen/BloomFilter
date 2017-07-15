//
//  main.cpp
//  BloomFilter
//
//  Created by Claus Guttesen on 14.07.2017.
//  Copyright © 2017 Claus Guttesen. All rights reserved.
//  http://blog.michaelschmatz.com/2016/04/11/how-to-write-a-bloom-filter-cpp/
//

#include <ctime>
#include <cmath>
#include <iostream>
#include <vector>
#include <sstream>

#include "BloomFilter.hpp"

const auto ELEMENTS = 1800000;
const auto FALSE_POSITIVES = 0.02;

int main(int argc, const char * argv[]) {
    auto filter_size = -1 * (ELEMENTS * log(FALSE_POSITIVES)) / (log(2.0) * log(2.0));
    auto hash_functions = filter_size / ELEMENTS * log(2.0);

    std::cout << "Elements: " << ELEMENTS << ", false positives: " << FALSE_POSITIVES << std::endl;
    std::cout << "filter size: " << filter_size << ", hash functions: " << hash_functions << std::endl;

    BloomFilter::BloomFilter bf(filter_size, hash_functions);

    auto present = false;
    std::vector<std::string> verify_elements = {
        "5", "101", "987654", "1987654", "Claus", "1799999"
    };

    std::vector<std::string> v;
    v.reserve(ELEMENTS);

    for (auto i = 0; i < ELEMENTS; ++i) {
        std::ostringstream oss;
        oss << i;
        v.emplace_back(oss.str().c_str());
    }

    std::clock_t begin = clock();
    
    for (auto i : v) {
        bf.add(reinterpret_cast<const uint8_t *>(i.c_str()), i.length());
    }

    std::clock_t end = clock();
    auto elapsed = double(end - begin);
    std::cout << "Time spent inserting into Bloom filter: " << elapsed << std::endl;

    for (auto i : verify_elements) {
        present = bf.possiblyContains(reinterpret_cast<const uint8_t *>(i.c_str()), i.size());

        if (present) {
            std::cout << "Element '" << i << "' is (probably) present." << std::endl;
        } else {
            std::cout << "Element '" << i << "' is not present." << std::endl;
        }
    }
    
    return 0;
}
