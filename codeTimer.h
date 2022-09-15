#ifndef _TIMER_H
#define _TIMER_H

#include <chrono>
#include <string>
#include <utility>

template<class T = std::chrono::milliseconds>
class codeTimer {

private:
    using clock = std::conditional_t<std::chrono::high_resolution_clock::is_steady,
                  std::chrono::high_resolution_clock,
                  std::chrono::steady_clock>;

    clock::time_point mStart;
    clock::time_point mEnd;

    std::string msg;

public:
    void start()
    {
        mStart = clock::now();
    }

    void start(std::string message)
    {
        msg = std::move(message);
        mStart = clock::now();
    }

    void stop()
    {
        mEnd = clock::now();
        std::cout << (!msg.empty() ? ("[" + msg + "] ") : "")
                  << "Time elapsed: "
                  << std::chrono::duration_cast<T>(mEnd - mStart).count()
                  << std::endl;
    }
};

#endif //_TIMER_H
