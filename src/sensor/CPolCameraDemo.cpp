#include "CPolCameraDemo.h"

bool CPolCameraDemo::init(PARAM_TAB sensor_param)
{
	std::stringstream ss(sensor_param["interval"]);
	uint32_t val;
	ss >> val;
	interval(val);
	return true;
}

bool CPolCameraDemo::start()
{
	return false;
}

bool CPolCameraDemo::publish()
{
	CAMERA_DATA_STRU data = { 4.0,4.0,4.0 };
	//TODO:get_data from driver
	//std::cout << "CPolCameraDemo publish!" << std::endl;
	CPolCamera::publish(data);
	return true;
}
