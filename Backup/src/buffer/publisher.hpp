#pragma once
#include <iostream>       // std::cout
#include <mutex>          // std::mutex
#include <set>
#include <memory>
#include <typeinfo>
#include "subscriber.hpp"


class publisher_base
{
public:
	virtual ~publisher_base(){}
	virtual std::string type() = 0;
};

template<typename T>
class publisher :public publisher_base
{	
public:
	~publisher() 
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		subs.clear();
	}
	publisher(std::string type) { m_type = type; }
	std::string type() { return m_type; }
	void insert_subscriber(subscriber<T>* pSub)
	{ 
		std::unique_lock<std::mutex> lock(m_mutex);
		subs.insert(pSub);
	}

	void write(T& t)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		std::shared_ptr<T> p1 = std::make_shared<T>(t);
		for (auto it : subs){ it->write(p1); }//如何算法创建一个订阅，然后析构，这里调用write会有问题吗？
	}
private:
	std::mutex m_mutex;
	std::string m_type;
	std::set<subscriber<T>*>  subs;
};
