#pragma once
#include "Sensor.h"
class PressureSensor :
    public Sensor
{
public:
    PressureSensor(int id, std::shared_ptr<Node> mainNode)
    {
        this->_id = id;
        this->_mainNode = mainNode;
        this->_stopFlag = false;
        this->_dist = std::uniform_real_distribution<float>(980,1200.0);
        this->_type = SensorType::PRESS;
        std::cout << "Pressure sensor created" << std::endl;
    }
    virtual ~PressureSensor() {
        _worker.join();
        std::cout << "Sensor{" << _id << "} - my Job is done" << std::endl;
    }

    SensorType getType() {
        return this->_type;

    }

private:
    std::thread _worker = std::thread(&PressureSensor::measure, this);
};

