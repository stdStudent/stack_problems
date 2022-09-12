#ifndef _STACK_A_TOOLS_H
#define _STACK_A_TOOLS_H

#include <string>
#include <cmath>

using std::string;

template <typename T>
void putToStack(T& dest, string& str)
{
    if (str.length() > 1000)
        str.resize(1000);

    dest.push(str);
}

/* move semantics */
template <typename T>
void putToStack(T& dest, string&& str)
{
    if (str.length() > 1000)
        str.resize(1000);

    dest.push(str);
}

template <typename T>
bool basicStackCmp(T& first, T& second)
{
    if (first.size() != second.size())
        return false;

    T clone_first = first;
    T clone_second = second;

    while (clone_first.size()) {
        if (clone_first.top() == clone_second.top()) {
            clone_first.pop();
            clone_second.pop();
        } else
            return false;
    }
    return true;
}

template<typename T>
concept isBasicTypeOfElem = requires (T& t)
{
    { t.top() } -> std::convertible_to<unsigned char>;
    { t.top() } -> std::convertible_to<char>;

    { t.top() } -> std::convertible_to<unsigned int>;
    { t.top() } -> std::convertible_to<int>;

    { t.top() } -> std::convertible_to<long>;
    { t.top() } -> std::convertible_to<unsigned long>;

    { t.top() } -> std::convertible_to<long long>;
    { t.top() } -> std::convertible_to<size_t>;

    { t.top() } -> std::convertible_to<float>;
    { t.top() } -> std::convertible_to<double>;
    { t.top() } -> std::convertible_to<long double>;
};

template <isBasicTypeOfElem T>
bool stackCmp(T& first, T& second) {
    if (first.size() != second.size())
        return false;

    auto* tmp1 = &first.top();
    const auto* m1 = tmp1 - (first.size() - 1); // bottom 1

    auto* tmp2 = &second.top();
    const auto* m2 = tmp2 - (second.size() - 1); // bottom 2

    const size_t n = first.size();

    for (size_t j = 0; j < n; ++j) {
        auto diff = m1[j] - m2[j];
        if (diff != 0)
            return false;
    }

    return true;
}

template <isBasicTypeOfElem T>
bool constTime_stackCmp(T& first, T&second)
{
    if (first.size() != second.size())
        return false;

    auto* tmp1 = &first.top();
    const auto* _m1 = tmp1 - (first.size() - 1);
    const auto* m1 = reinterpret_cast<const unsigned char*>(_m1); // bottom 1

    auto* tmp2 = &second.top();
    const auto* _m2 = tmp2 - (second.size() - 1);
    const auto* m2 = reinterpret_cast<const unsigned char*>(_m2); // bottom 2

    size_t n = first.size() * sizeof(first.top());

    const auto *pm1 = m1 + n;
    const auto *pm2 = m2 + n;
    int res = 0;
    if (n > 0) {
        do {
            int diff = *--pm1 - *--pm2;
            res = (res & -!diff) | diff;
        } while (pm1 != m1);
    }

    if ((res > 0) - (res < 0) == 0)
        return true;
    else
        return false;
}


#endif //_STACK_A_TOOLS_H
