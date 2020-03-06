#pragma once
#ifndef COMMON_DATASTRUCT
#define COMMON_DATASTRUCT
const std::string IMU = "IMU";
const std::string COMPASS = "COMPASS";
const std::string GNSS = "GNSS";
const std::string BAROMETRIC = "BAROMETRIC";
const std::string CAMERA = "CAMERA";
const std::string POLCAMERA = "POLCAMERA";
const std::string GROUP = "GROUP";

struct BAROMETRIC_DATA_STRU
{
	double x;
	double y;
	double z;
};

struct CAMERA_DATA_STRU
{
	double x;
	double y;
	double z;
};

struct COMPASS_DATA_STRU
{
	double x;
	double y;
	double z;
};
struct GNSS_DATA_STRU
{
	double x;
	double y;
	double z;
};
struct IMU_DATA_STRU
{
	double x;
	double y;
	double z;
};







#endif // !COMMON_DATASTRUCT
