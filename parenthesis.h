#ifndef _PARENTHESIS_H
#define _PARENTHESIS_H

#include <iostream>
#include <string>
#include <exception>
#include <stack>

#include "stack_tools.h"

using std::string;

template <class Stack>
bool checkPars(string sequence)
{
    Stack stack;

    if (sequence.empty())
        return true;

    for (char & i : sequence) {
        switch (i) {
            case '(':
            case '[':
            case '{':
                stack.push(i);
                break;

            case ')':
                if (stack.size() == 0 || stack.top() != '(') {
                    return false;
                } else
                    stack.pop();

                break;

            case ']':
                if (stack.size() == 0 || stack.top() != '[') {
                    return false;
                } else
                    stack.pop();

                break;

            case '}':
                if (stack.size() == 0 || stack.top() != '{') {
                    return false;
                } else
                    stack.pop();

                break;

            default:
                exit(-2);
        }
    }

    if (stack.size() == 0)
        return true;

    return false;
}

template <class Stack>
long long getIndexAtWrongPar(string seq)
{
    Stack s;
    std::stack<long long> index;

    for (int i = 0; i < seq.length(); ++i) {
        switch(seq[i]) {
            case '(':
            case '[':
            case '{':
                s.push(seq[i]);
                index.push(i);
                break;

            case ')':
                if (s.size() < 1 || s.top() != '(')
                    return i;
                else {
                    s.pop();
                    index.pop();
                }
                break;

            case ']':
                if (s.size() < 1 || s.top() != '[')
                    return i;
                else {
                    s.pop();
                    index.pop();
                }
                break;

            case '}':
                if (s.size() < 1 || s.top() != '{')
                    return i;
                else {
                    s.pop();
                    index.pop();
                }
                break;
        }
    }

    if (s.size() != 0) {
        reverseStack(index);
        return index.top();
    }

    return -1;
}

#endif //_PARENTHESIS_H
