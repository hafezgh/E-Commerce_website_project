#include "siteInterface.hpp"

using namespace std;

vector<string> parseCSVLine(string line)
{
    vector<string> parsedLine;
    stringstream ss(line);
    string substr;
    while(ss.good())
    {
        getline(ss, substr, COMMA);
        parsedLine.push_back(substr);
    }
    return parsedLine;
}

void SiteInterface::parseCommand()
{
    stringstream ss(command);
    istream_iterator<string> begin(ss);
    istream_iterator<string> end;
    vector<string> vstrings(begin, end);
    parsedCommand = vstrings;
    if(parsedCommand.size() == 0)
        throw BadRequestException();
    if(parsedCommand.size() > 0 && (parsedCommand[0] != "POST" && parsedCommand[0] != "GET"))
        throw BadRequestException();
}

int SiteInterface::getProductIndex(int Id)
{
    for(int i = 0; i < products.size(); i++)
        if(products[i]->getId() == Id)
            return i;
    return -1;
}

int SiteInterface::getBuyerIndex(int Id)
{
    for(int i = 0; i < buyers.size(); i++)
        if(buyers[i].getId() == Id)
            return i;
    return -1;
}

int SiteInterface::getSellerIndex(int Id)
{
    for(int i = 0; i < sellers.size(); i++)
        if(sellers[i].getId() == Id)
            return i;
    return -1;
}

