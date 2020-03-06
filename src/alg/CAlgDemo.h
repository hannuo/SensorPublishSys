#pragma once
#ifndef CALG_DEMO_CLASS_H
#define CALG_DEMO_CLASS_H

#include <vector>
#include <fstream>

#include "CAlg_base.h"
#include "../comm/ConfigParse.h"
#include "../comm/ComonStruct.h"

class CAlgDemo : public CAlg_base
{
public:
	CAlgDemo(std::string alg_name, std::string alg_cfgname);
	~CAlgDemo();

	bool init();

	bool start();

	bool start_publish();

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
	std::thread m_algpub;
	std::map<std::string, std::string> m_algCfgData;
	std::map<std::string, std::string> m_algCfgPubToSub;

	publisher<IMU_DATA_STRU>* m_publiser;

	friend void AlgDemoThread_proc(CAlgDemo *pObj);

	friend void AlgDemoThread_pub(CAlgDemo *pObj);
};

void AlgDemoThread_proc(CAlgDemo *pObj);
friend void AlgDemoThread_pub(CAlgDemo *pObj);
#endif

