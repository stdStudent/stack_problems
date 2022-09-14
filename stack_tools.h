#ifndef STACK_STACK_TOOLS_H
#define STACK_STACK_TOOLS_H

#include <string>
#include <cmath>
#include <vector>

#include "aides.h"

using std::string;

template <typename T>
comptime void putToStack(T& dest, string& str)
{
    if (str.length() > 1000)
        str.resize(1000);

    dest.push(str);
}

/* move semantics */
template <typename T>
comptime void putToStack(T& dest, string&& str)
{
    if (str.length() > 1000)
        str.resize(1000);

    dest.push(str);
}

template <typename T>
comptime bool stackCmp(T& first, T& second) {
    if (first.size() != second.size())
        return false;

    const size_t a = first.size();

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
comptime bool isSubStack(T& stack, T& substack) {
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
comptime void deleteCommonElems(T& stack, const U& elem)
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

#endif //STACK_STACK_TOOLS_H
