#ifndef _HANDLERS_
#define _HANDLERS_

#include "../APHTTP/server/server.hpp"
#include "domainAndAI/siteInterface.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

class HomePage : public TemplateHandler {
public:
    HomePage(std::string _path) : TemplateHandler(_path) {} ;
    std::map<std::string, std::string> handle(Request *req);
};

class SignupPage : public TemplateHandler {
public:
    SignupPage(std::string _path) : TemplateHandler(_path) {} ;
    std::map<std::string, std::string> handle(Request *req);
};

class SignupHandler : public RequestHandler {
    SiteInterface* siteUI;
public:
    SignupHandler(SiteInterface* _siteUI) : siteUI(_siteUI) {} ;
    Response *callback(Request *);
};

class LoginPage : public TemplateHandler {
public:
    LoginPage(std::string _path) : TemplateHandler(_path) {} ;
    std::map<std::string, std::string> handle(Request *req);
};

class BadRequestHandler : public TemplateHandler {
public:
    BadRequestHandler(std::string _path) : TemplateHandler(_path) {} ;
    std::map<std::string, std::string> handle(Request *req);
};

class PasswordsNotSameHandler : public TemplateHandler {
public:
    PasswordsNotSameHandler(std::string _path) : TemplateHandler(_path) {} ;
    std::map<std::string, std::string> handle(Request *req);
};

class NotFoundHandler : public TemplateHandler {
public:
    NotFoundHandler(std::string _path) : TemplateHandler(_path) {} ;
    std::map<std::string, std::string> handle(Request *req);
};

class NoPermissionHandler : public TemplateHandler {
public:
    NoPermissionHandler(std::string _path) : TemplateHandler(_path) {} ;
    std::map<std::string, std::string> handle(Request *req);
};

class EmptyFieldHandler : public TemplateHandler {
public:
    EmptyFieldHandler(std::string _path) : TemplateHandler(_path) {} ;
    std::map<std::string, std::string> handle(Request *req);
};

class UserNameExistsHandler : public TemplateHandler {
public:
    UserNameExistsHandler(std::string _path) : TemplateHandler(_path) {} ;
    std::map<std::string, std::string> handle(Request *req);
};

class EmailExistsHandler : public TemplateHandler {
public:
    EmailExistsHandler(std::string _path) : TemplateHandler(_path) {} ;
    std::map<std::string, std::string> handle(Request *req);
};

class IncorrectEmailOrPassHandler : public TemplateHandler {
public:
    IncorrectEmailOrPassHandler(std::string _path) : TemplateHandler(_path) {} ;
    std::map<std::string, std::string> handle(Request *req);
};

class NoOneLoggedIn : public TemplateHandler {
public:
    NoOneLoggedIn(std::string _path) : TemplateHandler(_path) {} ;
    std::map<std::string, std::string> handle(Request *req);
};

class ProductAddSuccess : public TemplateHandler {
public:
    ProductAddSuccess(std::string _path) : TemplateHandler(_path) {} ;
    std::map<std::string, std::string> handle(Request *req);
};

class CartAddSuccess : public TemplateHandler {
public:
    CartAddSuccess(std::string _path) : TemplateHandler(_path) {} ;
    std::map<std::string, std::string> handle(Request *req);
};

class OfferAddSuccess : public TemplateHandler {
public:
    OfferAddSuccess(std::string _path) : TemplateHandler(_path) {} ;
    std::map<std::string, std::string> handle(Request *req);
};

class ChargedSuccess : public TemplateHandler {
public:
    ChargedSuccess(std::string _path) : TemplateHandler(_path) {} ;
    std::map<std::string, std::string> handle(Request *req);
};

class SeeAllOffers : public TemplateHandler {
    SiteInterface* siteUI;
public:
    SeeAllOffers(SiteInterface* _siteUI, std::string _path) : TemplateHandler(_path), siteUI(_siteUI) {} ;
    std::map<std::string, std::string> handle(Request *req);
};

class CartSubmitted : public TemplateHandler {
public:
    CartSubmitted(std::string _path) : TemplateHandler(_path) {} ;
    std::map<std::string, std::string> handle(Request *req);
};


class MakeOfferPage : public TemplateHandler {
    SiteInterface* siteUI;
public:
    MakeOfferPage(SiteInterface* _siteUI, std::string _path) : TemplateHandler(_path), siteUI(_siteUI) {} ;
    std::map<std::string, std::string> handle(Request *req);
};

class LoginHandler : public RequestHandler {
    SiteInterface* siteUI;
public:
    LoginHandler(SiteInterface* _siteUI) : siteUI(_siteUI) {} ;
    Response *callback(Request *);
};

class ImportProductsFromFile : public RequestHandler {
    SiteInterface* siteUI;
public:
    ImportProductsFromFile(SiteInterface* _siteUI) : siteUI(_siteUI) {} ;
    Response *callback(Request *);
};

class HandleMakeOffer : public RequestHandler {
    SiteInterface* siteUI;
public:
    HandleMakeOffer(SiteInterface* _siteUI) : siteUI(_siteUI) {} ;
    Response *callback(Request *);
};

class LogoutHandler : public RequestHandler {
    SiteInterface* siteUI;
public:
    LogoutHandler(SiteInterface* _siteUI, std::string path_) : siteUI(_siteUI) {} ;
    Response *callback(Request *);
};

