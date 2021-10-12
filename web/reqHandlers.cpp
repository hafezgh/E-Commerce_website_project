#include "reqHandlers.hpp"

using namespace std;

std::map<std::string, std::string> HomePage::handle(Request *req) {
    map<string, string> context;
    return context;
}

std::map<std::string, std::string> SignupPage::handle(Request *req) {
    map<string, string> context;
    return context;
}

std::map<std::string, std::string> OfferAddSuccess::handle(Request *req) {
    map<string, string> context;
    return context;
}

std::map<std::string, std::string> CartSubmitted::handle(Request *req) {
    map<string, string> context;
    return context;
}

std::map<std::string, std::string> ChargedSuccess::handle(Request *req) {
    map<string, string> context;
    return context;
}

std::map<std::string, std::string> CartAddSuccess::handle(Request *req) {
    map<string, string> context;
    return context;
}

std::map<std::string, std::string> ProductAddSuccess::handle(Request *req) {
    map<string, string> context;
    return context;
}

std::map<std::string, std::string> BadRequestHandler::handle(Request *req) {
    map<string, string> context;
    return context;
}

std::map<std::string, std::string> PasswordsNotSameHandler::handle(Request *req) {
    map<string, string> context;
    return context;
}

std::map<std::string, std::string> NotFoundHandler::handle(Request *req) {
    map<string, string> context;
    return context;
}

std::map<std::string, std::string> NoPermissionHandler::handle(Request *req) {
    map<string, string> context;
    return context;
}

std::map<std::string, std::string> EmptyFieldHandler::handle(Request *req) {
    map<string, string> context;
    return context;
}

std::map<std::string, std::string> UserNameExistsHandler::handle(Request *req) {
    map<string, string> context;
    return context;
}

std::map<std::string, std::string> EmailExistsHandler::handle(Request *req) {
    map<string, string> context;
    return context;
}

std::map<std::string, std::string> IncorrectEmailOrPassHandler::handle(Request *req) {
    map<string, string> context;
    return context;
}

std::map<std::string, std::string> NoOneLoggedIn::handle(Request *req) {
    map<string, string> context;
    return context;
}

Response *SignupHandler::callback(Request *req) {
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");
    string retypedPassword = req->getBodyParam("retypedPassword");
    string email = req->getBodyParam("email");
    string usertype = req->getBodyParam("usertype");
    Response* res = Response::redirect("/signup");
    try {
        if(password != retypedPassword){
            throw PasswordsDoNotMatchException();}
        else
        {
            if(username == "" || password == "" || email == "")
                throw EmptyFieldsException();
            string request= "POST signup ? email " + email + " username " + username + " password " + password + " type " + usertype;
            siteUI->handleRequest(request);
            request = "POST login ? email " + email + " password " + password;
            siteUI->handleRequest(request);
            res = Response::redirect("/" + usertype + "home" + "?user=" + username);
            res->setSessionId(username);
        }
    } catch (std::exception& e){
            cerr << e.what() << endl;
            string s = e.what();
            s.erase(remove(s.begin(), s.end(), ' '), s.end());;
            return Response::redirect("/" + s);
        }
    return res;
}

std::map<std::string, std::string> LoginPage::handle(Request *req) {
    map<string, string> context;
    return context;
}

Response *LoginHandler::callback(Request *req) {
    string email = req->getBodyParam("email");
    string password = req->getBodyParam("password");
    Response *res;
    string request = "POST login ? email " + email + " password " + password;
    try {
        if(email == "" || password == "")
            throw EmptyFieldsException();
        siteUI->handleRequest(request);
        siteUI->calcAllUsers();
        string username;
        vector<User*> users = siteUI->getAllUsers();
        for(int i = 0; i < users.size(); i++)
            if(users[i]->getEmail() == email)
                username = users[i]->getUserName();
        if(siteUI->getAdminLoginStatus())
            res = Response::redirect("/adminhome");
        else if(siteUI->getBuyerLoginStatus())
                res = Response::redirect("/buyerhome?user=" + username);
            else if(siteUI->getSellerLoginStatus())
                    res = Response::redirect("/sellerhome?user=" + username);
        if(username != siteUI->getAdminUsername())
            res->setSessionId(username);
        else
            res->setSessionId(siteUI->getAdminUsername());
    } catch(exception &e) {
            cerr << e.what() << endl;
            string s = e.what();
            s.erase(remove(s.begin(), s.end(), ' '), s.end());;
            return Response::redirect("/" + s);
        }
    return res;
}

