
#include <Semaphore.h>

Semaphore::Semaphore(size_t value) : _value(value) {}

void Semaphore::P() {
	std::unique_lock<std::mutex> lock(_mutex);
	while (!_value)
	{
		_condition.wait(lock);
	}
	--_value;
}

void Semaphore::V() {
	std::unique_lock<std::mutex> lock(_mutex);
	++_value;
	_condition.notify_one();
}
