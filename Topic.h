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
		std::string sign;
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
			time_t my_time = time(NULL);
		
		_message = "Sensor[" + std::to_string(_sensorId) + "] measured: " + std::to_string(_measurement) + sign + " Time: " + ctime(&my_time);

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

private:
	time_t _time{};
	int _sensorId{ 0 };
	int _sensorType{ 0 };
	float _measurement{ 0.0 };
	std::string _message{};
};

