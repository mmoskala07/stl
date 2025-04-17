#include "advancedCalculator.hpp"
#include <algorithm>
#include <cmath>
#include <functional>
#include <map>

double calculate_factorial(double num) {
    if (num >= 0) {
        return std::tgamma(num + 1.0);
    } else {
        return -std::tgamma((-1.0 * num) + 1.0);
    }
}

std::map<char, std::function<double(double, double)>> func_map = {
    {operation::add, [](double x, double y) { return x + y; }},
    {operation::mul, [](double x, double y) { return x * y; }},
    {operation::div, [](double x, double y) { return x / y; }},
    {operation::sub, [](double x, double y) { return x - y; }},
    {operation::mod, [](double x, double y) { return int(x) % int(y); }},
    {operation::fac, [](double x, double y) { return calculate_factorial(x); }},
    {operation::pow, [](double x, double y) { return std::pow(x, y); }},
    {operation::sqr, [](double x, double y) { return std::pow(x, 1.0 / y); }}};

ErrorCode evaluate_input_get_operation_iter(std::string& input, std::string::iterator& it_operation) {
    ErrorCode rc = ErrorCode::OK;

    auto f_allowed_values = [](char c) { return (std::isdigit(c) || c == '.' || func_map.count(c) == 1); };

    if (std::all_of(input.begin(), input.end(), f_allowed_values)) {
        if ((std::isdigit(*input.begin()) || *input.begin() == operation::sub) &&
            (std::isdigit(*(std::prev(input.end()))) || *(std::prev(input.end())) == operation::fac)) {
            auto f_operators = [](char c) { return func_map.count(c) == 1; };
            size_t cnt_operators = std::count_if(std::next(input.begin()), input.end(), f_operators);
            auto f_operator_sub = [](char c) { return c == operation::sub; };
            size_t cnt_operator_sub = std::count_if(std::next(input.begin()), input.end(), f_operator_sub);

            if ((cnt_operators == 1) || (cnt_operators == 2 && cnt_operator_sub >= 1)) {
                it_operation = std::find_if(std::next(input.begin()), input.end(), f_operators);
            } else {
                rc = ErrorCode::BadFormat;
            }
        } else {
            rc = ErrorCode::BadFormat;
        }
    } else {
        rc = ErrorCode::BadCharacter;
    }
    return rc;
}

ErrorCode evaluate_input_get_number(std::string& str_number, double& number, bool& is_integer) {
    ErrorCode rc = ErrorCode::OK;
    size_t dots = std::count(str_number.begin(), str_number.end(), '.');

    if (dots == 0) {
        number = std::stoi(str_number);
        is_integer = true;
    } else if (dots == 1) {
        number = std::stod(str_number);
        is_integer = false;
    } else {
        rc = ErrorCode::BadFormat;
    }
    return rc;
}

ErrorCode evaluate_input_verify_operation_parameters(char sign, std::string x_str, std::string y_str, double& x, double& y) {
    ErrorCode rc = ErrorCode::OK;

    bool x_is_integer = false;
    ErrorCode rc_x = evaluate_input_get_number(x_str, x, x_is_integer);
    (ErrorCode::OK == rc_x) ? (rc = rc) : (rc = rc_x);

    if (operation::fac == sign && ErrorCode::OK == rc) {
        if (y_str.size() > 0) {
            rc = ErrorCode::BadFormat;
        }
    } else {
        bool y_is_integer = false;
        ErrorCode rc_y = evaluate_input_get_number(y_str, y, y_is_integer);
        (ErrorCode::OK == rc_y) ? (rc = rc) : (rc = rc_y);

        if (ErrorCode::OK == rc) {
            switch (sign) {
            case operation::div: {
                if (0 == y)
                    rc = ErrorCode::DivideBy0;
                break;
            }
            case operation::sqr: {
                if (x < 0)
                    rc = ErrorCode::SqrtOfNegativeNumber;
                break;
            }
            case operation::mod: {
                if (!(x_is_integer && y_is_integer))
                    rc = ErrorCode::ModuleOfNonIntegerValue;
                break;
            }
            default:
                break;
            }
        }
    }
    return rc;
}

ErrorCode evaluate_input(std::string input, double& x, double& y, char& sign) {
    ErrorCode rc = ErrorCode::OK;
    std::string::iterator operation_iter = input.begin();

    input.erase(std::remove_if(input.begin(), input.end(), ::isspace), input.end());
    rc = evaluate_input_get_operation_iter(input, operation_iter);

    if (ErrorCode::OK == rc) {
        sign = *operation_iter;

        std::string x_str = std::string(input.begin(), operation_iter);
        std::string y_str = std::string(std::next(operation_iter), input.end());

        rc = evaluate_input_verify_operation_parameters(sign, x_str, y_str, x, y);
    }

    return rc;
}

ErrorCode process(std::string input, double* out) {
    double x = 0, y = 0;
    char sign = operation::none;

    ErrorCode rc = evaluate_input(input, x, y, sign);

    if (ErrorCode::OK == rc) {
        std::function<double(double, double)> func = func_map[sign];
        *out = func(x, y);
    }

    return rc;
}
