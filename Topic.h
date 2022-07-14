#pragma once
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <time.h>


//Class which represents messages
class Topic
{

public:
	Topic(int sensorId, float measurement, int sensorType) : _sensorId(sensorId),_measurement(measurement), _sensorType(sensorType) {
		std::string sign{};
		switch (_sensorType) {
			case 0: {
				sign = "\370C";
				break;
			}
			case 1: {
				sign = "%";
				break;
			}
			case 2: {
				sign = "Pa";
				break;
			}
		}
			
		_message = "Sensor[" + std::to_string(_sensorId) + "] measured: " + std::to_string(_measurement) + sign + " Time: " + getCurrentUTC();

	}
	std::string getMessage() {
		return _message;
	}
	int getSensorId() {
		return _sensorId;
	}
	float getRawMeasurement() {
		return _measurement;
	}
	int getSensorType() {
		return _sensorType;
	}
	static std::string getCurrentUTC() {
		struct tm newtime;
		std::string am_pm = "AM";
		__time64_t long_time;
		char timebuf[26];
		errno_t err;

		// Get time as 64-bit integer.
		_time64(&long_time);
		// Convert to local time.
		err = _localtime64_s(&newtime, &long_time);
		if (err)
		{
			printf("Invalid argument to _localtime64_s.");
			exit(1);
		}

		std::ostringstream oss;
		oss << std::put_time(&newtime, "%d-%m-%Y %H:%M:%S");
		 
		return oss.str();
	}
private:
	int _sensorId{ 0 };
	int _sensorType{ 0 };
	float _measurement{ 0.0 };
	std::string _message{};
};

