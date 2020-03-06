#pragma once
#include "CCompass.h"

class CCompassDemo :public CCompass
{
public:
	CCompassDemo()	{ std::cout << "Init CCompassDemo" << std::endl; }
	~CCompassDemo() {}

	virtual bool init(PARAM_TAB sensor_param);
	virtual bool start();
	virtual bool publish();

private:

};