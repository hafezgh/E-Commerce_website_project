#ifndef __SELLER__
#define __SELLER__

#include <string>
#include <vector>
#include "offer.hpp"
#include "user.hpp"

class Seller : public User {
public:
    Seller(std::string _email, std::string _username, std::string _password, int _Id) {totalIncome = 0.0; email = _email; username = _username;
                                                                                        password = _password; Id = _Id;};
    int setId() {return Id;};
    int getId() {return Id;};
    std::string getEmail() {return email;};
    std::string getPassword() {return password;};
    std::string getUserName() {return username;};
    int getOfferIndex(int offerId);
    std::vector<Offer> getOffers() {return offers;};
    void addOffer(int id, int productId, float unitPrice, int sellerId, int amount, std::string productName);
    bool isOfferNew(int productId);
    bool doesOfferExist(int offerId) {if(getOfferIndex(offerId) == -1) return false; return true;};
    void changeOffer(int offerId, float newOfferUnitPrice, int newOfferAmount);
    void addDiscountCodesToOffer(int offerId, int discountPercent, int discountNum);
    void purchaseOffer(int offerId, float discountPercent);
    void printWallet(int count);
private:
    std::vector<Offer> offers;
    float totalIncome;
    std::vector <float> wallet{0.0};
};

#endif