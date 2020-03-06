#pragma once
#include "CSensor.h"
#include "../buffer/CQueueFactory.h"
#include "../comm/ComonStruct.h"


class CImu :public CSensor
{
public:
	CImu() 
	{
		m_publiser = CQueueFactory::create_publiser<IMU_DATA_STRU>(type());
	}
	~CImu() { delete m_publiser; }

	virtual const std::string type() { return "IMU"; }
	virtual bool publish(IMU_DATA_STRU& data) { m_publiser->write(data); return true; }

private:
	publisher<IMU_DATA_STRU>* m_publiser;
};