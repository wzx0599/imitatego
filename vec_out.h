#ifndef VEC_OUT_H
#define VEC_OUT_H

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

#endif // VEC_OUT_H