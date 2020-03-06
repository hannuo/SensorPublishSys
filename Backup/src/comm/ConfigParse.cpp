#include <fstream>
#include <sstream>
#include "ConfigParse.h"
#include "yaml-cpp/yaml.h"

const std::string datastore = "datastore";
const std::string alg1 = "alg1";
const std::string alg2 = "alg2";

const std::string name = "name";
const std::string data = "data";
const std::string que_size = "que_size";
const std::string inteval = "inteval";

bool ConfigParse::parse_alg_cfg(std::string cfg_file, std::map<std::string, std::string>& param_tab)
{
	std::ifstream fin(cfg_file.c_str());
	if (fin.fail())
	{
		std::cout << "Error to open cfg file." << std::endl;
		return false;
	}

	YAML::Node config = YAML::LoadFile(cfg_file);

	std::string temp;

	temp = config[datastore].as<std::string>();
	param_tab.insert(std::pair<std::string, std::string>(datastore, temp));
	//std::cout << "datastore:" << temp << std::endl;

	temp = config[alg1].as<std::string>();
	param_tab.insert(std::pair<std::string, std::string>(alg1, temp));
	//std::cout << "alg1:" << temp << std::endl;

	std::map<std::string, std::string>::iterator iter;

	for (iter = param_tab.begin(); iter != param_tab.end(); iter++)
	{
		std::cout << iter->first << iter->second << std::endl;
	}

	return true;
}

bool ConfigParse::parse_alg_data(std::string algDataFile, Alg1Cfg& alg1CfgData)
{
	std::ifstream fin(algDataFile.c_str());
	if (fin.fail())
	{
		std::cout << "Error to open cfg file." << std::endl;
		return false;
	}

	YAML::Node config = YAML::LoadFile(algDataFile);

	std::string temp;
	unsigned int value;

	temp = config[name].as<std::string>();
	alg1CfgData.strAlgName = temp;
	std::cout << "datastore:" << temp << std::endl;

	temp = config[data].as<std::string>();
		//std::cout << "alg1:" << temp << std::endl;
	std::string temp2;
	std::stringstream ss(temp);
	while (ss >> temp2)
	{
		std::cout << temp2 << std::endl;
		alg1CfgData.dataVector.push_back(temp2);
	}

	value = config[que_size].as<unsigned int>();
	alg1CfgData.que_size = value;
	std::cout << "que_size:" << value << std::endl;

	value = config[inteval].as<unsigned int>();
	alg1CfgData.intevel = value;
	std::cout << "inteval:" << value << std::endl;

	std::vector<std::string>::iterator iter;
	for (iter = alg1CfgData.dataVector.begin(); iter != alg1CfgData.dataVector.end(); iter++)
	{
		std::cout << *iter << std::endl;
	}

	return true;
}