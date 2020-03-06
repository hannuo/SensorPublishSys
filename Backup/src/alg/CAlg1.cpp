#include "CAlg1.h"
#include "..//buffer/CQueueFactory.h"

CAlg1::CAlg1(std::string alg_name, std::string alg_cfgname)
{
	m_algname = alg_name;
	m_algCfgname = alg_cfgname;

	if (!ConfigParse::parse_alg_data(alg_cfgname, m_algCfgData))
		;
		//Log(...)
}

CAlg1::~CAlg1()
{
	delete m_algSub; //2.����ֱ���ͷŻ᲻�������⣬��Ϊ�����߻���ά����set�����
}

//1.alg_cfg�����˼����㷨��CAlgFactory::create�ͱ����ü���
//һ���㷨�У��ж�������߸���ô�죬��Ϊ����������δ֪���޷�ͨ��ָ������ά��
//���㷨���������ļ� datastore��data�ж����imu compass gnsss
//д����ÿ���㷨�������������Щ�����ߣ�ָ����T����ָ����name����data���Ƿ����� ���֣���������Ϊ������
//���Tȷ���ˣ��Ϳ���ͨ��ָ������ά����
bool CAlg1::init()
{
	m_algSub = CQueueFactory::create_subscriber<INS_DATA_ALG1>("imu", m_algname, m_algCfgData.que_size);
	if (m_algSub != NULL)
		return true;
	else
		return false;
}

bool CAlg1::start()
{
	return true;
}

subscriber<INS_DATA_ALG1>* CAlg1::GetSubScriber()
{
	return m_algSub;
}

std::string CAlg1::GetName()
{
	return m_algname;
}