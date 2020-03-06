#include "CSensorGrp.h"
#include "CSensorFactory.h"
#include "../comm/ConfigParse.h"
#include <sstream>
CSensorGrp::CSensorGrp()
{
	std::cout << "CSensorGrp" << std::endl;
}
bool CSensorGrp::init(PARAM_TAB sensor_param)
{	
	for (auto it : sensor_param)
	{
		if (it.second == "GROUP")
		{
			continue;
		}

		PARAM_TAB param;
		bool ret = ConfigParse::parse_cfg_mapstring(it.second, param);
		if (!ret) { continue; }
		if (param.find("type") == param.end()) { continue; }

		CSensor * pSensorObj = CSensorFactory::create(param["type"]);
		if (nullptr == pSensorObj)
		{
			std::cout << "CSensorGrp create" << param["type"] << "fail!" << std::endl;
			continue;
		}
		if (!pSensorObj->init(param))
		{
			continue;
		}
		add(pSensorObj);
		interval(pSensorObj->interval());
	}

	return true;
}

bool CSensorGrp::start()
{
	for (auto it : m_sensors)
	{
		it.second->start();
	}
	return true;
}

bool CSensorGrp::publish()
{
	for (auto it : m_sensors)
	{
		it.second->publish();
	}
	return true;
}

void CSensorGrp::add(CSensor * sensor)
{
	m_sensors[sensor->type()] = sensor;
}
