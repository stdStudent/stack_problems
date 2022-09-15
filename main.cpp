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

using std::string,
      std::cout,
      std::endl;

#define literal "apzyvkhlyfvhitgbcioqdzifgbjbbhqgibomkndysvtlkxrylryhzbelhyvtkvbtjvulgtustcwuimeoylzyogrscpwouboqsaasqcxidioisjlxlvguubsnimdtejwwzkdkzcnzslfmgtuejndbjqtplyyokueluvhxbqnopviobsdizltmanplcyppghubazushnvkmbhvsbecfihlpjlfadgmxkiarssxnehwwthtbhjisirhqfmdmftshdkkhbheedtfggqlmchzlucnaxxijgxamtaecrrawzzsnxsxfteuwfvxfuwwxterwcaigfntvmnwstgazeyqlljgadakgbubwufagjvejodriazyemgudwxgbqncmxyqsaxlurnipmqgtarkgpspubuflyrkdlvitxbrnhqnnvnixqajxodazrjuguvvsdzycetxddxgzvcvvblwmoebdexhrxfhujvidnydaepgvpxdcsqkhikshxxoihrkxejvgxlsyfrnpfghhqgkmhkqayujnwbkcstcgbmtgmyreavooalcdqavejojzarfhavppmesdzfdldpjgcorempmlohkaekdfnoiarotmdkgcxhmxjovrusdsnxqucgguswejcdajfljmqqngwiytrarzjanxtkcfagkwwldevwpptumhropkcctmrtyvgdolowzwoegdrythglztxqqlyfvvxhkmhmwtwkyevjysfzutwzmrtcgbexjuvbbyhwnhejbjnhbfanrrkekefkymgixztnrqdmotfhzvtnlxrbamulszdnhefooxwxvujixtsqgwdndeuuzjcsgmzocqrsmlrpleuzevksxpinpnwidblawvuecitwjmsxuvyhhgjcjcwtbamtuzthbnwogmeetijhahpbqysnivttocvrbuzldyyijetamuuwtwylinkzmtfxwmjolukcvgxcwinrsfqshaqagqfhzijmcazcvge"

template <class T = std::chrono::milliseconds>
void time_test(const size_t numOfElems) {
    std::stack<string> std_stack;
    stack_a<string> a_stack;
    stack_l<string> l_stack;
    cStack_l<string> cl_stack;

    string test_str = randStr(998);
    putToStack(a_stack, test_str);
    cout << "Random string: " << a_stack.top() << endl;

    codeTimer<T> timer;

    timer.start("std_stack");
    {
        for (size_t i = 0; i < numOfElems; ++i)
            putToStack(std_stack, test_str);
    }
    timer.stop();

    timer.start("a_stack");
    {
        for (size_t i = 0; i < numOfElems; ++i)
            putToStack(a_stack, test_str);
    }
    timer.stop();

    timer.start("l_stack");
    {
        for (size_t i = 0; i < numOfElems; ++i)
            putToStack(l_stack, test_str);
    }
    timer.stop();

    timer.start("cl_stack");
    {
        for (size_t i = 0; i < numOfElems; ++i)
            putToStack(cl_stack, test_str);
    }
    timer.stop();

    timer.start("std_stack + move &&");
    {
        for (size_t i = 0; i < numOfElems; ++i)
            putToStack(std_stack, literal);
    }
    timer.stop();

    timer.start("a_stack + move &&");
    {
        for (size_t i = 0; i < numOfElems; ++i)
            putToStack(a_stack, literal);
    }
    timer.stop();

    timer.start("l_stack + move &&");
    {
        for (size_t i = 0; i < numOfElems; ++i)
            putToStack(a_stack, literal);
    }
    timer.stop();

    timer.start("cl_stack + move &&");
    {
        for (size_t i = 0; i < numOfElems; ++i)
            putToStack(a_stack, literal);
    }
    timer.stop();
}

void commonStack_test() {
    std::stack<const char*> stack_a_1, stack_a_2;
//    stack_a_1.push("0");
//    stack_a_1.push("3");
//    stack_a_1.push("10");
//    stack_a_1.push("15");
//    stack_a_1.push("15");
//    stack_a_1.push("15");
//    stack_a_1.push("15");
//    stack_a_1.push("15");
//    stack_a_1.push("15");
//    stack_a_1.push("15");
//    stack_a_1.push("2");
//    stack_a_1.push("3");
//
//    stack_a_2.push("1");
//    stack_a_2.push("0");
//    stack_a_2.push("3");
//    stack_a_2.push("1");
//    stack_a_2.push("10");
//    stack_a_2.push("15");
//    stack_a_2.push("1");

    stack_a_1.push("0");
    stack_a_1.push("2");
    stack_a_1.push("3");

    stack_a_2.push("1");
    stack_a_2.push("2");
    stack_a_2.push("3");




    cout << "stackCmp():\t\t" << (stackCmp(stack_a_1, stack_a_2) ? "true" : "false")  << endl;
    cout << "isSubStack:\t\t" << (isSubStack(stack_a_1, stack_a_2) ? "true" : "false") << endl;

    //std::string s = "1";
    const char* s = "1";
    deleteCommonElems(stack_a_2, s);
    cout << "isSubStack:\t\t" << (isSubStack(stack_a_1, stack_a_2) ? "true" : "false")
         << " (after deleteCommonElems())" << endl;
}

void arrayBasedStack_test() {
    stack_a<float> a1, a2;
    a1.push(20);
    a1.push(10);
    a1.push(30);
    a1.push(40);

    a2.push(10);
    a2.push(30);

    cout << "stackInsideCmp():\t\t" << (stackInsideCmp(a1, a2) ? "true" : "false") << endl;
    cout << "stackByteByByteCmp():\t" << (stackByteByByteCmp(a1, a2) ? "true" : "false") << endl;
    cout << "isSubStackInside():\t\t" << (isSubStackInside(a1, a2) ? "true" : "false") << endl;

    deleteCommonElems(a1, 10.0f);
    cout << "isSubStackInside():\t\t" << (isSubStackInside(a1, a2) ? "true" : "false")
         << " (after deleteCommonElems())" << endl;
}

int main()
{
    //time_test<std::chrono::microseconds>(3000);

    commonStack_test();

    //arrayBasedStack_test();

    return 0;
}