void SiteInterface::executePostCommand()
{
    if (parsedCommand.size() < 2)
        throw NotFoundException();
    if (parsedCommand.size() == 2)
    {
        if(parsedCommand[1] == "submitCart") 
        {
            if(buyerLoggedIn == false)
                throw PermissionDeniedException();
            int buyerIndex = getBuyerIndex(loggedInUserId);
            pair<vector <Offer>, pair<vector<int>, vector<float>>> buyerCart = buyers[buyerIndex].getBuyerCart();
            buyers[buyerIndex].submitCart();
            for(int i = 0; i < buyerCart.first.size(); i++)
                for(int j = 0; j < buyerCart.second.first[i]; j++)
                    sellers[getSellerIndex(buyerCart.first[i].getSellerId())].purchaseOffer(buyerCart.first[i].getOfferId(), buyerCart.second.second[i]);
            buyers[buyerIndex].storePurchasedCar();
            cout << "OK" << endl;
            return;
        }
        if(parsedCommand[1] == "logout") 
        {
            if(noOneLoggedIn == true)
                throw PermissionDeniedException();
            /*if(buyerLoggedIn == true)
                buyers[getBuyerIndex(loggedInUserId)].emptyCart();*/
            adminLoggedIn = false;
            buyerLoggedIn = false;
            sellerLoggedIn = false;
            noOneLoggedIn = true;
            loggedInUsername = "";
            loggedInUserId = -1;
            loggedInPassword = "";
            loggedInEmail = "";
            cout << "OK" << endl;
            return;
        }
        if(parsedCommand[1] == "evaluateModel")
        {
            commentEval->saveModelEvaluationResult();
        }
        throw NotFoundException();
    }
    if (parsedCommand[1] == "signup")
    {
        if(parsedCommand.size() != 9 && parsedCommand.size() != 11)
            throw BadRequestException();
        if(parsedCommand[2] != "?" || parsedCommand[3] != "email" || parsedCommand[5] != "username" || parsedCommand[7] != "password")
            throw BadRequestException();
        if(parsedCommand.size() == 11 && (parsedCommand[9] != "type" || (parsedCommand[10] != "buyer" && parsedCommand[10] != "seller")))
            throw BadRequestException();
        calcAllUsers();
        for(int i = 0; i < allUsers.size(); i++)
        {
            if(allUsers[i]->getUserName() == parsedCommand[6])
                throw UserNameExistsException();
        }
        for(int i = 0; i < allUsers.size(); i++)
        {
            if(allUsers[i]->getEmail() == parsedCommand[4])
                throw EmailExistsException();
        }
        if(noOneLoggedIn == false)
        {
            adminLoggedIn = false;
            buyerLoggedIn = false;
            sellerLoggedIn = false;
            noOneLoggedIn = true;
        }
        if(parsedCommand.size() == 9 || (parsedCommand.size() == 11 && parsedCommand[10] == "buyer"))
        {
            userCounter++;
            buyers.push_back(Buyer(parsedCommand[4], parsedCommand[6], parsedCommand[8], userCounter));
            loggedInUserId = userCounter;
            loggedInEmail = parsedCommand[4];
            loggedInUsername = parsedCommand[6];
            loggedInPassword = parsedCommand[8];
            buyerLoggedIn = true;
            noOneLoggedIn = false;
            adminLoggedIn = false;
            sellerLoggedIn = false;
        }
        if(parsedCommand.size() == 11 && parsedCommand[10] == "seller") 
        {
            userCounter++;
            sellers.push_back(Seller(parsedCommand[4], parsedCommand[6], parsedCommand[8], userCounter));
            loggedInUserId = userCounter;
            loggedInEmail = parsedCommand[4];
            loggedInUsername = parsedCommand[6];
            loggedInPassword = parsedCommand[8];
            sellerLoggedIn = true;
            noOneLoggedIn = false;
            adminLoggedIn = false;
            buyerLoggedIn = false;
        }
        cout << "OK" << endl;
        return;
    }
    if(parsedCommand[1] == "login")
    {
        bool badRequest = true;
        if(parsedCommand.size() != 7 || parsedCommand[2] != "?" || parsedCommand[3] != "email" || parsedCommand[5] != "password")
            throw BadRequestException();

        if(parsedCommand[4] == ADMIN_EMAIL && parsedCommand[6] == ADMIN_PASS)
        {
            /*if(buyerLoggedIn == true)
                buyers[getBuyerIndex(loggedInUserId)].emptyCart();*/
            badRequest == false;
            adminLoggedIn = true;
            noOneLoggedIn = false;
            buyerLoggedIn = false;
            sellerLoggedIn = false;
            loggedInUserId = adminUserId;
            loggedInEmail = adminEmail;
            loggedInPassword = adminPassword;
            loggedInUsername = adminUsername;
            cout << "OK" << endl;
            return;
        }
        for(int i = 0; i < buyers.size(); i++)
        {
            if(parsedCommand[4] == buyers[i].getEmail() && parsedCommand[6] == buyers[i].getPassword())
            {
                /*if(buyerLoggedIn == true)
                    buyers[getBuyerIndex(loggedInUserId)].emptyCart();*/
                badRequest = false;
                adminLoggedIn = false;
                noOneLoggedIn = false;
                buyerLoggedIn = true;
                sellerLoggedIn = false;
                loggedInUserId = buyers[i].getId();
                loggedInEmail = buyers[i].getEmail();
                loggedInPassword = buyers[i].getPassword();
                loggedInUsername = buyers[i].getUserName();
                cout << "OK" << endl;
                return;  
            }
        }
        for(int i = 0; i < sellers.size(); i++)
        {
            if(parsedCommand[4] == sellers[i].getEmail() && parsedCommand[6] == sellers[i].getPassword())
            {
                /*if(buyerLoggedIn == true)
                    buyers[getBuyerIndex(loggedInUserId)].emptyCart();*/
                badRequest = false;
                adminLoggedIn = false;
                noOneLoggedIn = false;
                buyerLoggedIn = false;
                sellerLoggedIn = true;
                loggedInUserId = sellers[i].getId();
                loggedInEmail = sellers[i].getEmail();
                loggedInPassword = sellers[i].getPassword();
                loggedInUsername = sellers[i].getUserName();
                cout << "OK" << endl;
                return;   
            }
        }
        if(badRequest == true)
            throw IncorrectEmailOrPassException();
    }
    if(parsedCommand[1] == "importProducts")
    {
        if(parsedCommand.size() != 7 || parsedCommand[2] != "?" || parsedCommand[3] != "type" || parsedCommand[5] != "filePath")
            throw BadRequestException();
        if(adminLoggedIn != true)
            throw PermissionDeniedException();
        ifstream fin(parsedCommand[6]);
        if(!fin)
            throw NotFoundException();
        fin.close();
        if(parsedCommand[4] == "mobile")
            readMobiles(parsedCommand[6]);
        if(parsedCommand[4] == "TV")
            readTVs(parsedCommand[6]);
        if(parsedCommand[4] == "car")
            readCars(parsedCommand[6]);
        return; 
    }
    if(parsedCommand[1] == "offer")
    {
        if(parsedCommand.size() != 9 || parsedCommand[2] != "?" || parsedCommand[3] != "productId" || parsedCommand[5] != "offerUnitPrice"
            || parsedCommand[7] != "offerAmount")
                throw BadRequestException();
        if(sellerLoggedIn != true)
            throw PermissionDeniedException();
        int productIndex = getProductIndex(atoi(parsedCommand[4].c_str()));
        if(productIndex == -1)
            throw BadRequestException();
        if(!(sellers[getSellerIndex(loggedInUserId)].isOfferNew(atoi(parsedCommand[4].c_str())))){
            cout << "hi" << endl;
            throw BadRequestException();}
        string productName = products[getProductIndex(atoi(parsedCommand[4].c_str()))]->getProductName();
        sellers[getSellerIndex(loggedInUserId)].addOffer(++offerCounter, atoi(parsedCommand[4].c_str()),
                 atof(parsedCommand[6].c_str()), loggedInUserId, atoi(parsedCommand[8].c_str()), productName);
        cout << "OK" << endl;
        return;
    }
    if(parsedCommand[1] == "changeOffer")
    {
        if(parsedCommand.size() != 9 || parsedCommand[2] != "?" || parsedCommand[3] != "offerId" || parsedCommand[5] != "offerUnitPrice"
            || parsedCommand[7] != "offerAmount")
                throw BadRequestException();
        if(sellerLoggedIn != true)
            throw PermissionDeniedException();
        if(!(sellers[getSellerIndex(loggedInUserId)].doesOfferExist(atoi(parsedCommand[4].c_str()))))
            throw BadRequestException();
        sellers[getSellerIndex(loggedInUserId)].changeOffer(atoi(parsedCommand[4].c_str()), atof(parsedCommand[6].c_str()), atoi(parsedCommand[8].c_str()));
        cout << "OK" << endl;
        return;
    }
    if(parsedCommand[1] == "generateDiscountCode")
    {
        if(parsedCommand.size() != 9 || parsedCommand[2] != "?" || parsedCommand[3] != "offerId" || parsedCommand[5] != "discountPercent"
            || parsedCommand[7] != "discountNumber")
                throw BadRequestException();
        if(sellerLoggedIn != true)
            throw PermissionDeniedException();
        if(!sellers[getSellerIndex(loggedInUserId)].isOfferNew(atoi(parsedCommand[4].c_str())))
            throw BadRequestException();
        sellers[getSellerIndex(loggedInUserId)].addDiscountCodesToOffer(atoi(parsedCommand[4].c_str()), 
                atof(parsedCommand[6].c_str()), atoi(parsedCommand[8].c_str()));
        return;
    }
    if(parsedCommand[1] == "addToCart")
    {
        if(parsedCommand.size() != 7 && parsedCommand.size() != 9)
            throw BadRequestException();
        if(parsedCommand[2] != "?" || parsedCommand[3] != "offerId" || parsedCommand[5] != "amount")
            throw BadRequestException();
        if(parsedCommand.size() == 11 && parsedCommand[7] != "discountCode")
            throw BadRequestException();
        if(buyerLoggedIn != true)
            throw PermissionDeniedException();
        bool isRequestValid = false;
        int sellerIndex;
        int offerIndex;
        float discountPercent = 0.0;
        for (int i = 0; i < sellers.size(); i++)
        {
            if(sellers[i].doesOfferExist(atoi(parsedCommand[4].c_str())))
                if(sellers[i].getOffers()[sellers[i].getOfferIndex(atoi(parsedCommand[4].c_str()))].getAmount() > 0)
                {
                    isRequestValid = true;
                    sellerIndex = i;
                    offerIndex = sellers[i].getOfferIndex(atoi(parsedCommand[4].c_str()));
                }
        }
        if(!isRequestValid)
            throw BadRequestException();
        sellers[sellerIndex].changeOffer(atoi(parsedCommand[4].c_str()), sellers[sellerIndex].getOffers()[offerIndex].getUnitPrice(),
                                        sellers[sellerIndex].getOffers()[offerIndex].getOfferAmount() - 1);
        if(parsedCommand.size() == 7)
        {
            buyers[getBuyerIndex(loggedInUserId)].addOfferToCart(sellers[sellerIndex].getOffers()[offerIndex], atoi(parsedCommand[6].c_str()), discountPercent);
            cout << "OK" << endl;
            return;
        }
        if(parsedCommand.size() == 9)
        {
            if(!sellers[sellerIndex].getOffers()[offerIndex].doesDiscountExists(parsedCommand[8]))
                throw BadRequestException();
            discountPercent = sellers[sellerIndex].getOffers()[offerIndex].getDiscountPercent(parsedCommand[8]);
            sellers[sellerIndex].getOffers()[offerIndex].invalidateDiscount(parsedCommand[8]);
        }
        if(parsedCommand.size() == 9)
            buyers[getBuyerIndex(loggedInUserId)].addOfferToCart(sellers[sellerIndex].getOffers()[offerIndex], atoi(parsedCommand[6].c_str()), discountPercent);
        cout << "OK" << endl;
        return;
    }
    if(parsedCommand[1] == "chargeWallet")
    {
        if(parsedCommand.size() != 5)
            throw BadRequestException();
        if(parsedCommand[2] != "?" || parsedCommand[3] != "amount")
            throw BadRequestException();
        if(!buyerLoggedIn)
            throw PermissionDeniedException();
        if(atof(parsedCommand[4].c_str()) <= 0)
            throw BadRequestException();
        buyers[getBuyerIndex(loggedInUserId)].chargeWallet(atof(parsedCommand[4].c_str()));
        cout << "OK" << endl;
        return;
    }
    if(parsedCommand[1] == "comment")
    {
        if(parsedCommand[2] != "?" || parsedCommand[3] != "productId" || parsedCommand[5] != "comment")
            throw BadRequestException();
        if(!buyerLoggedIn)
            throw PermissionDeniedException();
        int productIndex = getProductIndex(atoi(parsedCommand[4].c_str()));
        if(productIndex == -1)
            throw NotFoundException();
        string comment;
        for(int i = 6; i < parsedCommand.size() - 1; i++)
        {
            comment = comment + parsedCommand[i] + ' ';
        }
        comment += parsedCommand[parsedCommand.size()-1];
        if(evalComment(comment))
            return;
        products[productIndex]->addComment(comment);
        commentCounter++;
        cout << "OK" << endl;
        return;
    }
    throw NotFoundException();
}

