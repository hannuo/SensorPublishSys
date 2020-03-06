#include "CBarometricDemo.h"

bool CBarometricDemo::init(PARAM_TAB sensor_param)
{
	std::stringstream ss(sensor_param["interval"]);
	uint32_t val;
	ss >> val;
	interval(val);
	return true;
}

bool CBarometricDemo::start()
{
	return false;
}

bool CBarometricDemo::publish()
{
	BAROMETRIC_DATA_STRU data;
	//TODO:get_data from driver
	//std::cout << "CBarometricDemo publish!" << std::endl;
	CBarometric::publish(data);
	return true;

}
