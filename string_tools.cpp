#include <iostream>
#include <string>
#include <algorithm>
#include <random>

#include "string_tools.h"

std::string randStr(size_t size)
{
    std::random_device rd;
    std::mt19937 mt(rd());

    std::uniform_int_distribution<int> alphabet('a', 'z');
    std::string result;

    std::generate_n(std::back_inserter(result), size, [&]{return alphabet(mt);});

    return result;
}