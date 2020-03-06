#include <iostream> 
#include "../sensor/CImuDemo.h"

#include "../alg/CAlgFactory.h"
#include "../comm/ConfigParse.h"
using namespace std;

void my_pause()
{
#if !defined(_MSC_VER)
	pause();
#else
	system("PAUSE");
#endif
}
int main(int argc, char ** argv)
{
	std::string cfg_file_path;
	if (argc < 2)
	{
		cout <<endl<< "please input config file's full path!" << endl<<endl;
		my_pause();
		//return 0;
	}
	//std::string cfg_file_path	= argv[1];
	std::string globle_cfg		= cfg_file_path + "/globle_cfg.yaml";
	std::string sensors_cfg		= cfg_file_path + "/sensors_cfg.yaml";
	std::string alg_cfg			= cfg_file_path + "/alg_cfg.yaml";
	CImu* pImuObj = new CImuDemo();
	PARAM_TAB globel_param;
	PARAM_TAB sensor_param;
	sensor_param["interval"] = "5";
	pImuObj->init(globel_param, sensor_param);
	//TODO: start sensor
	
	//TODO: start alg
	std::map<std::string,std::string> m_alg_cfg_loc;
	std::map<std::string,std::string>::iterator mapIter;
	
	if (ConfigParse::parse_alg_cfg(alg_cfg, m_alg_cfg_loc))
	{
		for (mapIter = m_alg_cfg_loc.begin(); mapIter != m_alg_cfg_loc.end(); ++mapIter)
		{
			CAlgFactory::create(mapIter->first, mapIter->second);
		}
	}
	
	

	my_pause();
	return 0;
}
