#pragma once
#include "CSensor.h"
#include "../buffer/CQueueFactory.h"
#include "../comm/ComonStruct.h"

class CGnss :public CSensor
{
public:
	CGnss() 
	{
		m_publiser = CQueueFactory::create_publiser<GNSS_DATA_STRU>(type());
	}
	~CGnss() { delete m_publiser; }

	virtual const std::string type() { return "GNSS"; }
	virtual bool publish(GNSS_DATA_STRU& data) { m_publiser->write(data); return true; }

private:
	publisher<GNSS_DATA_STRU>* m_publiser;
};