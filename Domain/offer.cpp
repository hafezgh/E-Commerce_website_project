#include "offer.hpp"

using namespace std;

string Offer::generateDiscountCode()
{
    int stringLength = sizeof(alphanum) - 1;
    string discountCode;
    srand(time(0));
    for(int i = 0; i < 8; i++)
        discountCode += alphanum[rand() % stringLength];
    return discountCode;
}

int Offer::getDiscountIndex(string discountCode)
{
    for(int i = 0; i < discountCodes.size(); i++)
        if(discountCodes[i] == discountCode)
            return i;
    return -1;
}

void Offer::addDiscountCode(float discountPercent) 
{
    string newDiscountCode;
    bool isCodeValid = true;
    while(true)
    {
        isCodeValid = true;
        newDiscountCode = generateDiscountCode();
        for(int i = 0; i < discountCodes.size(); i++)
            if(discountCodes[i] == newDiscountCode)
            {
                isCodeValid = false;
                break;
            }
        if(isCodeValid == true)
            break;
        else
            continue;
    }
    discountCodes.push_back(newDiscountCode); 
    discountPercents.push_back(discountPercent);
}

bool Offer::doesDiscountExists(string discountCode)
{
    if(getDiscountIndex(discountCode) != -1)
        return true;
    return false;
}

float Offer::getDiscountPercent(string discountCode)
{
    for(int i = 0; i < discountCodes.size(); i++)
        if(discountCodes[i] == discountCode)
            return discountPercents[i];
}

void Offer::invalidateDiscount(std::string discountCode)
{
    int index;
    for(int i = 0; i < discountCodes.size(); i++)
        if(discountCodes[i] == discountCode)
            index = i;
    discountCodes.erase(discountCodes.begin() + index);
    discountPercents.erase(discountPercents.begin() + index);
}