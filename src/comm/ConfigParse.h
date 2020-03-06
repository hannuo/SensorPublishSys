#pragma once
#ifndef CONFIGPARSE_H
#define CONFIGPARSE_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

struct Alg1Cfg
{
	std::string strAlgName;
	std::string dataVector;
	std::string que_size;
	std::string intevel;
};
const std::string gGlobalCfg = "../Global_Cfg.yaml";

class ConfigParse
{
private:
	ConfigParse() {};
public:
	~ConfigParse() {};

	static bool parse_global_cfg(std::string cfg_file);
	static std::string get_glocfg_byname(std::string& glocfgName);
	static bool parse_cfg_mapstring(std::string cfg_file, std::map<std::string, std::string>& cfg_data);
	static bool parse_alg_data(std::string algData_File, std::map<std::string, std::string>& alg_Data,
		std::map<std::string, std::string>& algPubToSub);
};

#endif