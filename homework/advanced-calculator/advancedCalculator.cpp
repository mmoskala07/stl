#include "advancedCalculator.hpp"
#include <cmath>
#include <functional>
#include <map>
#include <algorithm>

#include <iostream>

std::map<char, std::function<double(double, double)>> func_map = {
    {operation::add, [](double x, double y) { return x + y; }},
    {operation::mul, [](double x, double y) { return x * y; }},
    {operation::div, [](double x, double y) { return x / y; }},
    {operation::sub, [](double x, double y) { return x - y; }},
    {operation::mod, [](double x, double y) { return 0; }},
    {operation::fac, [](double x, double y) { return 0; }},
    {operation::pow, [](double x, double y) { return pow(x, y); }},
    {operation::sqr, [](double x, double y) { return pow(x, 1.0 / y); }}
};

ErrorCode evaluate_input_get_operation_iter(std::string& input, std::string::iterator& it_operation)
{
    ErrorCode rc = ErrorCode::OK;

    auto f_operators = [](char c){ return !(std::isdigit(c) || c == '.'); };
    size_t cnt_operators = std::count_if(std::next(input.begin()), std::prev(input.end()), f_operators);

    if (cnt_operators > 0)
    {       
        char op = operation::none;
        auto it = std::next(input.begin());

        while (cnt_operators > 0)
        {
            it = std::find_if(it, std::prev(input.end()), f_operators);

            if (func_map.find(*it) != func_map.end())
            {
                if ((operation::none == op) || 
                    (operation::sub == op && operation::sub != *it))
                {
                    op = *it;
                    it_operation = it;
                }
            }
            else
            {
                rc = ErrorCode::BadCharacter;
                break;
            }
            it++;
            cnt_operators--;
        }
    }
    else
    {
        rc = ErrorCode::BadFormat;
    }

    return rc;
}

ErrorCode evaluate_input(std::string input, double& x, double& y, char& sign) {
    ErrorCode rc = ErrorCode::OK;
    auto operation_iter = input.begin();

    input.erase(std::remove_if(input.begin(), input.end(), ::isspace), input.end());
    rc = evaluate_input_get_operation_iter(input, operation_iter);
    
    if (ErrorCode::OK == rc)
    {
        std::string x_str = std::string(input.begin(), operation_iter);
        std::string y_str = std::string(std::next(operation_iter), input.end());
        x = std::stod(x_str);
        sign = *operation_iter;
        y = std::stod(y_str);

        switch (sign)
        {
        case operation::div:
        {
            if (0 == y)
                rc = ErrorCode::DivideBy0;
            break;
        }
        case operation::sqr:
        {
            if (x < 0)
                rc = ErrorCode::SqrtOfNegativeNumber;
            break;
        }
        case operation::mod:
        {
            if (x_str.find('.') || y_str.find("."))
                rc = ErrorCode::ModuleOfNonIntegerValue;
            break;
        }
        default:
            break;
        }
    }

    return rc;
}

ErrorCode process(std::string input, double* out) {
    double x = 0, y = 0;
    char sign;

    std::cout << "Request: " << input << std::endl;

    ErrorCode rc = evaluate_input(input, x, y, sign);

    std::cout << "x: " << x << ", y: " << y << ", sign: " << sign << std::endl;

    if (ErrorCode::OK == rc) {
        std::function<double(double, double)> func = func_map[sign];
        *out = func(x, y);
    }

    return rc;
}