#pragma once
#include "CSensor.h"
const std::string IMU		= "IMU";
const std::string COMPASS	= "COMPASS";
const std::string GNSS		= "GNSS";
const std::string BAROMETRIC= "BAROMETRIC";
const std::string CAMERA	= "CAMERA";
const std::string POLCAMERA = "POLCAMERA";
const std::string GROUP		= "GROUP";
class CSensorFactory
{
	static void create(std::string cfg_file);

private:
	static CSensor* create(std::string type, std::string sub_typ = "default");

};