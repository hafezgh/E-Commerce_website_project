#ifndef __TV__
#define __TV__

#include "product.hpp"
#include <string>
#include <vector>

class TV : public Product {
public:
    TV(int _productId, std::string _name, int _screenSize, std::string _screenTech, std::string _resolution, bool _isThreeD, bool isHDR) {
    productId = _productId; name = _name; screenSize = _screenSize; screenTech = _screenTech, resolution = _resolution, isThreeD = _isThreeD; isHDR = isHDR;};
    std::string virtual getProductFeaturesForPrinting() {return (name + '\n' + "Screen Size: " + std::to_string(screenSize) + '\n' +
        "Screen Type: "+ screenTech + '\n' + "Resolution: " + resolution + '\n' + "3D: " + std::to_string(int(isThreeD)) + '\n' + "HDR: " + std::to_string(int(isHDR)));};;
    std::vector<std::string> virtual getProductFeaturesForCompare() {std::vector<std::string> vect{std::to_string(screenSize), screenTech,
        resolution, std::to_string(int(isThreeD)), std::to_string(int(isHDR)), std::to_string(productId)}; return vect;};
private:
    int screenSize;
    std::string screenTech;
    std::string resolution;
    bool isThreeD;
    bool isHDR;
    int productId;
};

#endif