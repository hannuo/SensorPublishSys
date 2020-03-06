#include "CCompassDemo.h"

bool CCompassDemo::init(PARAM_TAB sensor_param)
{
	std::stringstream ss(sensor_param["interval"]);
	uint32_t val;
	ss >> val;
	interval(val);
	return true;
}

bool CCompassDemo::start()
{
	return false;
}

bool CCompassDemo::publish()
{
	COMPASS_DATA_STRU data;
	//TODO:get_data from driver
	//std::cout << "CCompassDemo publish!" << std::endl;
	CCompass::publish(data);
	return true;
}
