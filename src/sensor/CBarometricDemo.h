#pragma once
#include "CBarometric.h"
#include <sstream>

class CBarometricDemo :public CBarometric
{
public:
	CBarometricDemo() { std::cout << "CBarometricDemo" << std::endl; }
	~CBarometricDemo(){}

	virtual bool init(PARAM_TAB sensor_param);
	virtual bool start();
	virtual bool publish();
private:
};