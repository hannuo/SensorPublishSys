#include "CImuDemo.h"
#include <sstream>
bool CImuDemo::init(PARAM_TAB sensor_param)
{
	std::stringstream ss(sensor_param["interval"]);
	uint32_t val;
	ss >> val;
	interval(val);
	return true;
}

bool CImuDemo::start()
{
	return true;
}

bool CImuDemo::publish()
{
	IMU_DATA_STRU ins = { 2.0, 2.0, 2.0 };
	//TODO:get_data from driver
	//std::cout << "CImuDemo publish!" << std::endl;
	CImu::publish(ins);

	return true;
}
