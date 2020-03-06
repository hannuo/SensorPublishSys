#pragma once
#include "CSensor.h"
#include "../buffer/CQueueFactory.h"
#include "../comm/ComonStruct.h"

class CCompass :public CSensor
{
public:
	CCompass() 
	{
		m_publiser = CQueueFactory::create_publiser<COMPASS_DATA_STRU>(type());
	}
	~CCompass() { delete m_publiser; }

	virtual const std::string type() { return "COMPASS"; }
	virtual bool publish(COMPASS_DATA_STRU& data) { m_publiser->write(data); return true; }

private:
	publisher<COMPASS_DATA_STRU>* m_publiser;
};