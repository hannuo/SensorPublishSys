#include "CSensorFactory.h"
#include "CImuDemo.h"
#include "CBarometricDemo.h"
#include "CCameraDemo.h"
#include "CCompassDemo.h"
#include "CGnssDemo.h"
#include "CPolCameraDemo.h"
#include "CSensorGrp.h"
#include "../comm/ConfigParse.h"
#include <map>
#include <thread>

std::map<std::string ,CSensor*> g_sensors_map;
std::map<std::string, std::thread> g_threads_map;
bool b_stop = false;
void thread_proc(CSensor * pObj)
{
	pObj->start();
	while (!b_stop)
	{
		pObj->publish();
		std::this_thread::sleep_for(std::chrono::milliseconds(pObj->interval()));
	}
}

void CSensorFactory::start_sensors()
{
	for (auto it : g_sensors_map)
	{
		g_threads_map[it.first] = std::thread(thread_proc, it.second);
	}
}
void CSensorFactory::stop_sensors()
{
	b_stop = true;
	for (auto it : g_sensors_map)
	{
		g_threads_map[it.first].join();
	}
}
bool CSensorFactory::create_sensors(std::string sensors_cfg_file)
{
	PARAM_TAB sensors;	
	bool ret = ConfigParse::parse_cfg_mapstring(sensors_cfg_file, sensors);
	if (!ret) { return false;	}
	for (auto it: sensors)
	{
		PARAM_TAB param;		
		ret = ConfigParse::parse_cfg_mapstring(it.second, param);
		if (!ret) 
		{
			return false;
		}
		if(param.find("type") == param.end()) { continue; }

		CSensor * pSensorObj = create(param["type"]);
		if(nullptr == pSensorObj)
        {
            std::cout<<"CSensorFactory create"<<param["type"]<<"fail!"<<std::endl;
            continue;
        }
		pSensorObj->init(param);
		g_sensors_map[it.first] = pSensorObj;
	}
	return true;
}

template <typename T>
CSensor * _create(){ return new T();}
CSensor * CSensorFactory::create(std::string type)
{
	std::map<std::string, std::function<CSensor *()>> map_fun;
	map_fun[IMU] = _create<CImuDemo>;
	map_fun[COMPASS] = _create<CCompassDemo>;
	map_fun[GNSS] = _create<CGnssDemo>;
	map_fun[BAROMETRIC] = _create<CBarometricDemo>;
	map_fun[CAMERA] = _create<CCameraDemo>;
	map_fun[POLCAMERA] = _create<CPolCameraDemo>;
	map_fun[GROUP] = _create<CSensorGrp>;

	if (map_fun.end() == map_fun.find(type))
	{
		return nullptr;
	}

	return map_fun[type]();
}
