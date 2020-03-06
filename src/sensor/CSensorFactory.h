#pragma once
#include "CSensor.h"

class CSensorFactory
{
public:
	static void start_sensors();
	static void stop_sensors();
	static bool create_sensors(std::string cfg_file);	
	static CSensor* create(std::string type);
};