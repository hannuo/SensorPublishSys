#include <iostream>
#include "../buffer/subscriber.hpp"
#include "../comm/ComonStruct.h"
#ifndef CALG_BASE_H
#define CALG_BASE_H

class CAlg_base
{
public:
	CAlg_base() {}
	virtual ~CAlg_base() {}

	virtual bool init() = 0;

	virtual bool start() = 0;

	virtual bool stop() = 0;

	virtual std::string GetAlgName() = 0;

};

#endif