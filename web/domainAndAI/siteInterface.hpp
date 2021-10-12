#ifndef __SITE_INTERFACE__
#define __SITE_INTERFACE__

#include <string>
#include "seller.hpp"
#include "buyer.hpp"
#include "product.hpp"
#include "exceptions.hpp"
#include "user.hpp"
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
#include "CommentEvaluatorAI.hpp"

#define ADMIN_USER "siteAdmin"
#define ADMIN_PASS "admin"
#define ADMIN_EMAIL "admin@gmail.com"
#define ADMIN_USERID 0
#define COMMA ','
#define SPACE ' '
#define PC_FILE_PATH "class probabilities"
#define TRAIN_DATA_FILE_PATH "train.csv"
#define TEST_DATA_FILE_PATH "test.csv"
#define CARS_FILE_PATH "Car.csv"
#define MOBILES_FILE_PATH "Mobile.csv"
#define TVS_FILE_PATH "TV.csv"

class SiteInterface {
public:
    SiteInterface(std::string _PcFilePath, std::string _trainDataFilePath, std::string _testDataFilePath) {
        adminUsername = ADMIN_USER; adminPassword = ADMIN_PASS; adminEmail = ADMIN_EMAIL; userCounter = 0; productCounter = 0;
                    adminLoggedIn = true; noOneLoggedIn = false; sellerLoggedIn = false; buyerLoggedIn = false;
                     loggedInUserId = 0; offerCounter = 0; loggedInEmail = ADMIN_EMAIL; loggedInPassword = ADMIN_PASS;
                    loggedInUsername = ADMIN_USER; adminUserId = ADMIN_USERID; PcFilePath = _PcFilePath;
                     trainDataFilePath = _trainDataFilePath; testDataFilePath = _testDataFilePath; commentCounter = 0;
                     commentEval = new CommentEvaluatorAI(_PcFilePath, _trainDataFilePath, _testDataFilePath);}
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
    void readProducts() {readCars(CARS_FILE_PATH); readMobiles(MOBILES_FILE_PATH); readTVs(TVS_FILE_PATH);};
    bool evalComment(std::string comment);
    std::string command;
    std::vector<std::string> parsedCommand;
    void compareProducts(int product1Index, int product2Index, std::string productType);
    void handleRequest(std::string request);
    void calcAllUsers();
    std::vector<User*> getAllUsers() {return allUsers;};
    int getSellersCount() {return buyers.size();};
    int getBuyersCount() {return sellers.size();};
    bool getAdminLoginStatus() {return adminLoggedIn;};
    bool getBuyerLoginStatus() {return buyerLoggedIn;};
    bool getSellerLoginStatus() {return sellerLoggedIn;};
    std::string getLoggedInUsername() {return loggedInUsername;};
    std::string getAdminUsername() {return adminUsername;};
    std::string PcFilePath;
    std::string trainDataFilePath;
    std::string testDataFilePath;
    std::string getCurrentSellerOffers() {return currentSellerOffers;};
    std::string getAllProdects() {return allProducts;};
    std::string getAllOffersStr() {return allOffersStr;};
    std::string getCurrentProductDetails() {return currentProductDetails;};
    std::string getCurrentProductOffers() {return currentProductOffers;};
    std::string getCurrentBuyerCart() {return currentBuyerCart;};
    float getCurrentBuyerTotalCartPrice() {return currentBuyerCartTotalPrice;};
    std::string getCurrentBuyerWallet() {return currentBuyerWallet;};
    int commentCounter;
private:
    float currentBuyerCartTotalPrice;
    std::string currentBuyerWallet;
    bool adminLoggedIn;
    bool noOneLoggedIn;
    bool buyerLoggedIn;
    bool sellerLoggedIn;
    std::string loggedInUsername;
    std::string loggedInEmail;
    std::string loggedInPassword;
    std::string currentSellerOffers;
    std::string currentProductDetails;
    std::string currentBuyerCart;
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
    std::vector<User*> allUsers;
    std::string allOffersStr;
    std::string currentProductOffers;
    CommentEvaluatorAI* commentEval;
    std::string allProducts;
};

#endif