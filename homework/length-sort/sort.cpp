#include "sort.hpp"
#include <algorithm>

std::deque<std::string> lengthSort(const std::forward_list<std::string>& words) {
    std::deque<std::string> sorted(words.begin(), words.end());

    std::sort(sorted.begin(), sorted.end(), [](const std::string& s1, const std::string& s2) {
        if (s1.length() == s2.length()) {
            for (size_t i = 0; i < s1.length(); i++) {
                if (s1[i] != s2[i]) {
                    return s1[i] < s2[i];
                }
            }
        } else {
            return s1.length() < s2.length();
        }
    });
    return sorted;
}
