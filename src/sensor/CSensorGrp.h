#pragma once
#include "CSensor.h"
class CSensorGrp :public CSensor
{
public:
	CSensorGrp();

	~CSensorGrp() 
	{
		for (auto it: m_sensors)
		{
			delete it.second;
		}
	}

	virtual const std::string type() { return "GROUP"; }
	virtual bool init(PARAM_TAB sensor_param);
	virtual bool start();
	virtual bool publish();


private:
	void add(CSensor* sensor);

private:
	std::map<std::string, CSensor*> m_sensors;
};