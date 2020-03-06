#pragma once
#include "CSensor.h"
#include "../buffer/CQueueFactory.h"
#include "../comm/ComonStruct.h"

class CCamera :public CSensor
{
public:
	CCamera() 
	{
		m_publiser = CQueueFactory::create_publiser<CAMERA_DATA_STRU>(type());
	}
	~CCamera() { delete m_publiser; }

	virtual const std::string type() { return "CAMERA"; }
	virtual bool publish(CAMERA_DATA_STRU& data) { m_publiser->write(data); return true; }

private:
	publisher<CAMERA_DATA_STRU>* m_publiser;
};