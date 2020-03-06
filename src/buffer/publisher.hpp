#pragma once
#include <iostream>       // std::cout
#include <mutex>          // std::mutex
#include <set>
#include <memory>
#include <typeinfo>
#include "subscriber.hpp"

template<typename T>
class publisher :public publisher_base
{	
public:
	~publisher() 
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		for (auto it : subs) { delete it; }
		subs.clear();
	}

	publisher(std::string type) { m_type = type; }
	std::string type() { return m_type; }

	void insert_subscriber(subscriber_base* p)
	{ 
		std::unique_lock<std::mutex> lock(m_mutex);
		if (NULL != p) {subs.insert(p);}
	}

	void erase_subscriber(subscriber_base* p)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		if (NULL != p) {subs.erase(p);}		
	}

	void write(T& t)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		std::shared_ptr<T> p1 = std::make_shared<T>(t);		
		for (auto it : subs)
		{
			subscriber<T>* pSub = dynamic_cast<subscriber<T>*>(it);
			if (NULL != pSub) {pSub->write(p1);}
		}
	}
private:
	std::mutex m_mutex;
	std::string m_type;
	std::set<subscriber_base*>  subs;
};
