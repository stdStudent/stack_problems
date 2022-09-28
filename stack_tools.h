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

template <typename STACK>
comptime bool stackCmp(STACK& first, STACK& second) {
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

template <class Stack>
void sortStack(Stack& orig_stack)
{
    Stack helper_stack;
    while (orig_stack.size() != 0) {
        auto element = orig_stack.top();
        orig_stack.pop();

        while (helper_stack.size() != 0 && helper_stack.top() > element) {
            orig_stack.push(helper_stack.top());
            helper_stack.pop();
        }

        helper_stack.push(element);
    }

    while (helper_stack.size() != 0) {
        orig_stack.push(helper_stack.top());
        helper_stack.pop();
    }
}

template <class Stack>
void insert_at_bottom(Stack& st, decltype(st.top()) x)
{
    if (st.size() == 0)
        st.push(x);
    else {
        auto a = st.top();
        st.pop();
        insert_at_bottom(st, x);
        st.push(a);
    }
}

template <class Stack>
void reverseStack(Stack& st) // O(n)
{
    if (st.size() > 0) {
        auto x = st.top();
        st.pop();
        reverseStack(st);
        insert_at_bottom(st, x);
    }
}

template <class Stack>
void mergeSortStack(Stack& stack) // O(n log[n])
{
    if (stack.size() == 1)
        return;

    Stack s1, s2;

    while (s1.size() < stack.size()) {
        s1.push(stack.top());
        stack.pop();
    }

    while (stack.size() != 0) {
        s2.push(stack.top());
        stack.pop();
    }

    mergeSortStack(s1); // first half of the stack
    mergeSortStack(s2); // second half --||--||--

    reverseStack(s1);
    reverseStack(s2);

    /* Now head of s1 (and s2) is the smallest one. */
    while (s1.size() != 0 && s2.size() != 0)
        if (s1.top() < s2.top()) {
            stack.push(s1.top());
            s1.pop();
        } else {
            stack.push(s2.top());
            s2.pop();
        }

    /* The tail. */
    while (s1.size() != 0) {
        stack.push(s1.top());
        s1.pop();
    }

    while (s2.size() != 0) {
        stack.push(s2.top());
        s2.pop();
    }
}

#endif //STACK_STACK_TOOLS_H
