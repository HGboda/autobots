#include "shared.h"
#include "rtos.h"

Mutex stdio_mutex;
void prints(std::string s) // prints to serial
{
//    stdio_mutex.lock();
    pc.printf(s.c_str());
//    stdio_mutex.unlock();
}