bool SiteInterface::evalComment(string comment)
{
    return commentEval->evaluateComment(comment);
}

void SiteInterface::readMobiles(string filePath)
{
    ifstream fin(filePath);
    string line;
    vector<string> parsedLine;
    getline(fin, line);
    while(getline(fin, line))
    {
        parsedLine.clear();
        parsedLine = parseCSVLine(line);
        Mobile* newMobile = new Mobile(++productCounter, parsedLine[0], atoi(parsedLine[1].c_str()), atof(parsedLine[2].c_str()), atoi(parsedLine[3].c_str()),
                        atoi(parsedLine[4].c_str()),atof(parsedLine[5].c_str()),atoi(parsedLine[6].c_str()), parsedLine[7]);
        products.push_back(newMobile);
    }
    cout << "OK" << endl;
}

void SiteInterface::readTVs(string filePath)
{
    ifstream fin(filePath);
    string line;
    vector<string> parsedLine;
    getline(fin, line);
    while(getline(fin, line))
    {
        parsedLine.clear();
        parsedLine = parseCSVLine(line);
        TV* newTV = new TV(++productCounter, parsedLine[0], atoi(parsedLine[1].c_str()), parsedLine[2], parsedLine[3], atoi(parsedLine[4].c_str()),
                            atoi(parsedLine[5].c_str()));
        products.push_back(newTV);
    }
    cout << "OK" << endl;
}

