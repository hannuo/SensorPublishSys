#pragma once
#include "CAlg_base.h"
#include "../buffer/subscriber.hpp"
#include "../comm/ConfigParse.h"

#include <vector>

struct INS_DATA_ALG1
{
	double x;
	double y;
	double z;
};


class CAlg1 : public CAlg_base
{
public:
	CAlg1(std::string alg_name, std::string alg_cfgname);
	~CAlg1();

	bool init();

	bool start();

	subscriber<INS_DATA_ALG1>* GetSubScriber();

	std::string GetName();

private:
	std::string m_algname;
	std::string m_algCfgname;
	subscriber<INS_DATA_ALG1>* m_algSub;
	Alg1Cfg m_algCfgData;

};
