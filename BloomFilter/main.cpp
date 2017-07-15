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
    std::cout << "Jeg æder blåbærsyltetøj!" << std::endl;
    
    auto filter_size = -1 * (ELEMENTS * log(FALSE_POSITIVES)) / (log(2.0) * log(2.0));
    auto hash_functions = filter_size / ELEMENTS * log(2.0);

    //struct timespec start, finish;
    
    BloomFilter::BloomFilter bf(filter_size, hash_functions);

    auto present = false;
    auto s1 = "5";
    auto s2 = "101";
    auto s3 = "987654";
    auto s4 = "1987654";

    std::vector<std::string> v;
    v.reserve(ELEMENTS);

    for (auto i = 0; i < ELEMENTS; ++i) {
        std::ostringstream oss;
        oss << i;
        v.emplace_back(oss.str().c_str());
    }

    std::clock_t begin = clock();
    //clock_gettime(CLOCK_MONOTONIC, &start);
    
    for (auto i : v) {
        bf.add(reinterpret_cast<const uint8_t *>(i.c_str()), i.length());
    }

    std::clock_t end = clock();
    auto elapsed = double(end - begin);
    //clock_gettime(CLOCK_MONOTONIC, &finish);
    //auto elapsed = (finish.tv_nsec - start.tv_nsec);
    std::cout << "Time spent inserting into Bloom filter: " << elapsed << std::endl;

    present = bf.possiblyContains(reinterpret_cast<const uint8_t *>(s1), strlen(s1));
    
    if (present) {
        std::cout << "Teksten '" << s1 << "' findes." << std::endl;
    } else {
        std::cout << "Teksten '" << s1 << "' findes ikke." << std::endl;
    }

    present = bf.possiblyContains(reinterpret_cast<const uint8_t*>(s2), strlen(s2));
    
    if (present) {
        std::cout << "Teksten '" << s2 << "' findes." << std::endl;
    } else {
        std::cout << "Teksten '" << s2 << "' findes ikke." << std::endl;
    }

    present = bf.possiblyContains(reinterpret_cast<const uint8_t*>(s3), strlen(s3));
    
    if (present) {
        std::cout << "Teksten '" << s3 << "' findes." << std::endl;
    } else {
        std::cout << "Teksten '" << s3 << "' findes ikke." << std::endl;
    }
    
    present = bf.possiblyContains(reinterpret_cast<const uint8_t*>(s4), strlen(s4));
    
    if (present) {
        std::cout << "Teksten '" << s4 << "' findes." << std::endl;
    } else {
        std::cout << "Teksten '" << s4 << "' findes ikke." << std::endl;
    }
    
    return 0;
}
