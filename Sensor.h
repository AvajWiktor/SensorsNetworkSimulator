#pragma once
#include <vector>
#include <thread>
#include <chrono>
#include <atomic>
#include <random>
#include "Node.h"
#include "Topic.h"
#include <iostream>
class Sensor
{
public:
		virtual ~Sensor() {}
		enum SensorType
		{
			TEMP = 0,
			HUM = 1,
			PRESS = 2
		};
		virtual SensorType getType() = 0;
		void stopMeasure() {
			std::cout << "I stopped measuring" << std::endl;
			this->_stopFlag = true;
		}
		void measure() {
			std::random_device random_device;
			std::mt19937 random_engine(random_device());

			while (!_stopFlag) {
				_measurement = this->_dist(random_engine);
				_mainNode->publishValue(Topic(this->_id, _measurement, this->_type));
			}
		}
protected:
		int _id;
		std::shared_ptr<Node> _mainNode;
		bool _stopFlag = false;
		float _measurement{};
		std::uniform_real_distribution<float> _dist;
		SensorType _type;
};

