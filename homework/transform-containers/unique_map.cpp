#include "unique_map.hpp"
#include <algorithm>
#include <iostream>

std::map<int, std::string> removeDuplicateAndTranformToMap(std::list<std::string> in_list, std::deque<int> in_deque) {
    std::map<int, std::string> result;

    in_list.sort();
    std::sort(in_deque.begin(), in_deque.end());

    in_list.erase(std::unique(in_list.begin(), in_list.end()), in_list.end());
    in_deque.erase(std::unique(in_deque.begin(), in_deque.end()), in_deque.end());

    std::transform(in_list.begin(), in_list.end(),
                   in_deque.begin(),
                   std::inserter(result, result.end()),
                   [](auto& str, auto& num) {
                       return std::make_pair(num, str);
                   });

    return result;
}