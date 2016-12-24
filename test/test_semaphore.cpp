
#include <Semaphore.h>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// 任务队列
vector<int> tasks;
mutex g_tasks_mutex;

// 缓冲区大小
size_t const max_queue_size = 100;

size_t const test_count = 30;

Semaphore g_empty_s(0);
Semaphore g_full_s(max_queue_size);

void producer() {
	size_t count = test_count;
	while (count--)
	{
		g_full_s.P();	// 队列满了吗？
		std::unique_lock<std::mutex> lock(g_tasks_mutex);
		int task = rand();
		cout << "thread producer:task=" << task << endl;
		tasks.push_back(task);
		g_empty_s.V();	//	塞入了一个
	}
}

void consumer() {
	size_t count = test_count;
	while (count)	// 逻辑循环
	{
		// 一次性消耗完当前队列
		vector<int> tmp;
		{
			size_t size = 0;
			{
				std::unique_lock<std::mutex> lock(g_tasks_mutex);
				size = tasks.size();
			}
			while (size--)
			{
				g_empty_s.P();	// 队列是否为空？
				std::unique_lock<std::mutex> lock(g_tasks_mutex);
				tmp.push_back(tasks[0]);
				tasks.erase(tasks.begin());
				g_full_s.V();	// 消耗了一个
			}
		}
		// 一次性获得当前所有
		if (tmp.size())
		{
			std::unique_lock<std::mutex> lock(g_tasks_mutex);	// 这行是保护控制台
			cout << "thread consumer:task=";
			for_each(tmp.begin(), tmp.end(), [&](int task) {
				cout << task << ",";
			});
			cout << endl;
			count -= tmp.size();
		}
	}
}

int main(){
	std::thread producer_t(producer);
	std::thread consumer_t(consumer);
	producer_t.join();
	consumer_t.join();

	return 0;
}