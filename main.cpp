#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <atomic>
#include "System.h"
#include "Client.h"

int main()
{
    //Create system instance with 10-size circular buffer
    System s(10);
    //Example vector of clients which gona subscribe main node
    std::vector<Client> clients;
    //Adding new client with name tadek
    clients.emplace_back(Client("tadek"));
    //Subscribe sensor notifications by tadek
    s.subscribe(clients[0].getName(), std::make_unique<Client>(clients[0]));
    //Adding new client with name mirek
    clients.emplace_back(Client("mirek"));
    //Subscribe sensor notifications by mirek
    s.subscribe(clients[1].getName(), std::make_unique<Client>(clients[1]));
    //Add some example sensors
    s.addSensor(Sensor::SensorType::HUM);
    s.addSensor(Sensor::SensorType::PRESS);

    //Example loop to make program responsible and editable during runtime
    char tmp = '0';

    while (tmp != 'x') {
        tmp = std::getchar();
        switch (tmp) {
            //Add new client with id based on clients number
            case 'c': {
                clients.emplace_back(Client(std::to_string(clients.size())));
                s.subscribe(clients[clients.size() - 1].getName(), std::make_unique<Client>(clients[clients.size() - 1]));
                break;
            }
            //Add new humidity sensor
            case 'h': {
                s.addSensor(Sensor::SensorType::HUM);
                break;
            }
            //Add new temperature sensor

            case 't': {
                s.addSensor(Sensor::SensorType::TEMP);
                break;
            }
            //Add new pressure sensor

            case 'p': {
                s.addSensor(Sensor::SensorType::PRESS);
                break;
            }
            //Start notyfing clients with default printing last value received by client
            case 's': {
                s.startNotifying();
                break;
            }
            //Stop notyfing clients
            case 'o': {
                s.stopNotifying();
                break;
            }
            //Enable full notifications
            case 'f': {
                s.startNotifying(true);
                break;
            }
            case'm': {
                s.stopSensorMeasurements(0);
                break;
            }
        }
    }
    //Start closing procedure (join threads etc.)
    s.closeSystem();
    
    return 0;
}