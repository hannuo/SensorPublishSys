#pragma once
#include "CPolCamera.h"


class CPolCameraDemo :public CPolCamera
{
public:
	CPolCameraDemo() { std::cout << "Init CPolCameraDemo ___" << std::endl; }
	~CPolCameraDemo() {}

	virtual bool init(PARAM_TAB sensor_param);
	virtual bool start();
	virtual bool publish();
private:

};