void SiteInterface::readCars(string filePath)
{
    ifstream fin(filePath);
    string line;
    vector<string> parsedLine;
    getline(fin, line);
    while(getline(fin, line))
    {
        parsedLine.clear();
        parsedLine = parseCSVLine(line);
        Car* newCar = new Car(++productCounter, parsedLine[0], atoi(parsedLine[1].c_str()), atoi(parsedLine[2].c_str()), atoi(parsedLine[3].c_str()),
                        atoi(parsedLine[4].c_str()),atoi(parsedLine[5].c_str()));
        products.push_back(newCar);
    }
    cout << "OK" << endl;
}

SiteInterface::~SiteInterface()
{
    for(int i = 0; i < products.size(); i++)
        delete products[i];
    delete commentEval;
}

bool sortByOfferIdA(Offer firstOffer, Offer secondOffer)
{
    return firstOffer.getOfferId() < secondOffer.getOfferId();
}

bool sortByOfferIdD(Offer firstOffer, Offer secondOffer)
{
    return firstOffer.getOfferId() > secondOffer.getOfferId();
}

bool sortByOfferPriceA(Offer firstOffer, Offer secondOffer)
{
    if (firstOffer.getOfferUnitPrice() == secondOffer.getOfferUnitPrice())
        return firstOffer.getOfferId() < secondOffer.getOfferId();
    return firstOffer.getOfferUnitPrice() < secondOffer.getOfferUnitPrice();
}

