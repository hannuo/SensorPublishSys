#pragma once
#include <iostream>
#include <map>
typedef std::map<std::string, std::string> PARAM_TAB;
class CSensor
{	
public:
	CSensor()	{}
	virtual ~CSensor()	{}
	virtual bool init(PARAM_TAB globle_param, PARAM_TAB sensor_param) = 0;
	virtual bool start() = 0;
	virtual const std::string  type() = 0;
	//virtual const std::string  sub_type() = 0;
	uint32_t interval() { return m_interval; }
	void interval(uint32_t interval) {	m_interval = interval;}
private:
	uint32_t m_interval; //µ•Œª£∫∫¡√Î
	//std::string m_type;
	//std::string m_sub_type;
};