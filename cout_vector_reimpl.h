#ifndef UTIL_INCLUDE_COUT_VECTOR_REIMPL_H
#define UTIL_INCLUDE_COUT_VECTOR_REIMPL_H

#include <iostream>
#include <vector>
#include <iterator>

template<typename T>
std::ostream &operator<<(std::ostream &os, std::vector<T> vec)
{
    os << "{ ";
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<T>(os, " "));
    os << "}";
    return os;
}

#endif // !UTIL_INCLUDE_COUT_VECTOR_REIMPL_H