#pragma once
#include "Node.h"
#include "TemperatureSensor.h"
#include "PressureSensor.h"
#include "HummiditySensor.h"
#include <iostream>
#include "CircularBuffer.h"
#include <unordered_map>
#include <memory>
#include "Client.h"

//Main class, system representation, covering subscribing, notifying, adding sensors etc.
class System
{
public:
	
	System(size_t buffer_size) {
		_mainNode = std::make_shared<Node>(buffer_size);
	}	
	~System() { 
		if (_worker.joinable()) {
			_worker.join();
		}
		std::cout << "System finished job" << std::endl;
	}
	void addSensor(Sensor::SensorType sensorType) {
		int newId = _sensors.size();
		while (_sensors.find(newId) != _sensors.end()){
			newId++;
		}
		switch (sensorType) {
			case Sensor::SensorType::TEMP: {
				_sensors[newId]= std::make_unique<TemperatureSensor>(newId, _mainNode);
				break;
			}
			case Sensor::SensorType::HUM: {
				_sensors[newId] = std::make_unique<HumiditySensor>(newId, _mainNode);
				break;
			}
			case Sensor::SensorType::PRESS: {
				_sensors[newId] = std::make_unique<PressureSensor>(newId, _mainNode);
				break;
			}
		}
	}
	bool subscribe(std::string name, std::unique_ptr<Client> client) {
		std::unique_lock lock(_mutex);
		if (_subscribents.find(name) == _subscribents.end()) {
			_subscribents[name] = std::move(client);
			return true;
		}
		return false;
	}
	bool unsubscribe(std::string name) {
		std::unique_lock lock(_mutex);
		if (_subscribents.find(name) == _subscribents.end()) {
			_subscribents.erase(name);
			return true;
		}
		return false;
	}
	void notifySubscribents() {
		while (_systemStatus) {
			
			if (_notifyFlag) {
#ifdef _WIN32 || _WIN64
				system("cls");
#endif
#ifdef __linux__
				system("clear");
#endif
				std::unique_lock lock(_mutex);
				for (auto& i : _subscribents) {

					i.second->notify(_mainNode->getCollectedData(), _fullNotification);
				}
				std::cout << "Available sensors: " << _sensors.size() << std::endl;
				std::chrono::milliseconds timespan(1000);
				std::this_thread::sleep_for(timespan);
				lock.unlock();
			}
			
		}

	}
	void removeSensor(int sensorId){
		_sensors.erase(sensorId);
	}
	void stopSensorMeasurements(int sensorId) {
		_sensors[sensorId]->stopMeasure();
	}
	void listSensors() {
		for (auto &i : _sensors)
		{
			std::cout << i.second->getType() << ", with id: " << i.first << std::endl;
		}
	}
	void startNotifying(bool fullNotif = false) {
		_notifyFlag = true;
		_fullNotification = fullNotif;
	}
	void stopNotifying() {
		_notifyFlag = false;
	}
	void closeSystem() {
		_systemStatus = false;
		_worker.join();
		for (auto& i : _sensors) {
			i.second->stopMeasure();
		}
	}

private:
	bool _systemStatus = true;
	mutable std::shared_mutex _mutex;
	std::thread _worker = std::thread(&System::notifySubscribents, this);
	bool _notifyFlag = false;
	bool _fullNotification = false;
	std::shared_ptr<Node> _mainNode;
	std::unordered_map<int, std::unique_ptr<Sensor>> _sensors;
	std::unordered_map<std::string, std::unique_ptr<Client>> _subscribents;
};

