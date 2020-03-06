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
	delete m_algSub; //2.这里直接释放会不会有问题，因为发布者还在维护其set，类比
}

//1.alg_cfg配置了几个算法，CAlgFactory::create就被调用几次
//一个算法中，有多个订阅者该怎么办，因为订阅者类型未知，无法通过指针数组维护
//如算法数据配置文件 datastore，data有多个，imu compass gnsss
//写死，每个算法对象包含具体哪些订阅者（指定好T）（指定好name）（data里是发布者 名字，在这里作为参数）
//如果T确定了，就可以通过指针数组维护了
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