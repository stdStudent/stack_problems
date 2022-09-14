#include <iostream>
#include <string>
#include <stack>


#define enable_comptime

#include "stack_a.h"
#include "stack_l.h"
#include "stack_tools.h"
#include "stack_a_tools.h"
#include "string_tools.h"
#include "codeTimer.h"
#include "aides.h"

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

    stack_l<float> stack_a_1, stack_a_2;
    stack_a_1.push(1);
    stack_a_1.push(3);
    stack_a_1.push(3);
    stack_a_1.push(10);
    stack_a_1.push(15);
    stack_a_1.push(15);
    stack_a_1.push(2);
    stack_a_1.push(3);
    cout << stack_a_1.size() << endl;

    stack_a_2.push(1);
    stack_a_2.push(0);
    stack_a_2.push(3);
    //stack_a_2.push(1);
    //stack_a_2.push(10);
    //stack_a_2.push(15);
    //stack_a_2.push(1);

    auto* p = &stack_a_2.top();
    auto* p2 = p - 2;
    std::cout << *p << " before " << *p2 << std::endl;

    cout << stackCmp(stack_a_1, stack_a_2) << endl;
    //cout << stackInsideCmp(stack_a_1, stack_a_2) << " alt" << endl;
    //cout << stackByteByByteCmp(stack_a_1, stack_a_2) << "alt" << endl;

    cout << isSubStack(stack_a_1, stack_a_2) << endl;
    //cout << isSubStackInside(stack_a_1, stack_a_2) << " alt" << endl;

    deleteCommonElems(stack_a_2, 1.0f);

    cout << isSubStack(stack_a_1, stack_a_2) << endl;
    //cout << isSubStackInside(stack_a_1, stack_a_2) << "alt" << endl;
    cout << typeid(stack_a_1).name() << endl;

    sizeRestrictedVector<int> v(10);
    cout << v.size() << '[' << v.capacity() << ']' << endl;
    v.push_back(123);
    cout << v.size() << '[' << v.capacity() << ']' << endl;
    v.push_back(123);
    cout << v.size() << '[' << v.capacity() << ']' << endl;
    v.push_back(123);
    cout << v.size() << '[' << v.capacity() << ']' << endl;
    v.push_back(123);
    cout << v.size() << '[' << v.capacity() << ']' << endl;
    v.push_back(123);
    cout << v.size() << '[' << v.capacity() << ']' << endl;
    v.push_back(123);
    cout << v.size() << '[' << v.capacity() << ']' << endl;
    v.push_back(123);
    cout << v.size() << '[' << v.capacity() << ']' << endl;
    v.push_back(123);
    cout << v.size() << '[' << v.capacity() << ']' << endl;
    v.push_back(123);
    cout << v.size() << '[' << v.capacity() << ']' << endl;
    v.push_back(123);
    cout << v.size() << '[' << v.capacity() << ']' << endl;


    return 0;
}
