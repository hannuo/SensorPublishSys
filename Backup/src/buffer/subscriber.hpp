#pragma once
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex
#include <queue>
//#include "publisher.hpp"
template<typename T>
class subscriber
{
	
public:
	subscriber(std::string name , uint32_t size)
	{ 
		m_name = name; 
		m_queue_size = size;
	}
	~subscriber() { }

	bool read(T& t)
	{
		std::unique_lock<std::mutex> uni_lock(m_mutex);
		if (m_queue.empty())
		{
			return false;
		}

		t = *(m_queue.front());
		m_queue.pop();

		return true;
	}

	void write(std::shared_ptr<T>& t)
	{
		std::unique_lock<std::mutex> uni_lock(m_mutex);

		if (m_queue.size() >= m_queue_size)
		{
			//TODO: 如果队列长度超过设定长度,3种处理方式可选
			//1.删除队首的元素；
			//2.清空队列；
			//3.放弃本次写入；

			//TODO: log
		}

		m_queue.push(t);
	}
private:
	std::mutex m_mutex;
	std::string m_name;
	std::queue<std::shared_ptr<T>> m_queue;
	uint32_t m_queue_size;
	
};
