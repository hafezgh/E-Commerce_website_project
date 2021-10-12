#ifndef __MOBILE__
#define __MOBILE__

#include "product.hpp"
#include <string>

class Mobile : public Product {
public:
    Mobile(int _productId, std::string _name, int _weight, int _CPUFrequency, int _internalMemory, int _RAM, int _screenSize, int _cameraResolution, std::string _OS) {
    Id = _productId; name = _name; weight = _weight; CPUFrequency = _CPUFrequency; internalMemory = _internalMemory; screenSize = _screenSize; 
    cameraResolution = _cameraResolution; OS = _OS;};
    std::string virtual getProductFeaturesForPrinting() {return (name + '\n' + "Weight: " + std::to_string(weight) + '\n' + "CPU Frequency: " +
        std::to_string(CPUFrequency) + '\n' + "Built-in Memory: " + std::to_string(internalMemory) + '\n' +  "RAM: " + std::to_string(RAM) +
        + "Display Size: " + std::to_string(screenSize) + '\n' + "Camera Resolution: " + std::to_string(cameraResolution) + 
        '\n' + "Operating System: " + OS);};
    std::vector<std::string> virtual getProductFeaturesForCompare() {std::vector<std::string> vect{std::to_string(weight), std::to_string(CPUFrequency),
        std::to_string(internalMemory), std::to_string(RAM), std::to_string(screenSize), std::to_string(cameraResolution), OS}; return vect;};
private:
    int weight;
    float CPUFrequency;
    int internalMemory;
    int RAM;
    float screenSize;
    int cameraResolution;
    std::string OS;
};

#endif