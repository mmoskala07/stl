#pragma once

#include <string>

enum class ErrorCode {
    OK,
    BadCharacter,            // znak inny niż liczba
    BadFormat,               // zły format komendy np. + 5 4, powinno być 4 + 5
    DivideBy0,               // dzielenie przez 0
    SqrtOfNegativeNumber,    // pierwiastek z liczby ujemnej
    ModuleOfNonIntegerValue  // próba obliczenia % na liczbie niecałkowitej
};

namespace operation {
constexpr char add = '+';
constexpr char mul = '*';
constexpr char div = '/';
constexpr char sub = '-';
constexpr char mod = '%';
constexpr char fac = '!';
constexpr char pow = '^';
constexpr char sqr = '$';
constexpr char none = '_';
}  // namespace operation

ErrorCode process(std::string input, double* out);