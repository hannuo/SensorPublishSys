#pragma once
#include <iostream>      
#include "publisher.hpp"
#include "subscriber.hpp"

class CQueueFactory
{
public:	
	template<typename T>
	static publisher<T>* create_publiser(std::string type)
	{		
		publisher<T>* obj = dynamic_cast<publisher<T>*>(get(type));
		if (NULL == obj)
		{
			obj = new publisher<T>(type);//publisher不存在，则新创建一个
			add(obj);
		}
		return obj;//publisher已经存在，则直接返回该对象
	}
	template<typename T>
	static subscriber<T>* create_subscriber(std::string type, std::string name, uint32_t size)
	{		
		publisher<T>* obj = dynamic_cast<publisher<T>*>(get(type));
		if (NULL == obj)//publisher不存在，则创建subscriber失败
		{
			return NULL;
		}
		subscriber<T>* pSub = new subscriber<T>(name, size, obj);
		obj->insert_subscriber(pSub);
		return pSub;
	}
private:
	CQueueFactory() {}
	static void add(publisher_base* obj);
	static publisher_base* get(std::string type);
};