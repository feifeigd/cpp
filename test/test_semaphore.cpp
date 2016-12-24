
#include <Semaphore.h>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// �������
vector<int> tasks;
mutex g_tasks_mutex;

// ��������С
size_t const max_queue_size = 100;

size_t const test_count = 30;

Semaphore g_empty_s(0);
Semaphore g_full_s(max_queue_size);

void producer() {
	size_t count = test_count;
	while (count--)
	{
		g_full_s.P();	// ����������
		std::unique_lock<std::mutex> lock(g_tasks_mutex);
		int task = rand();
		cout << "thread producer:task=" << task << endl;
		tasks.push_back(task);
		g_empty_s.V();	//	������һ��
	}
}

void consumer() {
	size_t count = test_count;
	while (count)	// �߼�ѭ��
	{
		// һ���������굱ǰ����
		vector<int> tmp;
		{
			size_t size = 0;
			{
				std::unique_lock<std::mutex> lock(g_tasks_mutex);
				size = tasks.size();
			}
			while (size--)
			{
				g_empty_s.P();	// �����Ƿ�Ϊ�գ�
				std::unique_lock<std::mutex> lock(g_tasks_mutex);
				tmp.push_back(tasks[0]);
				tasks.erase(tasks.begin());
				g_full_s.V();	// ������һ��
			}
		}
		// һ���Ի�õ�ǰ����
		if (tmp.size())
		{
			std::unique_lock<std::mutex> lock(g_tasks_mutex);	// �����Ǳ�������̨
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