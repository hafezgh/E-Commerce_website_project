#ifndef __OFFER__
#define __OFFER__

#include <string>
#include <time.h>
#include <cstdlib>
#include <vector>

static const char alphanum[] =
"0123456789"
"!@#$%^&*"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";

class Offer {
public:
    Offer(int _id, int _productdId, float _unitPrice, int _sellerId, int _amount, std::string _productName) {
        Id = _id; productId = _productdId; amount = _amount; sellerId = _sellerId; unitPrice = _unitPrice; productName = _productName;};
    int getOfferId() {return Id;};
    int getSellerId() {return sellerId;};
    void setAmount(int newAmount) {amount = newAmount;};
    void setUnitPrice(float newPrice) {unitPrice = newPrice;};
    int getAmount() {return amount;};
    bool doesDiscountExists(std::string discountCode);
    float getDiscountPercent(std::string discountCode);
    void invalidateDiscount(std::string discountCode);
    float getOfferUnitPrice() {return unitPrice;};
    int getProductId() {return productId;};
    std::string getProductName() {return productName;};
    int getOfferAmount() {return amount;};
    std::string getOfferDataForPrinting() {return (std::to_string(productId) + " | " + std::to_string(Id) + " | " + 
                                                    std::to_string(unitPrice) + " | " + std::to_string(amount));};
    int getDiscountIndex(std::string discountCode);
    std::string generateDiscountCode();
    float getUnitPrice() {return unitPrice;};
    void addDiscountCode(float discountPercent);
private:
    int Id;
    int amount;
    int productId;
    float unitPrice;
    int sellerId;
    int potentialBuyerId;
    std::string productName;
    std::vector<std::string> discountCodes;
    std::vector<float> discountPercents;
};



#endif