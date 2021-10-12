#ifndef __PRODUCT__
#define __PRODUCT__

#include <iostream>
#include <string>
#include <vector>

class Product {
public:
    int getId() {return Id;};
    void addComment(std::string comment) {comments.push_back(comment);};
    std::string getProductName() {return name;};
    std::string getProductType() {return type;};
    void printProdcutComments() {for(int i = comments.size() - 1; i >= 0; i--) std::cout << comments[i] << std::endl;};
    std::string virtual getProductFeaturesForPrinting() = 0;
    std::vector<std::string> virtual getProductFeaturesForCompare() = 0;
protected:
    std::string name;
    std::string type;
    std::vector<std::string> comments;
    int Id;
};

#endif