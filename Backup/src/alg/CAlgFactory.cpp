#include "CAlgFactory.h"
#include "CAlg1.h"

#include <map>
#include <mutex>
#include <vector>
#include "CAlg1.h"

static std::map<std::string, CAlg_base*> g_map_algObj;
static std::mutex g_mutex_alg;




CAlg_base* CAlgFactory::create(std::string alg_name, std::string alg_cfgname)
{
	//vector<CAlg_base*> 
	//vector<string> alg_types;
	//ConfigParse::Parse(alg_cfgname,alg_types)
	if (alg_name.compare("alg1"))
	{

		CAlg1* cAlg1 = new CAlg1(alg_name, alg_cfgname);
		if (cAlg1->init())
		{
			std::unique_lock<std::mutex> lock(g_mutex_alg);
			add(cAlg1);
		}
		else
		{
			;
			//Log(...)
		}

		return cAlg1;
	}
	return NULL;
	
}

void CAlgFactory::add(CAlg_base* obj)
{
	std::unique_lock<std::mutex> lock(g_mutex_alg);
	g_map_algObj[obj->GetName()] = obj;
}

CAlg_base* CAlgFactory::get(std::string strAlgName)
{
	std::unique_lock<std::mutex> lock(g_mutex_alg);
	return g_map_algObj[strAlgName];
}
