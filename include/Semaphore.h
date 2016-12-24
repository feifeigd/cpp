
#pragma once

#include <mutex>
#include <condition_variable>

/// 信号量
class Semaphore{
	Semaphore(Semaphore const&) = delete;

	/// 队列的容量
	size_t _value;	
	std::mutex _mutex;
	std::condition_variable _condition;
public:
	Semaphore(size_t value);

	/// P操作，试图减1，如果_value为，进入阻塞，直到_value不为0，然后减1，返回
	void P();

	/// V操作，跟P相反，将_value加1，如果之前_value已经为0，则等待P操作的线程会被激活	
	void V();
};
