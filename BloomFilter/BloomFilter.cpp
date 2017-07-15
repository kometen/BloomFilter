//
//  BloomFilter.cpp
//  BloomFilter
//
//  Created by Claus Guttesen on 14.07.2017.
//  Copyright © 2017 Claus Guttesen. All rights reserved.
//

#include "BloomFilter.hpp"

BloomFilter::BloomFilter(uint64_t size, uint8_t numHashes)
    : m_bits(size), m_numHashes(numHashes) {}

std::array<uint64_t, 2> hash(const uint8_t *data, std::size_t len) {
    std::array<uint64_t, 2> hashValue;
    MurmurHash3_x64_128(data, len, 0, hashValue.data());
    
    return hashValue;
}

inline uint64_t nthHash(uint8_t n, uint64_t hashA, uint64_t hashB, uint64_t filterSize) {
    return (hashA + n * hashB) % filterSize;
}

void BloomFilter::add(const uint8_t *data, std::size_t len) {
    auto hashValues = hash(data, len);
    
    for (int n = 0; n < m_numHashes; ++n) {
        m_bits[nthHash(n, hashValues[0], hashValues[1], m_bits.size())] = true;
    }
}

bool BloomFilter::possiblyContains(const uint8_t *data, std::size_t len) const {
    auto hashValues = hash(data, len);
    
    for (int n = 0; n < m_numHashes; ++n) {
        if (!m_bits[nthHash(n, hashValues[0], hashValues[1], m_bits.size())]) {
            return false;
        }
    }
    
    return true;
}
