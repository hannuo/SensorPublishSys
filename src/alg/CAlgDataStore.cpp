#include <thread>

#include "CAlgDataStore.h"
#include "..//buffer/CQueueFactory.h"
#include "../comm/ConfigParse.h"


void DatastoreThead_proc(CAlgDataStore* pObj)
{
	

	while (!pObj->m_bDatastoreStop)
	{
		if (pObj->m_algIMUSub != NULL)
		{
			if (pObj->m_algIMUSub->read(pObj->IMUdata))
			{
				std::cout << "DataStore: IMU data - " << pObj->IMUdata.x << " - "
					<< pObj->IMUdata.y << " - " << pObj->IMUdata.z << std::endl;
				//store it to alg1 data file
				if (pObj->algDataFile)
				{
					pObj->algDataFile << "DataStore: IMU data - " << pObj->IMUdata.x << " - "
						<< pObj->IMUdata.y << " - " << pObj->IMUdata.z << std::endl;
				}
			}
			else
			{
				std::cout << "DataStore: IMU data is empty , pleas wait for publish data !" << std::endl;
			}

		}
		else
		{
			//std::cout << " Error no m_algIMUSub" << std::endl;
		}

		if (pObj->m_algCPSub != NULL)
		{
			if (pObj->m_algCPSub->read(pObj->CPdata))
			{
				std::cout << "DataStore:CP data - " << pObj->CPdata.x << " - "
					<< pObj->CPdata.y << " - " << pObj->CPdata.z << std::endl;
				//store it to alg1 data file
				if (pObj->algDataFile)
				{
					pObj->algDataFile << "DataStore:CP data - " << pObj->CPdata.x << " - "
						<< pObj->CPdata.y << " - " << pObj->CPdata.z << std::endl;
				}
			}
			else
			{
				std::cout << "DataStore: CP data is empty , pleas wait for publish data !" << std::endl;
			}

		}
		else
		{
			//std::cout << " Error m_algCPSub" << std::endl;
		}

		if (pObj->m_algCAMSub != NULL)
		{
			if (pObj->m_algCAMSub->read(pObj->CAMdata))
			{
				std::cout << "DataStore: CAMERA data - " << pObj->CAMdata.x << " - "
					<< pObj->CAMdata.y << " - " << pObj->CAMdata.z << std::endl;
				//store it to alg1 data file
				if (pObj->algDataFile)
				{
					pObj->algDataFile << "DataStore: CAMERA data - " << pObj->CAMdata.x << " - "
						<< pObj->CAMdata.y << " - " << pObj->CAMdata.z << std::endl;
				}
			}
			else
			{
				std::cout << "DataStore: CAMERA data is empty , pleas wait for publish data !" << std::endl;
			}
		}
		else
		{
			//std::cout << " Error m_algCAMSub" << std::endl;
		}

		if (pObj->m_algPCAMSub != NULL)
		{
			if (pObj->m_algPCAMSub->read(pObj->PCAMdata))
			{
				std::cout << "DataStore: PCAM data - " << pObj->PCAMdata.x << " - "
					<< pObj->PCAMdata.y << " - " << pObj->PCAMdata.z << std::endl;
				//store it to alg1 data file
				if (pObj->algDataFile)
				{
					pObj->algDataFile << "DataStore: PCAM data - " << pObj->PCAMdata.x << " - "
						<< pObj->PCAMdata.y << " - " << pObj->PCAMdata.z << std::endl;
				}
			}
			else
			{
				std::cout << "DataStore: PCAM data is empty , pleas wait for publish data !" << std::endl;
			}

		}
		else
		{
			//std::cout << " Error m_algPCAMSub" << std::endl;
		}

		if (pObj->m_algBARSub != NULL)
		{
			if (pObj->m_algBARSub->read(pObj->BARdata))
			{
				std::cout << "DataStore: BAR data - " << pObj->BARdata.x << " - "
					<< pObj->BARdata.y << " - " << pObj->BARdata.z << std::endl;
				//store it to alg1 data file
				if (pObj->algDataFile)
				{
					pObj->algDataFile << "DataStore: BAR data - " << pObj->BARdata.x << " - "
						<< pObj->BARdata.y << " - " << pObj->BARdata.z << std::endl;
				}
			}
			else
			{
				std::cout << "DataStore: BAR data is empty , pleas wait for publish data !" << std::endl;
			}

		}
		else
		{
			//std::cout << " Error m_algBARSub" << std::endl;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(std::stoi(pObj->m_algCfgData["inteval"])));

		//For a test , delete m_algIMUSub , to verify the destruct of subcirber.
		/*if (pObj->m_algIMUSub != NULL)
		{
			std::cout << "delete m_algIMUSub , to verify the destruct of subcirber." << std::endl;
			delete pObj->m_algIMUSub;
			pObj->m_algIMUSub = NULL;
		}*/
			
	}
}


CAlgDataStore::CAlgDataStore(std::string alg_name, std::string alg_cfgname)
{
	m_algname = alg_name;
	m_algCfgname = alg_cfgname;

	algDataFile.open("dataStoredata.txt");
}

CAlgDataStore::~CAlgDataStore()
{
	if (m_algIMUSub != NULL)
		delete m_algIMUSub; //2.这里直接释放会不会有问题，因为发布者还在维护其set，类比,用智能指针？？
	if (m_algCPSub != NULL)
		delete m_algCPSub;
	if (m_algBARSub != NULL)
		delete m_algBARSub;
	if (m_algCAMSub != NULL)
		delete m_algCAMSub;
	if (m_algPCAMSub != NULL)
		delete m_algPCAMSub;
}


bool CAlgDataStore::init()
{
	//...
	//datastore:
	// - imu: imu_datastore
	// - compass: compass_datastore
	// - gnss: gnss_datastore

	if (!ConfigParse::parse_alg_data(m_algCfgname, m_algCfgData, m_algCfgPubToSub)) 
	{
		std::cout << "Error: fail to get alg_cfgData." << "from file " << m_algCfgname << std::endl;
		return false;
	}
		
	std::map<std::string, std::string>::iterator iter;
	for (iter = m_algCfgPubToSub.begin(); iter != m_algCfgPubToSub.end(); iter++)
	{
		if (iter->first.compare("IMU") == 0)
		{
			m_algIMUSub = CQueueFactory::create_subscriber<IMU_DATA_STRU>(iter->first, iter->second, std::stoi(m_algCfgData["que_size"]));
			if (m_algIMUSub != NULL)
				std::cout << "Sucessfully to create:" << iter->first << " " << iter->second << " subcriber " << std::endl;
			else
				std::cout << "Not configure to create: " << iter->first << " " << iter->second << " subcriber " << std::endl;
		}

		if (iter->first.compare("COMPASS") == 0)
		{
			m_algCPSub = CQueueFactory::create_subscriber<COMPASS_DATA_STRU>(iter->first, iter->second, std::stoi(m_algCfgData["que_size"]));
			if (m_algCPSub != NULL)
				std::cout << "Sucessfully to create:" << iter->first << " " << iter->second << " subcriber " << std::endl;
			else
				std::cout << "Not configure  to create: " << iter->first << " " << iter->second << " subcriber " << std::endl;
		}

		if (iter->first.compare("BAROMETRIC") == 0)
		{
			m_algBARSub = CQueueFactory::create_subscriber<BAROMETRIC_DATA_STRU>(iter->first, iter->second, std::stoi(m_algCfgData["que_size"]));
			if (m_algBARSub != NULL)
				std::cout << "Sucessfully to create:" << iter->first << " " << iter->second << " subcriber " << std::endl;
			else
				std::cout << "Not configure to create: " << iter->first << " " << iter->second << " subcriber " << std::endl;
		}
		if (iter->first.compare("POLCAMERA") == 0)
		{
			m_algPCAMSub = CQueueFactory::create_subscriber<CAMERA_DATA_STRU>(iter->first, iter->second, std::stoi(m_algCfgData["que_size"]));
			if (m_algPCAMSub != NULL)
				std::cout << "Sucessfully to create:" << iter->first << " " << iter->second << " subcriber " << std::endl;
			else
				std::cout << "Not configure to create: " << iter->first << " " << iter->second << " subcriber " << std::endl;
		}
		if (iter->first.compare("CAMERA") == 0)
		{
			m_algCAMSub = CQueueFactory::create_subscriber<CAMERA_DATA_STRU>(iter->first, iter->second, std::stoi(m_algCfgData["que_size"]));
			if (m_algCAMSub != NULL)
				std::cout << "Sucessfully to create:" << iter->first << " " << iter->second << " subcriber " << std::endl;
			else
				std::cout << "Not configure to create: " << iter->first << " " << iter->second << " subcriber " << std::endl;
		}
		
		
	}
		
	return true;
}

bool CAlgDataStore::start()
{
	m_datastoreThread = std::thread(DatastoreThead_proc, this);
	
	return true;
}

bool CAlgDataStore::stop()
{
	m_bDatastoreStop = true;
	m_datastoreThread.join();

	return true;
}
std::string CAlgDataStore::GetAlgName()
{
	return m_algname;
}


