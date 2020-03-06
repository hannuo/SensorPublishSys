#pragma once
#include "CImu.h"
class CImuDemo :public CImu
{
public:
	CImuDemo() { std::cout << "Init CImuDemo___" << std::endl; }
	virtual ~CImuDemo() {}
	virtual bool init(PARAM_TAB sensor_param);
	virtual bool start();
	virtual bool publish();
private:

};

