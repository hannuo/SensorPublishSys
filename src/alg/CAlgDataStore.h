#pragma once
#pragma once
#ifndef CALGDATASTORE_CALSS_H
#define CALGDATASTORE_CLASS_H

#include <vector>
#include <fstream>

#include "CAlg_base.h"
#include "../comm/ConfigParse.h"
#include "../comm/ComonStruct.h"

class CAlgDataStore : public CAlg_base
{
public:
	CAlgDataStore(std::string alg_name, std::string alg_cfgname);
	~CAlgDataStore();

	bool init();

	bool start();

	bool stop();

	std::string GetAlgName();

	//void subscriberIMUData(IMU_DATA_STRU& data);

private:
	std::string m_algname;
	std::string m_algCfgname;
	std::thread m_datastoreThread;

	std::ofstream algDataFile;

	bool m_bDatastoreStop = false;

	IMU_DATA_STRU  IMUdata = { 0.0, 0.0, 0.0 };
	COMPASS_DATA_STRU  CPdata = { 0.0, 0.0, 0.0 };
	BAROMETRIC_DATA_STRU  BARdata = { 0.0, 0.0, 0.0 };
	CAMERA_DATA_STRU  PCAMdata = { 0.0, 0.0, 0.0 };
	CAMERA_DATA_STRU  CAMdata = { 0.0, 0.0, 0.0 };

	subscriber<IMU_DATA_STRU>* m_algIMUSub = NULL;
	subscriber<COMPASS_DATA_STRU>* m_algCPSub = NULL;
	subscriber<BAROMETRIC_DATA_STRU>* m_algBARSub = NULL;
	subscriber<CAMERA_DATA_STRU>* m_algPCAMSub = NULL;
	subscriber<CAMERA_DATA_STRU>* m_algCAMSub = NULL;

	//std::map<std::string, subscriber<INS_DATA_STRU>*> m_algSubCollect;
	std::map<std::string, std::string> m_algCfgData;
	std::map<std::string, std::string> m_algCfgPubToSub;

friend void DatastoreThead_proc(CAlgDataStore* pObj);
};

void DatastoreThead_proc(CAlgDataStore* pObj);

#endif