std::map<std::string, std::string> AdminHome::handle(Request *req) {
    map<string, string> context;
    try {
        if(siteUI->getAdminUsername() != req->getSessionId())
            throw PermissionDeniedException();
        return context;
    } catch(exception &e)
    {
        cerr << e.what() << endl;
        string s = e.what();
        throw Server::Exception(e.what());
    }
}

std::map<std::string, std::string> BuyerHome::handle(Request *req) {
    string loggedInUsername = req->getSessionId();
    Response* res;
    try {
        if(loggedInUsername != req->getSessionId() || siteUI->getBuyerLoginStatus() == false)
            throw PermissionDeniedException();
        siteUI->handleRequest("GET getProducts");
        string allProducts = siteUI->getAllProdects();
        map<string, string> context;
        istringstream split(allProducts);
        string line;
        int lineCounter = 0;
        while( getline(split,line) )
        {
            if(lineCounter == 0)
                context["listheader"] = line;
            else
                context["product" + to_string(lineCounter)]=line;
            lineCounter++;
        }
        context["buyerName"] = req->getQueryParam("user");
        return context;
    } catch(exception &e) {
            cerr << e.what() << endl;
            string s = e.what();
            throw Server::Exception(e.what());
        }
}


std::map<std::string, std::string> SellerHome::handle(Request *req) {
    string loggedInUsername = req->getSessionId();
    try {
        if(loggedInUsername != req->getSessionId() || siteUI->getSellerLoginStatus() == false)
            throw PermissionDeniedException();
        siteUI->handleRequest("GET myOffers");
        map<string, string> context;
        string offers = siteUI->getCurrentSellerOffers();
        istringstream spliter(offers);
        string line;
        int lineCounter = 0;
        while(getline(spliter, line))
        {
            if(lineCounter == 0)
            {
                lineCounter++;
                continue;
            }
            else
            {
                vector<string> tmp = split(line, "|", true);
                context["offers" + to_string(lineCounter) + "-productid"] = tmp[0];
                context["offers" + to_string(lineCounter) + "-offerid"] = tmp[1];
                context["offers" + to_string(lineCounter) + "-offerunitprice"] = tmp[2];
                context["offers" + to_string(lineCounter) + "-offeramount"] = tmp[3];
                lineCounter++;
            }
        }
        context["sellerName"]=req->getQueryParam("user");
        return context;
    } catch(exception &e) {
            cerr << e.what() << endl;
            string s = e.what();
            throw Server::Exception(e.what());
        }
}



Response *LogoutHandler::callback(Request *req) {
    try {
        string loggedInUser = siteUI->getLoggedInUsername();
        if(loggedInUser == "siteUI")
            throw PermissionDeniedException();
        siteUI->handleRequest("POST logout");
        Response* res=Response::redirect("/");
        res->setSessionId("");
        return res;
    } catch(exception &e) {
            cerr << e.what() << endl;
            string s = e.what();
            s.erase(remove(s.begin(), s.end(), ' '), s.end());;
            return Response::redirect("/" + s);
        }
}


std::map<std::string, std::string> SeeAllOffers::handle(Request *req) {
    try {
        if(req->getSessionId() != ADMIN_USER)
            throw PermissionDeniedException();
        siteUI->handleRequest("GET offers ? order " + req->getBodyParam("order") + " field " + req->getBodyParam("field"));
        map<string, string> context;
        string allOffers = siteUI->getAllOffersStr();
        istringstream splitoffers(allOffers);
        string line;
        int lineCounter = 0;
        while(getline(splitoffers,line))
        {
            if(lineCounter == 0)
                context["listheader"]=line;
            else
            {
                vector<string> tmp = split(line, "|", false);
                context["alloffers" + to_string(lineCounter) + "-productid"] = tmp[0];
                context["alloffers" + to_string(lineCounter) + "-offerid"] = tmp[1];
                context["alloffers" + to_string(lineCounter) + "-unitprice"] = tmp[2];
                context["alloffers" + to_string(lineCounter) + "-amount"] = tmp[3];
            }
            lineCounter++;
        }
        return context;
    } catch(exception &e) {
            cerr << e.what() << endl;
            string s = e.what();
            throw Server::Exception(e.what());
        }
}


