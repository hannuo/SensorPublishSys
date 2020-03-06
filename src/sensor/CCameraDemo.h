#pragma once
#include "CCamera.h"


class CCameraDemo :public CCamera
{
public:
	CCameraDemo(){ std::cout << "Init CCameraDemo___" << std::endl; }
	~CCameraDemo() {}

	virtual bool init(PARAM_TAB sensor_param);
	virtual bool start();
	virtual bool publish();

};