bool sortByOfferPriceD(Offer firstOffer, Offer secondOffer)
{
    if (firstOffer.getOfferUnitPrice() == secondOffer.getOfferUnitPrice())
        return firstOffer.getOfferId() < secondOffer.getOfferId();
    return firstOffer.getOfferUnitPrice() > secondOffer.getOfferUnitPrice();
}

void SiteInterface::executeGetCommand()
{
    if(parsedCommand[1] == "offers")
    {
        if(parsedCommand.size() != 7)
            throw BadRequestException();
        if(parsedCommand[2] != "?" || parsedCommand[3] != "order" || parsedCommand[5] != "field")
            throw BadRequestException();
        if(parsedCommand[4] != "ASCEND" && parsedCommand[4] != "DESCEND")
            throw BadRequestException();
        if(parsedCommand[6] != "offerId" && parsedCommand[6] != "offerPrice")
            throw BadRequestException();
        if(!adminLoggedIn)
            throw PermissionDeniedException();
        vector<Offer> sellerOffers;
        allOffers.clear();
        for (int i = 0; i < sellers.size(); i++)
        {
            sellerOffers.clear();
            sellerOffers = sellers[i].getOffers();
            for(int j = 0; j < sellerOffers.size(); j++)
                allOffers.push_back(sellerOffers[j]);
        }
        allOffersStr = "productId | offerId | offerUnitPrice | offerAmount" + '\n';
        cout<< "productId |" << " offerId |" << " offerUnitPrice |" << " offerAmount" <<endl;
        if(parsedCommand[3] == "ASCEND")
        {
            if(parsedCommand[6] == "offerId")
                sort(allOffers.begin(), allOffers.end(), sortByOfferIdA);
            if(parsedCommand[6] == "offerPrice")
                sort(allOffers.begin(), allOffers.end(), sortByOfferPriceA);
        }
        if(parsedCommand[3] == "DESCEND")
        {
            if(parsedCommand[6] == "offerId")
                sort(allOffers.begin(), allOffers.end(), sortByOfferIdD);
            if(parsedCommand[6] == "offerPrice")
                sort(allOffers.begin(), allOffers.end(), sortByOfferPriceD);
        }
        for(int i = 0; i < allOffers.size(); i++) {
            allOffersStr += allOffers[i].getOfferDataForPrinting() + '\n';
            cout << allOffers[i].getOfferDataForPrinting() << endl; }
        return;
    }
    if(parsedCommand[1] == "getProducts")
    {
        if(parsedCommand.size() != 2)
            throw BadRequestException();
        if(noOneLoggedIn)
            throw PermissionDeniedException();
        allProducts = "productId | productName" + '\n';
        cout << "productId |" << " productName" << endl;
        for (int i = 0; i < products.size(); i++) {
            allProducts += products[i]->getId() + " | " + products[i]->getProductName() + '\n';
            cout << products[i]->getId() << " | " << products[i]->getProductName() << endl;
        }
    }
    if(parsedCommand[1] == "myOffers")
    {
        if(parsedCommand.size() != 2)
            throw BadRequestException();
        if(!sellerLoggedIn)
            throw PermissionDeniedException();
        vector<Offer> sellerOffers = sellers[getSellerIndex(loggedInUserId)].getOffers();
        sort(sellerOffers.begin(), sellerOffers.end(), sortByOfferIdA);
        currentSellerOffers = "productId | offerId | offerUnitPrice | offerAmount" + '\n';
        cout << "productId |" << " offerId |" << " offerUnitPrice |" << " offerAmount" << endl;
        for (int i = 0; i < sellerOffers.size(); i++) {
            currentSellerOffers += sellerOffers[i].getOfferDataForPrinting() + '\n';
            cout << sellerOffers[i].getOfferDataForPrinting() << endl;}
    }
    if(parsedCommand[1] == "wallet")
    {
        if(parsedCommand.size() != 5 || parsedCommand[2] != "?" || parsedCommand[3] != "count")
            throw BadRequestException();
        if(!(sellerLoggedIn || buyerLoggedIn))
            throw PermissionDeniedException();
        if(buyerLoggedIn)
        {
            buyers[getBuyerIndex(loggedInUserId)].printWallet(atoi(parsedCommand[4].c_str()));
            currentBuyerWallet = buyers[getBuyerIndex(loggedInUserId)].getWallet();
        }
        if(sellerLoggedIn)
            sellers[getSellerIndex(loggedInUserId)].printWallet(atoi(parsedCommand[4].c_str()));
        return;
    }
    if(parsedCommand[1] == "offersOnProduct")
    {
        if(parsedCommand.size() != 5 || parsedCommand[2] != "?" || parsedCommand[3] != "productId")
            throw BadRequestException();
        if(!buyerLoggedIn)
            throw PermissionDeniedException();
        if(getProductIndex(atoi(parsedCommand[4].c_str())) == -1)
            throw NotFoundException();
        vector<Offer> productOffers;
        vector<Offer> sellerOffers;
        for(int i = 0; i < sellers.size(); i++)
        {
            sellerOffers.clear();
            sellerOffers = sellers[i].getOffers();
            for(int j = 0; j < sellerOffers.size(); j++)
                if(sellerOffers[j].getProductId() == atoi(parsedCommand[4].c_str()))
                    productOffers.push_back(sellerOffers[j]);
        }
        cout << "productId |" << " productName |" << " offerId |" << " offerUnitPrice |" << " offerAmount" << endl;
        currentProductOffers = "productId | productName | offerId | offerUnitPrice | offerAmount" + '\n';
        for(int i = 0; i < productOffers.size(); i++) {
            cout << productOffers[i].getProductId() << " | " << productOffers[i].getProductName() << " | " <<
                productOffers[i].getOfferId() << " | " << productOffers[i].getOfferUnitPrice() << " | " << productOffers[i].getOfferAmount() << endl;
            currentProductOffers +=  (productOffers[i].getProductId() + " | " + productOffers[i].getProductName() + " | " +
                to_string(productOffers[i].getOfferId()) + " | " + to_string(productOffers[i].getOfferUnitPrice()) + " | " 
                + to_string(productOffers[i].getOfferAmount()) + '\n');
        }
        return;
    }
    if(parsedCommand[1] == "productDetail")
    {
        if(parsedCommand.size() != 5 || parsedCommand[2] != "?" || parsedCommand[3] != "productId")
            throw BadRequestException();
        if(!buyerLoggedIn)
            throw PermissionDeniedException();
        if(getProductIndex(atoi(parsedCommand[4].c_str())) == -1)
            throw NotFoundException();
        currentProductDetails = products[getProductIndex(atoi(parsedCommand[4].c_str()))]->getProductName() + '\n';
        currentProductDetails += products[getProductIndex(atoi(parsedCommand[4].c_str()))]->getProductFeaturesForPrinting() + '\n';
        cout << products[getProductIndex(atoi(parsedCommand[4].c_str()))]->getProductName() << endl;
        cout << products[getProductIndex(atoi(parsedCommand[4].c_str()))]->getProductFeaturesForPrinting() << endl;
        return;
    }
    if(parsedCommand[1] == "comments")
    {
        if(parsedCommand.size() != 5 || parsedCommand[2] != "?" || parsedCommand[3] != "productId")
            throw BadRequestException();
        if(!buyerLoggedIn)
            throw PermissionDeniedException();
        if(getProductIndex(atoi(parsedCommand[4].c_str())) == -1)
            throw NotFoundException();
        products[getProductIndex(atoi(parsedCommand[4].c_str()))]->printProdcutComments();
        return;
    }
    if(parsedCommand[1] == "cart")
    {
        if(parsedCommand.size() != 2)
            throw BadRequestException();
        if(!buyerLoggedIn)
            throw PermissionDeniedException();
        buyers[getBuyerIndex(loggedInUserId)].printCart(buyers[getBuyerIndex(loggedInUserId)].getBuyerCart());
        currentBuyerCart = buyers[getBuyerIndex(loggedInUserId)].getCartForPrinting();
        currentBuyerCartTotalPrice = buyers[getBuyerIndex(loggedInUserId)].getTotalCartPrice();
        return;
    }
    if(parsedCommand[1] == "orders")
    {
        if(parsedCommand.size() != 5 || parsedCommand[2] != "?" || parsedCommand[3] != "count")
            throw BadRequestException();
        if(!buyerLoggedIn)
            throw PermissionDeniedException();
        buyers[getBuyerIndex(loggedInUserId)].printOrders(atoi(parsedCommand[4].c_str()));
        return;
    }
    if(parsedCommand[1] == "compare")
    {
        if(parsedCommand.size() != 7 || parsedCommand[2] != "?" || parsedCommand[3] != "productId1" || parsedCommand[5] != "productId2")
            throw BadRequestException();
        if(!buyerLoggedIn)
            throw PermissionDeniedException();
        if(getProductIndex(atoi(parsedCommand[4].c_str())) == -1 || getProductIndex(atoi(parsedCommand[6].c_str())) == -1)
            throw NotFoundException();
        int product1Index = getProductIndex(atoi(parsedCommand[4].c_str()));
        int product2Index = getProductIndex(atoi(parsedCommand[6].c_str()));
        if(products[product1Index]->getProductType() != products[product2Index]->getProductType())
            throw BadRequestException();
        compareProducts(product1Index, product2Index, products[product1Index]->getProductType());
        return;
    }
    throw NotFoundException();
}

