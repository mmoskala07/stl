#include "vowel.hpp"
#include <algorithm>

void removeVowels(std::vector<std::string>& vec) {
    char vowels[] = {'a', 'e', 'i', 'o', 'u', 'y',
                     'A', 'E', 'I', 'O', 'U', 'Y'};

    for (std::string& str : vec) {
        for (char vowel : vowels) {
            str.erase(std::remove(str.begin(), str.end(), vowel), str.end());
        }
    }
}