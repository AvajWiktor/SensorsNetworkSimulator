#pragma once
#include "Sensor.h"
class TemperatureSensor :
    public Sensor
{
public:
    TemperatureSensor(int id, std::shared_ptr<Node> mainNode)
    {
        this->_id = id;
        this->_mainNode = mainNode;
        this->_stopFlag = false;
        this->_dist = std::uniform_real_distribution<float>(-50.0, 50.0);
        this->_type = SensorType::TEMP;
        std::cout << "Temperature sensor created" << std::endl;
    }
    virtual ~TemperatureSensor() {
        _worker.join();
        std::cout << "Sensor{"<<_id<<"} - my Job is done"<<std::endl;
    }

    SensorType getType() {
        return this->_type;
    }

private:
    std::thread _worker = std::thread(&TemperatureSensor::measure, this);
};

