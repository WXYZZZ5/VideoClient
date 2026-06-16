#ifndef GLOBALCLOCK_H
#define GLOBALCLOCK_H

#include<mutex>
#include<chrono>
#include<atomic>
class globalClock
{


public:
    globalClock();
    static globalClock *getInstance();

    int64_t getClock();
    void setClock(int64_t _clock);
    void initClock();
    void setSysemClock(std::chrono::system_clock::time_point clock);
    std::chrono::system_clock::time_point getSystemClock();

private:
    std::atomic<int64_t> clock; //ms
    std::mutex sysMutex;
    std::chrono::system_clock::time_point sysClock;
};

#endif // GLOBALCLOCK_H
