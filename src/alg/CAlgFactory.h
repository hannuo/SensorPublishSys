#pragma once
#ifndef CALGFACOTRY_H
#define CALGFACTORY_H

#include "CAlg_base.h"

class CAlgFactory
{
private:
	CAlgFactory()	{}
public:
	~CAlgFactory()	{}

public:
	static bool create_algs(std::string alg_name);

	static CAlg_base* get(std::string strAlgName);

	static void start_algs();

	static void stop_algs();

	//static void remove(std::string strAlgName);
private:

	static bool create(std::string alg_name, std::string alg_cfgname);

	static void add(CAlg_base* obj);

};
#endif
