#include "arithmeticAverage.hpp"
#include <algorithm>
#include <cmath>
#include <numeric>

#include <iostream>

float ArithmeticAverage(const std::vector<int>& v1, const std::vector<int>& v2) {
    float sum = 0;
    sum = std::accumulate(v1.begin(), v1.end(), sum);
    sum = std::accumulate(v2.begin(), v2.end(), sum);

    return (sum / (v1.size() + v2.size()));
}

float Distance(const std::vector<int>& v1, const std::vector<int>& v2) {
    float sum_squared = 0.0;

    if (v1.size() == v2.size()) {
        auto it1 = v1.begin();
        auto it2 = v2.begin();
        for (; it1 != v1.end(); it1++, it2++) {
            sum_squared += pow(*it1 - *it2, 2);
        }
    }

    return sqrt(sum_squared);
}