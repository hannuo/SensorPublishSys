#include "CGnssDemo.h"

bool CGnssDemo::init(PARAM_TAB sensor_param)
{
	std::stringstream ss(sensor_param["interval"]);
	uint32_t val;
	ss >> val;
	interval(val);
	return true;
}

bool CGnssDemo::start()
{
	return false;
}

bool CGnssDemo::publish()
{
	GNSS_DATA_STRU data;
	//TODO:get_data from driver
	//std::cout << "CGnssDemo publish!" << std::endl;
	CGnss::publish(data);
	return true;
}