void SiteInterface::compareProducts(int product1Index, int product2Index, string productType)
{
    vector<string> product1Features = products[product1Index]->getProductFeaturesForCompare();
    vector<string> product2Features = products[product2Index]->getProductFeaturesForCompare();
    cout << products[product1Index]->getProductName() << " | " << products[product2Index]->getProductName() << endl;
    if(productType == "mobile")
    {
        cout << "Weight: " << product1Features[0] << " | " << product2Features[0] << endl;
        cout << "CPU Frequency: " << product1Features[1] << " | " << product2Features[1] << endl;
        cout << "RAM: " << product1Features[2] << " | " << product2Features[2] << endl;
        cout << "Display Size: " << product1Features[3] << " | " << product2Features[3] << endl;
        cout << "Camera Resolution: " << product1Features[4] << " | " << product2Features[4] << endl;
        cout << "Operating System: " << product1Features[5] << " | " << product2Features[5] << endl;
    }
    if(productType == "car")
    {
        cout << "Screen Size: " << product1Features[0] << " | " << product2Features[0] << endl;
        cout << "Screen Type: " << product1Features[1] << " | " << product2Features[1] << endl;
        cout << "Resolution: " << product1Features[2] << " | " << product2Features[2] << endl;
        cout << "3D: " << product1Features[3] << " | " << product2Features[3] << endl;
        cout << "HDR: " << product1Features[4] << " | " << product2Features[4] << endl;
    }
    if(productType == "tv")
    {
        cout << "Weight: " << product1Features[0] << " | " << product2Features[0] << endl;
        cout << "Num. of Seats: " << product1Features[1] << " | " << product2Features[1] << endl;
        cout << "Num. of Cylinders: " << product1Features[2] << " | " << product2Features[2] << endl;
        cout << "Engine Capacity: " << product1Features[3] << " | " << product2Features[3] << endl;
        cout << "Reverse Parking Sensors: " << product1Features[4] << " | " << product2Features[4] << endl;
    }
}

void SiteInterface::handleRequest(string request)
{
    try{
        command = request;
        parseCommand();
        if(parsedCommand[0] == "GET")
            executeGetCommand();
        if(parsedCommand[0] == "POST")
            executePostCommand();
    } catch(std::exception& e) {
        throw;
    }
}

void SiteInterface::calcAllUsers()
{
    allUsers.clear();
    for(int i = 0; i < sellers.size(); i++)
        allUsers.push_back(&(sellers[i]));
    for(int j = 0; j < buyers.size(); j++)
        allUsers.push_back(&buyers[j]);
}