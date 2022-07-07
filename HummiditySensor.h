#pragma once
#include "Sensor.h"
class HumiditySensor :
    public Sensor
{
public:
    HumiditySensor(int id, std::shared_ptr<Node> mainNode)
    {
        this->_id = id;
        this->_mainNode = mainNode;
        this->_stopFlag = false;
        this->_dist = std::uniform_real_distribution<float>(0, 100.0);
        this->_type = SensorType::HUM;
        std::cout << "Humidity sensor created" << std::endl;
    }
    virtual ~HumiditySensor() {
        _worker.join();
        std::cout << "Sensor{" << _id << "} - my Job is done" << std::endl;
    }

    SensorType getType() {
        return this->_type;
    }

private:
    std::thread _worker = std::thread(&HumiditySensor::measure, this);
};

