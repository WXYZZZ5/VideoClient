#include "globalclock.h"

globalClock::globalClock()
    :clock(0)
{}

globalClock *globalClock::getInstance()
{
    static globalClock* clock = new globalClock();
    return clock;
}

int64_t globalClock::getClock()
{
    return clock.load(std::memory_order_acquire);
}


void globalClock::setClock(int64_t _clock)
{
    clock.store(_clock,std::memory_order_release);
}

void globalClock::initClock()
{
    clock.store(0,std::memory_order_relaxed);
}

void globalClock::setSysemClock(std::chrono::system_clock::time_point clock)
{
    std::lock_guard<std::mutex>lock(sysMutex);
    sysClock = clock;
}

std::chrono::system_clock::time_point globalClock::getSystemClock()
{
    std::lock_guard<std::mutex>lock(sysMutex);
    return sysClock;
}



