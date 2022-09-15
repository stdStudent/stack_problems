#ifndef STACK_STACK_TOOLS_H
#define STACK_STACK_TOOLS_H

#include <string>
#include <cmath>
#include <vector>

#include "aides.h"

using std::string;

template <typename T>
comptime void putToStack(T& dest, string& str, const size_t limit = 0)
{
    if (str.length() > limit && limit != 0)
        str.resize(limit);

    dest.push(str);
}

/* move semantics */
template <typename T>
comptime void putToStack(T& dest, string&& str, const size_t limit = 0)
{
    if (str.length() > limit && limit != 0)
        str.resize(limit);

    dest.push(str);
}

template <typename T>
comptime bool stackCmp(T& first, T& second) {
    if (first.size() != second.size())
        return false;

    bool cmp = true;
    int count = 0;
    sizeRestrictedVector<typeof(first.top())> v(first.size());

    size_t size = first.size();
    while (count < size) {
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
comptime bool isSubStack(T& stack, T& substack) {
    // 14 6 9 34 6 1 2 3 4 5 6 9 34 5 1 2 3
    //      9 34 5
    if (stack.size() < substack.size())
        return false;

    bool result = false;
    sizeRestrictedVector<typeof(stack.top())> s(stack.size()), ss(substack.size());
    //std::vector<typeof(stack.top())> s, ss;

    while (stack.size() >= substack.size()) {
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
                    ss.clear(); // max capacity restricted to substack.size()
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
comptime void deleteCommonElems(T& stack, const U& elem)
{
    static_assert(std::same_as<typeof(stack.top()), U>);

    sizeRestrictedVector<U> v(stack.size());
    while (stack.size() != 0) {
        if (stack.top() != elem)
            v.push_back(stack.top());

        stack.pop();
    }

    for (int i = v.size() - 1; i >= 0; --i)
        stack.push(v[i]);
}

#endif //STACK_STACK_TOOLS_H
