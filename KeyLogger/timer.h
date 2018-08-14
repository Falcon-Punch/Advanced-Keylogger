#ifndef _TIMER_H_
#define _TIMER_H_

#include <thread>
#include <chrono>

class Timer
{
	std::thread Thread;
	bool alive = false;
	long callNumber = -1L;
	long repeatCount = -1L;
	std::chrono::milliseconds interval = std::chrono::milliseconds(0);
	std::function<void(void)> funct = nullptr;

}
#endif // _TIMER_H_