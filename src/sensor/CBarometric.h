#pragma once
#include "CSensor.h"
#include "../buffer/CQueueFactory.h"
#include "../comm/ComonStruct.h"


class CBarometric :public CSensor
{
public:
	CBarometric() 
	{
		m_publiser = CQueueFactory::create_publiser<BAROMETRIC_DATA_STRU>(type());
	}
	~CBarometric() { delete m_publiser; }

	virtual const std::string type() { return "BAROMETRIC"; }
	virtual bool publish(BAROMETRIC_DATA_STRU& data) { m_publiser->write(data); return true; }

private:
	publisher<BAROMETRIC_DATA_STRU>* m_publiser;
};