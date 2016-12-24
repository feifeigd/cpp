
#pragma once

#include <mutex>
#include <condition_variable>

/// �ź���
class Semaphore{
	Semaphore(Semaphore const&) = delete;

	/// ���е�����
	size_t _value;	
	std::mutex _mutex;
	std::condition_variable _condition;
public:
	Semaphore(size_t value);

	/// P��������ͼ��1�����_valueΪ������������ֱ��_value��Ϊ0��Ȼ���1������
	void P();

	/// V��������P�෴����_value��1�����֮ǰ_value�Ѿ�Ϊ0����ȴ�P�������̻߳ᱻ����	
	void V();
};
