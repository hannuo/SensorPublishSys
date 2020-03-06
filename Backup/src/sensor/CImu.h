#pragma once
#include "CSensor.h"
#include "../buffer/CQueueFactory.h"
struct INS_DATA_STRU
{
	double x;
	double y;
	double z;
};
class CImu :public CSensor
{
public:
	CImu() 
	{
		m_publiser = CQueueFactory::create_publiser<INS_DATA_STRU>(type());
	}
	~CImu() { delete m_publiser; }

	virtual const std::string type() { return "IMU"; }
	virtual bool init(PARAM_TAB globle_param, PARAM_TAB sensor_param) ;
	virtual bool start() ;
	virtual bool publish(INS_DATA_STRU& ins) { m_publiser->write(ins); return true; }

private:
	publisher<INS_DATA_STRU>* m_publiser;
};