#include "CSensorFactory.h"
#include "CImuDemo.h"
#include <map>
std::map<std::string ,CSensor*> g_sensors_map;
void CSensorFactory::create(std::string cfg_file)
{

}
CSensor * CSensorFactory::create(std::string type , std::string sub_type)
{
	if (IMU == type)
	{
		if ("default" == sub_type)
		{
			return new CImuDemo();
		}
	}

	if (COMPASS == type)
	{

	}

	if (GNSS == type)
	{

	}

	if (BAROMETRIC == type)
	{

	}

	if (CAMERA == type)
	{

	}

	if (POLCAMERA == type)
	{

	}

	if (GROUP == type)
	{

	}
	return nullptr;
}
