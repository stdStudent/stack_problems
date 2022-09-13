#ifndef _STACK_A_TOOLS_H
#define _STACK_A_TOOLS_H

#include <string>
#include <cmath>
#include <vector>

#include "stack_a.h"

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
bool stackCmp(T& first, T& second) {
    if (first.size() != second.size())
        return false;

    bool cmp = true;
    int count = 0;
    std::vector<typeof(first.top())> v;
    while (count < first.size() - 1) {
        if (first.top() == second.top()) {
            v.push_back(std::move(first.top()));
            first.pop();
            second.pop();
        } else {
            cmp = false;
            break;
        }

        ++count;
    }

    for (int i =v.size() - 1; i >= 0; --i) {
        first.push(v[i]);
        second.push(v[i]);
    }

    return cmp;
}

template <typename T>
bool isSubStack(T& stack, T& substack) {
    // 14 6 9 34 6 1 2 3 4 5 6 9 34 5 1 2 3
    //      9 34 5
    if (stack.size() < substack.size())
        return false;

    bool result = false;
    std::vector<typeof(stack.top())> s, ss;

    while (stack.size() > substack.size()) {
        if (stack.top() == substack.top()) {
            s.push_back(stack.top());
            stack.pop();

            ss.push_back(substack.top());
            substack.pop();

            bool falseAlarm = false;
            while (substack.size() != 0) {
                if (stack.top() == substack.top()) {
                    s.push_back(stack.top());
                    stack.pop();
                } else {
                    for (int i = ss.size() - 1; i >= 0; --i)
                        substack.push(ss[i]);
                    falseAlarm = true;
                    break;
                }
                ss.push_back(substack.top());
                substack.pop();
            }

            if (!falseAlarm){
                result = true;
                break;
            }
        } else {
            s.push_back(stack.top());
            stack.pop();
        }
    }

    for (int i = s.size() - 1; i >= 0; --i)
        stack.push(s[i]);

    for(int i = ss.size() - 1; i >= 0; --i)
        substack.push(ss[i]);

    return result;
}

template <typename T, typename U>
void deleteCommonElems(T& stack, const U& elem)
{
    static_assert(std::same_as<typeof(stack.top()), U>);

    std::vector<U> v;
    while (stack.size() != 0) {
        if (stack.top() != elem)
            v.push_back(stack.top());

        stack.pop();
    }

    for (int i = v.size() - 1; i >= 0; --i)
        stack.push(v[i]);
}

template<typename T>
concept isBasicTypeOfElem = requires (T& t) {
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
bool stackInsideCmp(T& first, T& second)
{
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
bool stackByteByByteCmp(T& first, T&second)
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

template <isBasicTypeOfElem T>
bool isSubStackInside(T& stack, T& substack) {
    auto* tmp1 = &stack.top();
    const auto* A = tmp1 - (stack.size() - 1); // bottom 1

    auto* tmp2 = &substack.top();
    const auto* B = tmp2 - (substack.size() - 1); // bottom 2

    // Two pointers to traverse the arrays
    int i = 0, j = 0;

    // Traverse both arrays simultaneously
    while (i < stack.size() && j < substack.size()) {

        // If element matches
        // increment both pointers
        if (A[i] == B[j]) {

            i++;
            j++;

            // If array B is completely
            // traversed
            if (j == substack.size())
                return true;
        }
            // If not,
            // increment i and reset j
        else {
            i = i - j + 1;
            j = 0;
        }
    }

    return false;
}

#endif //_STACK_A_TOOLS_H
