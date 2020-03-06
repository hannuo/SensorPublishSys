#pragma once
#include "CImu.h"
class CImuDemo :public CImu
{
public:
	CImuDemo()	{ interval(5); }
	virtual ~CImuDemo() {}
	virtual bool init(PARAM_TAB globle_param, PARAM_TAB sensor_param);
	virtual bool start();
private:

};

