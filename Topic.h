#pragma once
#include <string>
#include "sUtilities.h"



//Class which represents messages
class Topic
{

public:
	Topic(int sensorId, float measurement, SensorType sensorType) : _sensorId(sensorId),_measurement(measurement), _sensorType(sensorType) {
		std::string sign{};
		switch (_sensorType) {
			case SensorType::TEMP: {
				sign = "\370C";
				break;
			}
			case SensorType::HUM: {
				sign = "%";
				break;
			}
			case SensorType::PRESS: {
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
	SensorType getSensorType() {
		return _sensorType;
	}
	
private:
	int _sensorId{ 0 };
	SensorType _sensorType;
	float _measurement{ 0.0 };
	std::string _message{};
};

