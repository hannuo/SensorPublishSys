#include <fstream>
#include <sstream>
#include "ConfigParse.h"
#include "yaml-cpp/yaml.h"

static std::map<std::string,std::string> g_globa_cfgData;

bool ConfigParse::parse_global_cfg(std::string cfg_file)
{
	return parse_cfg_mapstring(cfg_file, g_globa_cfgData);
}

std::string ConfigParse::get_glocfg_byname(std::string& glocfgName)
{
	return g_globa_cfgData[glocfgName];
}

bool ConfigParse::parse_cfg_mapstring(std::string globalCfg_file, std::map<std::string, std::string>& globalCfgData)
{
	
	bool bRet = false;

	
	std::ifstream fin(globalCfg_file.c_str());
	if (fin.fail())
	{
		std::cout << "Error to open cfg file:" << globalCfg_file.c_str() << std::endl;
		return bRet;
	}

	try 
	{
		YAML::Node config = YAML::LoadFile(globalCfg_file);

		if (!config.IsNull() && config.IsMap())
		{
			bRet = true;


			YAML::iterator it;
			for (it = config.begin(); it != config.end(); it++)
			{

				globalCfgData.insert(std::pair<std::string, std::string>(it->first.as<std::string>(), it->second.as<std::string>()));

			}
		}
		else
		{
			std::cout << "Error: yaml file contains no member" << std::endl;
		}

	}
	catch (YAML::Exception e)
	{
		std::cout << e.msg << std::endl;
		fin.close();
		return false;
	}
	
	return bRet;
}


bool ConfigParse::parse_alg_data(std::string algData_File, std::map<std::string, std::string>& alg_Data,
	std::map<std::string, std::string>& algPubToSub)
{
	bool bRet = false;
	
	std::ifstream fin(algData_File.c_str());
	if (fin.fail())
	{
		std::cout << "Error to open cfg file." << algData_File << std::endl;
		return bRet;
	}

	try
	{
		YAML::Node config = YAML::LoadFile(algData_File);

		if (config.IsMap())
		{
			bRet = true;

			YAML::iterator it = config.begin();
			while (it != config.end())
			{
				YAML::Node key = it->first;
				YAML::Node child = it->second;
				//std::cout << "1nd key:" << key.as<std::string>() << std::endl;
				if (child.IsMap())
				{
					//std::cout << "1nd value is map object, size:" << child.size() << std::endl;
					for (auto it = child.begin(); it != child.end(); ++it)
					{
						YAML::Node childKey = it->first;
						YAML::Node childValue = it->second;

						if (childValue.IsMap())
						{
							//std::cout << " 2nd value is map object, size:" << childValue.size() << std::endl;
							std::cout << "Sorry, wo do not suport 3 level scalar" << std::endl;
							for (auto it = childValue.begin(); it != childValue.end(); ++it)
							{
								;
							}
						}
						else
						{
							algPubToSub.insert(std::pair<std::string, std::string>(childKey.as<std::string>(),
								childValue.as<std::string>()));
						}
					}
				}
				else
				{
					alg_Data.insert(std::pair<std::string, std::string>(key.as<std::string>(),
						child.as<std::string>()));
				}

				it++;
			}

		}
		else
		{
			std::cout << "Error: yaml file contains no member" << std::endl;
		}
	}
	catch (YAML::Exception e)
	{
		std::cout << e.msg << std::endl;
		fin.close();
		return false;
	}
	
	return bRet;
}

