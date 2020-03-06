#pragma once
#include "CCamera.h"
#include "../buffer/CQueueFactory.h"

class CPolCamera :public CSensor
{
public:
	CPolCamera() 
	{
		m_publiser = CQueueFactory::create_publiser<CAMERA_DATA_STRU>(type());
	}
	~CPolCamera() { delete m_publiser; }

	virtual const std::string type() { return "POLCAMERA"; }
	virtual bool publish(CAMERA_DATA_STRU& data) { m_publiser->write(data); return true; }

private:
	publisher<CAMERA_DATA_STRU>* m_publiser;
};