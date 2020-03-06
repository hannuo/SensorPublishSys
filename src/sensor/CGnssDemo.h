#pragma once
#include "CGnss.h"
class CGnssDemo :public CGnss
{
public:
	CGnssDemo()	{ std::cout << "CGnssDemo" << std::endl; }
	virtual ~CGnssDemo() {  }
	virtual bool init(PARAM_TAB sensor_param);
	virtual bool start();
	virtual bool publish();
private:

};