Response* ImportProductsFromFile::callback(Request *req) {
    try{
        if(req->getSessionId() != ADMIN_USER)
            throw PermissionDeniedException();
        string request = "POST importProducts ? type " + req->getBodyParam("producttype") + " filePath " + req->getBodyParam("fileName");
        siteUI->handleRequest(request);
        Response* res;
        throw Server::Exception("Products added successfully!");
        return res;
    } catch(exception &e) {
            cerr << e.what() << endl;
            string s = e.what();
            throw Server::Exception(e.what());
        }
}

std::map<std::string, std::string> MakeOfferPage::handle(Request *req) {
    string loggedInUsername = req->getSessionId();
    try {
        if(loggedInUsername != req->getSessionId() || siteUI->getSellerLoginStatus() == false)
            throw PermissionDeniedException();
        string allproducts;
        siteUI->handleRequest("GET getProducts");
        allproducts = siteUI->getAllProdects();
        map<string, string> context;
        istringstream splitter(allproducts);
        string line;
        int lineCounter = 0;
        while(getline(splitter,line))
        {
            if(lineCounter == 0)
            {
                lineCounter++;
                continue;
            }
            else
            {
                vector<string> tmp = split(line, "|", true);
                context["allproducts" + to_string(lineCounter) + "-id"] = tmp[0];
                context["allproducts" + to_string(lineCounter) + "-name"] = tmp[1];
            }
            lineCounter++;
        }
        return context;
    } catch(exception &e) {
            cerr << e.what() << endl;
            string s = e.what();
            throw Server::Exception(e.what());
        }
}


Response* HandleMakeOffer::callback(Request *req) {
    string loggedInUsername = req->getSessionId();
    try {
        if(loggedInUsername != req->getSessionId() || siteUI->getSellerLoginStatus() == false)
            throw PermissionDeniedException();
        string productid=req->getBodyParam("productid");
        string offerunitprice=req->getBodyParam("offerunitprice");
        string offeramount=req->getBodyParam("offeramount");
        Response* res;
        if(stod(offerunitprice) > 0.0 && stoi(offeramount) > 0)
        {
            string request = "POST offer ? productId " + productid + " offerUnitPrice " + offerunitprice + " offerAmount " + offeramount;
            siteUI->handleRequest(request);
        }
        else
            throw BadRequestException();
        throw Server::Exception("Offer added successfully!");
        return res;
    } catch(exception &e) {
            cerr << e.what() << endl;
            string s = e.what();
            throw Server::Exception(e.what());
        }
}

std::map<std::string, std::string> ProductDetailsPage::handle(Request *req) 
{
    string loggedInUsername = siteUI->getLoggedInUsername();
    try {
        if(loggedInUsername != req->getSessionId() || siteUI->getBuyerLoginStatus() == false)
            throw PermissionDeniedException();
        productId = req->getQueryParam("productid");
        string productDetails;
        siteUI->handleRequest("GET productDetail ? productId " + productId);
        productDetails = siteUI->getCurrentProductDetails();
        map<string, string> context;
        context["productid"] = productId;
        istringstream splitDetails(productDetails);
        string line;
        int lineCounter = 0;
        while(getline(splitDetails, line))
        {
            if(lineCounter == 0)
                context["productname"]=line;
            else
            {
                vector<string> tmp=split(line, ":", true);
                context["feature" + to_string(lineCounter) + "-name"] = tmp[0];
                context["feature" + to_string(lineCounter) + "-value"] = tmp[1];
            }
            lineCounter++;
        }
        string productOffers;
        siteUI->handleRequest("GET offersOnProduct ? productId " + productId);
        productOffers = siteUI->getCurrentProductOffers();
        istringstream splitOffers(productOffers);
        lineCounter = 0;
        while(getline(splitOffers, line))
        {
            int firstpartIndex = line.find("|");
            int secondpartIndex = line.find("|", firstpartIndex + 1);
            line = line.substr(secondpartIndex + 2);
            if(lineCounter == 0)
                context["listheader"] = line;
            else
            {
                vector<string> tmp = split(line, "|", true);
                context["offer" + to_string(lineCounter) + "-offerid"] = tmp[0];
                context["offer" + to_string(lineCounter) + "-unitprice"] = tmp[1];
                context["offer" + to_string(lineCounter) + "-amount"] = tmp[2];
            }
            lineCounter++;
        }
        return context;
    } catch(exception &e) {
            cerr << e.what() << endl;
            string s = e.what();
            throw Server::Exception(e.what());
        }
}

