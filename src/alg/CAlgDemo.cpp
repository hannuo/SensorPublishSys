#include <thread>

#include "CAlgDemo.h"
#include "..//buffer/CQueueFactory.h"
#include "../comm/ConfigParse.h"


void AlgDemoThread_proc(CAlgDemo* pObj)
{
	while (!pObj->m_bAlgStop)
	{
		if (pObj->m_algSub != NULL)
		{
			if (pObj->m_algSub->read(pObj->IMUdata))
			{
				std::cout << "CALG1: IMU data - " << pObj->IMUdata.x << " - "
					<< pObj->IMUdata.y << " - " << pObj->IMUdata.z << std::endl;
				if (pObj->algDataFile)
				{
					pObj->algDataFile << "CALG1: IMU data - " << pObj->IMUdata.x << " - "
						<< pObj->IMUdata.y << " - " << pObj->IMUdata.z << std::endl;
				}
			}
			else
			{
				std::cout << "CALG1: IMU data is empty , pleas wait for publish data ! " << std::endl;
			}

			//store it to alg1 data file
		}
		else
		{
			std::cout << " Error m_algSub" << std::endl;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(std::stoi(pObj->m_algCfgData["inteval"])));
	}
}

void AlgDemoThread_pub(CAlgDemo* pObj)
{
	while (!pObj->m_bAlgStop)
	{
		if (pObj->m_publiser != NULL)
		{
			IMU_DATA_STRU ins = { 2.0, 2.0, 2.0 };

			m_publiser->write(data);
	
		}
		else
		{
			std::cout << " Error m_publiser" << std::endl;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(std::stoi(pObj->m_algCfgData["inteval"])));
	}
}

CAlgDemo::CAlgDemo(std::string alg_name, std::string alg_cfgname)
{
	m_algname = alg_name;
	m_algCfgname = alg_cfgname;

	algDataFile.open("alg1data.txt");
}

CAlgDemo::~CAlgDemo()
{
	if (m_algSub != NULL)
		delete m_algSub; 
	if (m_publiser != NULL)
		delete m_publiser;
	if (algDataFile)
		algDataFile.close();
}


bool CAlgDemo::init()
{
	m_publiser = CQueueFactory::create_publiser<IMU_DATA_STRU>("IMU");

	if (!ConfigParse::parse_alg_data(m_algCfgname, m_algCfgData, m_algCfgPubToSub))
	{
		std::cout << "Error: fail to get alg_cfgData." << "from file " << m_algCfgname << std::endl;
		return false;
	}
	m_algSub = CQueueFactory::create_subscriber<IMU_DATA_STRU>("IMU", m_algname, std::stoi(m_algCfgData["que_size"]));
	if (m_algSub != NULL)
		return true;
	else
		return false;
}

bool CAlgDemo::start()
{
	m_algthread = std::thread(AlgDemoThread_proc, this);

	return true;
}


bool CAlgDemo::start_publish()
{
	m_algpub = std::thread(AlgDemoThread_pub, this);

	return true;
}

bool CAlgDemo::stop()
{
	m_bAlgStop = true;
	m_algthread.join();
	m_algpub.join();

	return true;
}

std::string CAlgDemo::GetAlgName()
{
	return m_algname;
}