class SellerHome : public TemplateHandler {
    SiteInterface* siteUI;
public:
    SellerHome(SiteInterface* _siteUI, std::string _path) : TemplateHandler(_path), siteUI(_siteUI) {} ;
    std::map<std::string, std::string> handle(Request *req);
};

class BuyerHome : public TemplateHandler {
    SiteInterface* siteUI;
public:
    BuyerHome(SiteInterface* _siteUI, std::string _path) : TemplateHandler(_path), siteUI(_siteUI) {} ;
    std::map<std::string, std::string> handle(Request *req);
};


class AdminHome : public TemplateHandler {
    SiteInterface* siteUI;
public:
    AdminHome(SiteInterface* _siteUI, std::string path_) : TemplateHandler(path_), siteUI(_siteUI) {} ;
    std::map<std::string, std::string> handle(Request *req);
};

class ProductDetailsPage : public TemplateHandler {
    SiteInterface* siteUI;
    std::string productId;
public:
    ProductDetailsPage(SiteInterface* _siteUI, std::string _path) : TemplateHandler(_path), siteUI(_siteUI) {} ;
    std::map<std::string, std::string> handle(Request *req);
};

class HandleAddToCart : public RequestHandler {
    SiteInterface* siteUI;
    std::string productId;
public:
    HandleAddToCart(SiteInterface* _siteUI) : siteUI(_siteUI) {};
    Response* callback(Request *);
};

class CartPage : public TemplateHandler {
    SiteInterface* siteUI;
public:
    CartPage(SiteInterface* _siteUI, std::string _path) : TemplateHandler(_path), siteUI(_siteUI) {} ;
    std::map<std::string, std::string> handle(Request *req);
};

class SubmitCartHandler : public RequestHandler {
    SiteInterface* siteUI;
public:
    SubmitCartHandler(SiteInterface* _siteUI) : siteUI(_siteUI) {};
    Response* callback(Request *);
};

class ChargeWallet : public RequestHandler {
    SiteInterface* siteUI;
public:
    ChargeWallet(SiteInterface* _siteUI) : siteUI(_siteUI) {};
    Response* callback(Request *);
};

class WalletPage : public TemplateHandler {
    SiteInterface* siteUI;
public:
    WalletPage(SiteInterface* _siteUI, std::string _path) : TemplateHandler(_path), siteUI(_siteUI) {} ;
    std::map<std::string, std::string> handle(Request *req);
};

/*
class LogoutHandler : public RequestHandler {
    Bazar* bazar;
public:
    LogoutHandler(Bazar* bazar_) : bazar(bazar_) {} ;
    Response *callback(Request *);
};

class ShowManagerHome : public TemplateHandler {
    Bazar* bazar;
public:
    ShowManagerHome(Bazar* bazar_,std::string path_) : TemplateHandler(path_), bazar(bazar_) {} ;
    std::map<std::string, std::string> handle(Request *req);
};

class ImportProducts : public RequestHandler {
    Bazar* bazar;
public:
    ImportProducts(Bazar* bazar_) : bazar(bazar_) {};
    Response* callback(Request *);
};

class PrintAllOffers : public TemplateHandler {
    Bazar* bazar;
fublic:
    PrintAllOffers(Bazar* bazar_,std::string path_) : TemplateHandler(path_), bazar(bazar_) {} ;
    std::map<std::string, std::string> handle(Request *req);
};



class ShowSetOfferPage : public TemplateHandler {
    Bazar* bazar;
public:
    ShowSetOfferPage(Bazar* bazar_,std::string path_) : TemplateHandler(path_), bazar(bazar_) {} ;
    std::map<std::string, std::string> handle(Request *req);
};

class SetOffer : public RequestHandler {
    Bazar* bazar;
public:
    SetOffer(Bazar* bazar_) : bazar(bazar_) {};
    Response* callback(Request *);
};

;


class AddToCart : public RequestHandler {
    Bazar* bazar;
    std::string productid;
public:
    AddToCart(Bazar* bazar_) : bazar(bazar_) {};
    Response* callback(Request *);
};

class GetCart : public TemplateHandler {
    Bazar* bazar;
public:
    GetCart(Bazar* bazar_, std::string path_) : TemplateHandler(path_), bazar(bazar_) {} ;
    std::map<std::string, std::string> handle(Request *req);
};

class SubmitCart : public RequestHandler {
    Bazar* bazar;
public:
    SubmitCart(Bazar* bazar_) : bazar(bazar_) {};
    Response* callback(Request *);
};

class GetWallet : public TemplateHandler {
    Bazar* bazar;
public:
    GetWallet(Bazar* bazar_, std::string path_) : TemplateHandler(path_), bazar(bazar_) {} ;
    std::map<std::string, std::string> handle(Request *req);
};

class ChargeWallet : public RequestHandler {
    Bazar* bazar;
public:
    ChargeWallet(Bazar* bazar_) : bazar(bazar_) {};
    Response* callback(Request *);
};

class AddComment : public RequestHandler {
    Bazar* bazar;
public:
    AddComment(Bazar* bazar_) : bazar(bazar_) {};
    Response* callback(Request *);
};*/



#endif
