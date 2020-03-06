#pragma once
#include "CAlg_base.h"

class CAlgFactory
{
private:
	CAlgFactory()	{}
public:
	~CAlgFactory()	{}

public:
	static CAlg_base* create(std::string alg_name, std::string alg_cfgname);

	static void add(CAlg_base* obj);

	static CAlg_base* get(std::string strAlgName);

	//static void remove(std::string strAlgName);

};
