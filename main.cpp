#include <iostream>
#include <string>
#include <stack>

#include "stack_a.h"
#include "stack_a_tools.h"
#include "string_tools.h"
#include "codeTimer.h"

using std::string,
      std::cout,
      std::endl;


int main()
{
    /*stack_a<string> a_stack;

    string test_str = randStr(998);
    putToStack(a_stack, test_str);
    cout << a_stack.top() << endl;

    putToStack(a_stack, "5rgrewg34gtwrf344tgwfw4t43twf");
    cout << a_stack.top() << endl;

    codeTimer<std::chrono::milliseconds> timer;

    std::stack<string> std_stack;

    timer.start("std_stack");
    {
        for (size_t i = 0; i < 3'000'000; ++i)
            putToStack(std_stack, test_str);
    }
    timer.stop();

    timer.start("a_stack");
    {
        for (size_t i = 0; i < 3'000'000; ++i)
            putToStack(a_stack, test_str);
    }
    timer.stop();

    timer.start("std_stack + move &&");
    {
        for (size_t i = 0; i < 3'000'000; ++i)
            putToStack(std_stack, "vnoerwqp8jwnfrf8qwpn8c44ccwaurcnp8wqfn894fn893nf83p489fjwwnrfuiwnqr89fpqw4f");
    }
    timer.stop();

    timer.start("a_stack + move &&");
    {
        for (size_t i = 0; i < 3'000'000; ++i)
            putToStack(a_stack, "vnoerwqp8jwnfrf8qwpn8c44ccwaurcnp8wqfn894fn893nf83p489fjwwnrfuiwnqr89fpqw4f");
    }
    timer.stop();*/

    stack_a<int> stack_a_1, stack_a_2;
    stack_a_1.push(1);
    stack_a_1.push(2);
    stack_a_1.push(4);

    stack_a_2.push(1);
    stack_a_2.push(2);
    stack_a_2.push(4);

    //cout << basicStackCmp(stack_a_1, stack_a_2) << endl;
    cout << stackCmp(stack_a_1, stack_a_2) << endl;
    cout << constTime_stackCmp(stack_a_1, stack_a_2) << endl;
    cout << &stack_a_2.bottom() << endl;
    cout << &stack_a_2.top() << endl;
    auto* tmp = (void*) ((uintptr_t) &stack_a_2.top() & ~(uintptr_t) (pow(2, stack_a_2.size() + 1) - 1));
    cout << tmp << " " << pow(2, stack_a_2.size() + 1) - 1 << endl;


    return 0;
}
