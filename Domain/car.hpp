#ifndef __CAR__
#define __CAR__

#include <string>
#include "product.hpp"

class Car : public Product {
public:
    Car(int _productId, std::string _name, int _weight, int _numOfPassengers, int _numOfCylinders, int _engineCapacity, bool _hasParkingSensor) {
        productId = _productId; name = _name; weight = _weight; numOfPassengers = _numOfPassengers; numOfCylinders = _numOfCylinders;
        engineCapacity = _engineCapacity; hasParkingSensor = _hasParkingSensor;};
    std::string virtual getProductFeaturesForPrinting() {return (name + '\n' + "Weight: " + std::to_string(weight) + '\n' + "Num. of Seats" +
        std::to_string(numOfPassengers) + '\n' + "Num. of Cylinders: " + std::to_string(numOfCylinders) + '\n' +  "Engine Capacity: " 
        + std::to_string(engineCapacity) + '\n' + "Reverse Parking Sensor: " + std::to_string(int(hasParkingSensor)));};
    std::vector<std::string> virtual getProductFeaturesForCompare() {std::vector<std::string> vect{std::to_string(weight), std::to_string(numOfPassengers),
        std::to_string(numOfCylinders), std::to_string(engineCapacity), std::to_string(int(hasParkingSensor))}; return vect;};
private:
    int weight;
    int productId;
    int numOfPassengers;
    int numOfCylinders;
    int engineCapacity;
    bool hasParkingSensor;
};

#endif