Response* HandleAddToCart::callback(Request *req) {
    string loggedInUsername = siteUI->getLoggedInUsername();
    try {
        if(loggedInUsername != req->getSessionId() || siteUI->getBuyerLoginStatus() == false)
            throw PermissionDeniedException();
        Response* res;
        siteUI->handleRequest("POST addToCart ? offerId " + req->getBodyParam("offerid") + " amount " + req->getBodyParam("amount"));
        throw Server::Exception("Added to cart successfully!");
        return res;
    } catch(exception &e) {
            cerr << e.what() << endl;
            string s = e.what();
            throw Server::Exception(e.what());
        }
}

std::map<std::string, std::string> CartPage::handle(Request *req) {
    string loggedInUsername = siteUI->getLoggedInUsername();
    try {
        if(loggedInUsername != req->getSessionId() || siteUI->getBuyerLoginStatus() == false)
            throw PermissionDeniedException();
        string cart; 
        siteUI->handleRequest("GET cart");
        cart = siteUI->getCurrentBuyerCart();
        map<string, string> context;
        istringstream splitter(cart);
        string line;
        int lineCounter = 0;
        while(getline(splitter,line))
        {
            if(lineCounter == 0)
                context["carttitle"] = line;
            else
            {
                vector<string> tmp = split(line, "|", true);
                context["order" + to_string(lineCounter) + "-productid"] = tmp[0];
                context["order" + to_string(lineCounter) + "-productname"] = tmp[1];
                context["order" + to_string(lineCounter) + "-offerid"] = tmp[2];
                context["order" + to_string(lineCounter) + "-sellerid"] = tmp[3];
                context["order" + to_string(lineCounter) + "-totalprice"] = tmp[4];
                context["order" + to_string(lineCounter) + "-amount"] = tmp[5];
            }
            lineCounter++;
        }
        context["cartcost"] = to_string(siteUI->getCurrentBuyerTotalCartPrice());
        return context;
    } catch(exception &e) {
            cerr << e.what() << endl;
            string s = e.what();
            throw Server::Exception(e.what());
        }
}

Response* SubmitCartHandler::callback(Request *req) {
    string loggedInUsername = siteUI->getLoggedInUsername();
    try {
        if(loggedInUsername != req->getSessionId() || siteUI->getBuyerLoginStatus() == false)
            throw PermissionDeniedException();
        Response* res;
        siteUI->handleRequest("POST submitCart");
        res=Response::redirect("/buyerhome/cartsubmitted");
        return res;
    } catch(exception &e) {
            cerr << e.what() << endl;
            string s = e.what();
            throw Server::Exception(e.what());
        }
}

std::map<std::string, std::string> WalletPage::handle(Request *req) {
    string loggedInUsername = siteUI->getLoggedInUsername();
    try {
        if(loggedInUsername != req->getSessionId() || siteUI->getBuyerLoginStatus() == false)
            throw PermissionDeniedException();
        siteUI->handleRequest("GET wallet ? count 1");
        string wallet = siteUI->getCurrentBuyerWallet();
        map<string, string> context;
        istringstream split(wallet);
        string line;
        int lineCounter = 0;
        while(getline(split, line))
        {
            if(lineCounter == 0)
                context["listheader"] = line;
            else
                context["credit" + to_string(lineCounter)] = line;
            lineCounter++;
        }
        return context;
    } catch(exception &e) {
            cerr << e.what() << endl;
            string s = e.what();
            throw Server::Exception(e.what());
        }
}

Response* ChargeWallet::callback(Request *req) {
    string loggedInUsername = siteUI->getLoggedInUsername();
    try {
        if(loggedInUsername != req->getSessionId() || siteUI->getBuyerLoginStatus() == false)
            throw PermissionDeniedException();
        Response* res;
        siteUI->handleRequest("POST chargeWallet ? amount " + req->getBodyParam("amount"));
        throw Server::Exception("Wallet charged successfully!");
        return res;
    } catch(exception &e) {
            cerr << e.what() << endl;
            string s = e.what();
            throw Server::Exception(e.what());
        }
}
