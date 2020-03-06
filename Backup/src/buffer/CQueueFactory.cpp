#include <iostream>       // std::cout
#include <memory>
#include <typeinfo>
#include <map>
#include <mutex>          // std::mutex
#include "CQueueFactory.h"

static std::mutex g_mutex_queue;
static std::map<std::string, publisher_base*> g_map_base;

void CQueueFactory::add(publisher_base* obj)
{
	std::unique_lock<std::mutex> lock(g_mutex_queue);
	g_map_base[obj->type()] = obj;
}

publisher_base* CQueueFactory::get(std::string type)
{
	std::unique_lock<std::mutex> lock(g_mutex_queue);
	return (g_map_base[type]);
}




