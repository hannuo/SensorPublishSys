#include "CCameraDemo.h"

bool CCameraDemo::init(PARAM_TAB sensor_param)
{
	std::stringstream ss(sensor_param["interval"]);
	uint32_t val;
	ss >> val;
	interval(val);
	return true;
}

bool CCameraDemo::start()
{
	return false;
}

bool CCameraDemo::publish()
{
	CAMERA_DATA_STRU data = { 2.0,3.0,3.0 };
	//TODO:get_data from driver
	//std::cout << "CCameraDemo publish!" << std::endl;
	CCamera::publish(data);
	return true;
}
