#include <map>
#include <mutex>
#include <vector>
#include <thread>

#include "CAlgFactory.h"
#include "CAlg1.h"
#include "CAlgDataStore.h"

static std::map<std::string, CAlg_base*> g_map_algObj;
//std::map<std::string, std::thread> g_algThreads_map;
static std::mutex g_mutex_alg;


//void algThead_proc(CAlg_base *pObj)
//{
//	
//	while (true)
//	{
//		pObj->start();
//		std::this_thread::sleep_for(std::chrono::milliseconds(4000));
//	}
//}

void CAlgFactory::start_algs()
{
	for (auto it : g_map_algObj)
	{
		it.second->start();
		//g_algThreads_map[it.first] = std::thread(algThead_proc, it.second);	
	}
}
void CAlgFactory::stop_algs()
{
	for (auto it : g_map_algObj)
	{
		it.second->stop();
		//g_algThreads_map[it.first].join();
	}
}

bool CAlgFactory::create_algs(std::string alg_name)
{
	std::map<std::string, std::string> algCfgMap;

	if (!ConfigParse::parse_cfg_mapstring(alg_name, algCfgMap))
	{
		std::cout << "Error:" << "do not get the spec data." << std::endl;
		return false;
	}
	else
	{
		std::map<std::string, std::string>::iterator iter;

		for (iter = algCfgMap.begin(); iter != algCfgMap.end(); iter++)
		{
			if (!create(iter->first, iter->second))
				return false;
		}
	}

	return true;
}

bool CAlgFactory::create(std::string alg_name, std::string alg_cfgname)
{
	bool bRet = false;

	if (alg_name.compare("alg1") == 0)
	{
		CAlg1* cAlg1 = new CAlg1(alg_name, alg_cfgname);

		if (cAlg1->init())
		{
			add(cAlg1);
			bRet = true;
		}
		else
		{
			std::cout << "Error: fail to init the CAlg Object." << std::endl;
			//delete cAlg1;
		}
	}
	else if (alg_name.compare("datastore") == 0)
	{
		CAlgDataStore* cAlgDataStore = new CAlgDataStore(alg_name, alg_cfgname);

		if (cAlgDataStore->init())
		{
			add(cAlgDataStore);
			bRet = true;
		}
		else
		{
			std::cout << "Error: fail to init the CAlg Object." << std::endl;
			//delete cAlgDataStore;
		}
	}
	else
	{
		std::cout << "Not implement other CAlg class ," << std::endl;
		std::cout << "Or wrong alg cfg data file path : " << alg_cfgname << std::endl;
	}
	

	return bRet;
	
}

void CAlgFactory::add(CAlg_base* obj)
{
	std::unique_lock<std::mutex> lock(g_mutex_alg);
	g_map_algObj[obj->GetAlgName()] = obj;
}

CAlg_base* CAlgFactory::get(std::string strAlgName)
{
	std::unique_lock<std::mutex> lock(g_mutex_alg);
	return g_map_algObj[strAlgName];
}

