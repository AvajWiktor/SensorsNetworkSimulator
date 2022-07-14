#pragma once
#include <vector>
#include "Topic.h"
#include <iostream>
//Client class which gona subscribe and receive notifications
class Client
{
public:
	Client(std::string name):_name(name){}

	void notify(std::vector<Topic> notification, bool fullNotif) {
		_sensorsData = notification;
		
		if (fullNotif) {
			std::cout << "Client [" << _name << "] received full notification" << std::endl;

			for (auto& i : _sensorsData) {
				std::cout << i.getMessage() << std::endl;
			}
		}
		else {
			std::cout << "Client [" << _name << "] received notification with last value: " << _sensorsData[_sensorsData.size() - 1].getRawMeasurement() << std::endl;
		}
		std::cout << "#################################" << std::endl;
	}
	std::string getName() {
		return _name;
	}
private:
	std::vector<Topic> _sensorsData;
	std::string _name{};
};

