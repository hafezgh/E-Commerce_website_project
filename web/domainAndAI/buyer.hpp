#ifndef __BUYER__
#define __BUYER__

#include <string>
#include <vector>
#include <cstdlib>
#include "offer.hpp"
#include "user.hpp"

class Buyer : public User {
public:
    Buyer(std::string _email, std::string _username, std::string _password, int _Id) {credit = 0.0; email = _email; username = _username;
                                                                        password = _password; Id = _Id;};
    void submitCart();
    void emptyCart() {cart.first.clear(); cart.second.first.clear(); cart.second.second.clear();};
    int setId() {return Id;};
    int getId() {return Id;};
    std::string getEmail() {return email;};
    std::string getPassword() {return password;};
    virtual std::string getUserName() {return username;};
    std::pair<std::vector <Offer>, std::pair<std::vector<int>, std::vector<float>>> getBuyerCart() {return cart;};
    void addOfferToCart(Offer offer, int offerAmount, float discountPercent);
    void chargeWallet(float amount);
    void storePurchasedCar();
    void printWallet(int count);
    void printCart(std::pair<std::vector <Offer>, std::pair<std::vector<int>, std::vector<float>>> _cart);
    void printOrders(int count);
    float getTotalCartPrice() {return cartTotalPrice;}; 
    float getCredit(){return credit;};
    std::string getCartForPrinting() {return cartForPrinting;};
    std::string getWallet() {return walletStr;};
private:
    std::string cartForPrinting;
    std::string walletStr;
    std::vector <float> wallet{0.0};
    float credit;
    float cartTotalPrice;
    std::pair<std::vector <Offer>, std::pair<std::vector<int>, std::vector<float>>> cart;
    std::vector<std::pair<std::vector <Offer>, std::pair<std::vector<int>, std::vector<float>>>> purchasedCarts;
};

#endif