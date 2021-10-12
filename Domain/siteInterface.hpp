#ifndef __SITE_INTERFACE__
#define __SITE_INTERFACE__

#include <string>
#include "seller.hpp"
#include "buyer.hpp"
#include "product.hpp"
#include "exceptions.hpp"
#include <vector>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <iterator>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <math.h>
#include "mobile.hpp"
#include "tv.hpp"
#include "car.hpp"

#define ADMIN_USER "siteAdmin"
#define ADMIN_PASS "0000Admin@"
#define ADMIN_EMAIL "admin@gmail.com"
#define ADMIN_USERID 0
#define COMMA ','
#define SPACE ' '



class SiteInterface {
public:
    SiteInterface(){adminUsername = ADMIN_USER; adminPassword = ADMIN_PASS; adminEmail = ADMIN_EMAIL; userCounter = 0; productCounter = 0;
                    adminLoggedIn = true; noOneLoggedIn = false; sellerLoggedIn = false; buyerLoggedIn = false; loggedInUserId = 0; offerCounter = 0;
                    loggedInEmail = ADMIN_EMAIL; loggedInPassword = ADMIN_PASS; loggedInUsername = ADMIN_USER; adminUserId = ADMIN_USERID;};
    ~SiteInterface();
    void parseCommand();
    void executePostCommand();
    void executeGetCommand();
    int getSellerIndex(int Id);
    int getBuyerIndex(int Id);
    int getProductIndex(int Id);
    void readMobiles(std::string filePath);
    void readTVs(std::string filePath);
    void readCars(std::string filePath);
    std::string command;
    std::vector<std::string> parsedCommand;
    void compareProducts(int product1Index, int product2Index, std::string productType);
private:
    bool adminLoggedIn;
    bool noOneLoggedIn;
    bool buyerLoggedIn;
    bool sellerLoggedIn;
    std::string loggedInUsername;
    std::string loggedInEmail;
    std::string loggedInPassword;
    int userCounter;
    int productCounter;
    int offerCounter;
    int loggedInUserId;
    int adminUserId;
    std::string adminUsername;
    std::string adminPassword;
    std::string adminEmail;
    std::vector<Buyer> buyers;
    std::vector<Seller> sellers;
    std::vector<Product*> products;
    std::vector<Offer> allOffers;
};

#endif