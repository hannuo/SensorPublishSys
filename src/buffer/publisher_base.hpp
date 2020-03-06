#pragma once
#include "subscriber_base.hpp"
class publisher_base
{
public:
	virtual ~publisher_base(){}
	virtual std::string type() = 0;
	virtual void insert_subscriber(subscriber_base* p) = 0;
	virtual void erase_subscriber(subscriber_base* p) = 0;
};
