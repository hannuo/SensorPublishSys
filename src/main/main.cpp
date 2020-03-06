#include <iostream> 
#include <thread>
#include "../sensor/CSensorFactory.h"
#include "../sensor/CImuDemo.h"

#include "../alg/CAlgFactory.h"
#include "../comm/ConfigParse.h"
#if !defined(_MSC_VER)
#include <unistd.h>
#endif
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
	if (argc < 2)
	{
		cout <<endl<< "please input config file's full path!" << endl<<endl;
		my_pause();
		return 0;
	}
	std::string cfg_file_path	= argv[1];
	std::string globle_cfg		= cfg_file_path + "/globle_cfg.yaml";
	std::string sensors_cfg		= cfg_file_path + "/sensors_cfg.yaml";
	std::string alg_cfg			= cfg_file_path + "/alg_cfg.yaml";
	//TODO: load globel param
	if (!ConfigParse::parse_global_cfg(globle_cfg))
	{
		cout << "Sorry, you input path can not be found or wrong format.please check globle_cfg_file!" << endl;
		my_pause();
		return 1;
	}

	//TODO: start sensor
	if (!CSensorFactory::create_sensors(sensors_cfg))
	{
		cout << "Sorry, you input puth can not be found or wrong format. please check sensors_cfg_file!" << endl;
		my_pause();
		return 1;
	}
	CSensorFactory::start_sensors();

	//TODO: start alg
	if (!CAlgFactory::create_algs(alg_cfg))
	{
		cout << "create_algs fail, please check your alg_cfg_file!" << endl;
		CSensorFactory::stop_sensors();
		my_pause();
		return 1;
	}
	CAlgFactory::start_algs();	

	

	while (1)
	{
		std::cout << "begin main circulation !" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	}

	CSensorFactory::stop_sensors();
	return 0;
}
