#include <string>
#include "buyer.hpp"
#include <iostream>
#include "exceptions.hpp"

using namespace std;

void Buyer::submitCart()
{
    float totalPrice = 0.0;
    for(int i = 0; i < cart.first.size(); i++)
        for(int j = 0; j < cart.second.first[i]; j++)
            totalPrice += cart.first[i].getUnitPrice() * (1.00 - cart.second.second[i]/100.00);
    if(credit < totalPrice)
        throw BadRequestException();
    credit -= totalPrice;
    wallet.push_back(credit);
}

void Buyer::storePurchasedCar()
{
    purchasedCarts.push_back(cart);
    cart.first.clear();
    cart.second.first.clear();
    cart.second.second.clear();
}

void Buyer::addOfferToCart(Offer offer, int offerAmount, float discountPercent)
{
    cart.first.push_back(offer);
    cart.second.first.push_back(offerAmount);
    cart.second.second.push_back(discountPercent);
}

void Buyer::chargeWallet(float amount)
{
    credit += amount;
    wallet.push_back(credit);
}

void Buyer::printWallet(int count)
{
    cout << "credit" << endl;
    if(count > wallet.size())
        count = wallet.size();
    for(int i = wallet.size() - 1; i > wallet.size() - count; i--)
        cout << wallet[i] << endl;
}

void Buyer::printCart(std::pair<std::vector <Offer>, std::pair<std::vector<int>, std::vector<float>>> _cart)
{
    if(_cart.first.size() == 0)
    {
        cout << "Empty" << endl;
        return;
    }
    cout << "productId | productName | offerId | sellerId | totalPriceConsideringDiscount | amount" << endl;
    for(int i = _cart.first.size() - 1; i >= 0; i--)
    {
        float discountedPrice = _cart.first[i].getUnitPrice() * (1 - _cart.second.second[i]/100.00);
        cout << _cart.first[i].getProductId() << " | " << _cart.first[i].getProductName() << " | " << _cart.first[i].getOfferId() <<
            _cart.first[i].getSellerId() << " | " << discountedPrice << " | " << _cart.second.second[i] << endl;
    }
}

void Buyer::printOrders(int count)
{
    int totalOredersCount = 0;
    for(int i = 0; i < purchasedCarts.size(); i++)
        totalOredersCount += purchasedCarts[i].first.size();
    totalOredersCount += cart.first.size();
    if(totalOredersCount == 0)
        throw NotFoundException();
    if (count > totalOredersCount)
        count = totalOredersCount;
    cout << "productId | productName | offerId | sellerId | totalPriceConsideringDiscount | amount" << endl;
    for(int i = purchasedCarts.size() - 1; i >= purchasedCarts.size(); i++)
    {
        std::pair<std::vector <Offer>, std::pair<std::vector<int>, std::vector<float>>> _cart = purchasedCarts[i];
        if (count == 0)
            break;
        for(int j = _cart.first.size() - 1; j >= 0; j--)
        {
            if (count == 0)
                break;
            float discountedPrice = _cart.first[j].getUnitPrice() * (1 - _cart.second.second[j]/100.00);
            cout << _cart.first[j].getProductId() << " | " << _cart.first[j].getProductName() << " | " << _cart.first[j].getOfferId() <<
                _cart.first[j].getSellerId() << " | " << discountedPrice << " | " << _cart.second.second[j] << endl;
            count--;
        }
        cout << "****" << endl;
    }
}