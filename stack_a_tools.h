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

template <typename T>
bool stackCmp(T& first, T& second) {
    if (first.size() != second.size())
        return false;

    //const auto* m1 = &first.bottom();
    //const auto* m2 = &second.bottom();

    const auto* m1 = (typeof(first.top())*) ((uintptr_t) &first.top() & ~(uintptr_t) (pow(2, first.size() + 1) - 1));
    const auto* m2 = (typeof(first.top())*) ((uintptr_t) &second.top() & ~(uintptr_t) (pow(2, second.size() + 1) - 1));
    const size_t n = first.size();

    for (size_t j = 0; j < n; ++j) {
        auto diff = m1[j] - m2[j];
        if (diff != 0)
            return false;
    }

    return true;
}

template <typename T>
bool constTime_stackCmp(T& first, T&second)
{
    if (first.size() != second.size())
        return false;

    //const auto* m1 = &first.bottom();
    //const auto* m2 = &second.bottom();

    const auto* m1 = (typeof(first.top())*) ((uintptr_t) &first.top() & ~(uintptr_t) (pow(2, first.size() + 1) - 1));
    const auto* m2 = (typeof(first.top())*) ((uintptr_t) &second.top() & ~(uintptr_t) (pow(2, second.size() + 1) - 1));
    const size_t n = first.size();

    const auto* pm1 = m1 + n;
    const auto* pm2 = m2 + n;
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
