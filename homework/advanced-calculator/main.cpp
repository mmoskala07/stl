#include <iostream>
#include <string>
#include "advancedCalculator.hpp"

int main() {
    double result = 0;
    std::string command = "-54.31 - -0.69";

    ErrorCode rc = process(command, &result);

    std::cout << command << " = " << result << std::endl;
}