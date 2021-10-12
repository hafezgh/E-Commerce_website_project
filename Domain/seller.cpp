#include <string>
#include "seller.hpp"
#include <iostream>

using namespace std;

int Seller::getOfferIndex(int offerId) 
{
    for(int i = 0; i < offers.size(); i++) 
        if(offers[i].getOfferId() == offerId) 
            return i; 
    return -1;
}

void Seller::addOffer(int id, int productId, int unitPrice, int sellerId, int amount, std::string productName) 
{
    offers.push_back(Offer(id, productId, unitPrice, sellerId, amount, productName));
}

bool Seller::isOfferNew(int productId)
{
    for(int i = 0; i < offers.size(); i++)
        if(offers[i].getProductId() == productId)
            return true;
    return false;
}

void Seller::changeOffer(int offerId, float newOfferUnitPrice, int newOfferAmount)
{
    int offerIndex = getOfferIndex(offerId);
    offers[offerIndex].setUnitPrice(newOfferUnitPrice);
    offers[offerIndex].setAmount(newOfferAmount);
}

void Seller::addDiscountCodesToOffer(int offerId, int discountPercent, int discountNum)
{
    int offerIndex = getOfferIndex(offerId);
    for(int i = 0; i < discountNum; i++)
        offers[offerIndex].addDiscountCode(discountPercent);
}

void Seller::purchaseOffer(int offerId, float discountPercent)
{
    int offerIndex = getOfferIndex(offerId);
    float income = offers[offerIndex].getOfferUnitPrice() * (1.00 - discountPercent/100.00);
    totalIncome += income;
    wallet.push_back(totalIncome);
}

void Seller::printWallet(int count)
{
    cout << "credit" << endl;
    if(count > wallet.size())
        count = wallet.size();
    for(int i = wallet.size() - 1; i > wallet.size() - count; i--)
        cout << wallet[i] << endl;
}