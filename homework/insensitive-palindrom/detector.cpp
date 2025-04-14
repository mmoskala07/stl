#include "detector.hpp"
#include <algorithm>
#include <iostream>

std::string toLowerAndRemoveSpecial(const std::string& input) {
    std::string result;
    result.reserve(input.size());

    std::for_each(input.begin(), input.end(), [&result](char c) {
        if (std::isalnum(static_cast<unsigned char>(c))) {
            result += std::tolower(static_cast<unsigned char>(c));
        }
    });

    return result;
}

bool is_palindrome(std::string word) {
    std::string word_raw = toLowerAndRemoveSpecial(word);
    std::string word_raw_reverse = word_raw;

    std::reverse_copy(word_raw.begin(), word_raw.end(), word_raw_reverse.begin());

    return std::equal(word_raw.begin(), word_raw.end(), word_raw_reverse.begin(), word_raw_reverse.end());
}