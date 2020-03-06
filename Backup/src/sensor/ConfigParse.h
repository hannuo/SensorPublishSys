#pragma once
#include <iostream>
#include <vector>
#include <map>

struct Alg1Cfg
{
	std::string strAlgName;
	std::vector<std::string> dataVector;
	unsigned int que_size;
	unsigned int intevel;
};
class ConfigParse
{
private:
	ConfigParse() {};
public:
	~ConfigParse() {};

	static bool parse_alg_cfg(std::string cfg_file, std::map<std::string, std::string>& param_tab);
	static bool parse_alg_data(std::string algDataFile, Alg1Cfg& alg1CfgData);
};