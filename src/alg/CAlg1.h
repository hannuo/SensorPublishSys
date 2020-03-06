#pragma once
#ifndef CALG1_CLASS_H
#define CALG1_CLASS_H

#include <vector>
#include <fstream>

#include "CAlg_base.h"
#include "../comm/ConfigParse.h"
#include "../comm/ComonStruct.h"

class CAlg1 : public CAlg_base
{
public:
	CAlg1(std::string alg_name, std::string alg_cfgname);
	~CAlg1();

	bool init();

	bool start();

	bool stop();

	std::string GetAlgName();

public:
	

private:
	IMU_DATA_STRU  IMUdata = { 0.0, 0.0, 0.0 };
	bool m_bAlgStop = false;
	subscriber<IMU_DATA_STRU>* m_algSub;
	std::ofstream algDataFile;

	std::string m_algname;
	std::string m_algCfgname;
	std::thread m_algthread;
	std::map<std::string,std::string> m_algCfgData;
	std::map<std::string, std::string> m_algCfgPubToSub;

	friend void Alg1Thead_proc(CAlg1* pObj);
};

void Alg1Thead_proc(CAlg1* pObj);
#endif
