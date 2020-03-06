#include <thread>

#include "CAlg1.h"
#include "..//buffer/CQueueFactory.h"
#include "../comm/ConfigParse.h"


void Alg1Thead_proc(CAlg1* pObj)
{
	while(!pObj->m_bAlgStop)
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

CAlg1::CAlg1(std::string alg_name, std::string alg_cfgname)
{
	m_algname = alg_name;
	m_algCfgname = alg_cfgname;

	algDataFile.open("alg1data.txt");
}

CAlg1::~CAlg1()
{
	if(m_algSub != NULL)
		delete m_algSub; //2.这里直接释放会不会有问题，因为发布者还在维护其set，类比,用智能指针？？
	if (algDataFile)
		algDataFile.close();
}


bool CAlg1::init()
{
	if (!ConfigParse::parse_alg_data(m_algCfgname, m_algCfgData, m_algCfgPubToSub))
	{
		std::cout << "Error: fail to get alg_cfgData." << "from file " << m_algCfgname << std::endl;
		return false;
	}
	m_algSub = CQueueFactory::create_subscriber<IMU_DATA_STRU>("IMU", m_algname,std::stoi(m_algCfgData["que_size"]));
	if (m_algSub != NULL)
		return true;
	else
		return false;
}

bool CAlg1::start()
{
	m_algthread = std::thread(Alg1Thead_proc, this);

	return true;
}

bool CAlg1::stop()
{
	m_bAlgStop = true;
	m_algthread.join();
	
	return true;
}

std::string CAlg1::GetAlgName()
{
	return m_algname;
}
