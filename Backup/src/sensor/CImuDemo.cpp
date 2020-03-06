#include "CImuDemo.h"
#include <sstream>
bool CImuDemo::init(PARAM_TAB globle_param, PARAM_TAB sensor_param)
{
	std::stringstream ss(sensor_param["interval"]);
	uint32_t val;
	ss >> val;
	interval(val);
	return true;
}

bool CImuDemo::start()
{
	INS_DATA_STRU ins;
	ins.x = 0;
	ins.y = 0;
	ins.z = 0;
	while (1)
	{
		ins.x++;
		ins.y++;
		ins.z++;

		publish(ins);
		std::this_thread::sleep_for(std::chrono::milliseconds(interval()));
	}
	return false;
}
