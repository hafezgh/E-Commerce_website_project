#include "domainAndAI/siteInterface.hpp"
#include "reqHandlers.hpp"
#include "myServer.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

int main()
{
    try {
        SiteInterface* siteUI = new SiteInterface(PC_FILE_PATH, TRAIN_DATA_FILE_PATH, TEST_DATA_FILE_PATH);
        MyServer server(5000);
        server.setNotFoundErrPage("static/404.html");
        server.get("/", new HomePage("dynamic/home.html"));
        server.get("/signup", new SignupPage("dynamic/signup.html"));
        server.post("/signup", new SignupHandler(siteUI));
        server.get("/login", new LoginPage("dynamic/login.html"));
        server.get("/BadRequest", new BadRequestHandler("static/badrequest.html"));
        server.get("/Passwordsdonotmatch!", new PasswordsNotSameHandler("static/passwordsnotsame.html"));
        server.get("/NotFound!", new NotFoundHandler("static/notfound.html"));
        server.get("/PermissionDenied!", new NoPermissionHandler("static/permissiondenied.html"));
        server.get("/Youdidnotfilloneoftherequiredfields!", new EmptyFieldHandler("static/emptyfield.html"));
        server.get("/Usernamealreadyexists!", new UserNameExistsHandler("static/usernameexists.html"));
        server.get("/Emailalreadyexists!", new EmailExistsHandler("static/emailexists.html"));
        server.get("/Incorrectemailorpassword!", new IncorrectEmailOrPassHandler("static/incorrectemailorpass.html"));
        server.get("/Nooneisloggedin!", new NoOneLoggedIn("static/nooneloggedin.html"));
        server.post("/login", new LoginHandler(siteUI));
        server.get("/adminhome", new AdminHome(siteUI, "dynamic/adminhome.html"));
        server.get("/buyerhome", new BuyerHome(siteUI, "dynamic/buyerhome.html"));
        server.get("/sellerhome", new SellerHome(siteUI, "dynamic/sellerhome.html"));
        server.get("/alloffers", new SeeAllOffers(siteUI, "dynamic/alloffers.html"));      
        server.post("/adminhome", new ImportProductsFromFile(siteUI));
        server.post("/offer", new HandleMakeOffer(siteUI));
        server.get("/offer", new MakeOfferPage(siteUI, "dynamic/makeoffer.html"));
        server.get("/productdetail", new ProductDetailsPage(siteUI, "dynamic/productdetails.html"));
        server.get("/buyerhome/cartsubmitted", new CartSubmitted("static/cartsubmitted.html"));
        server.post("/addproducttocart", new HandleAddToCart(siteUI));
        server.get("/cartpage", new CartPage(siteUI, "dynamic/cartpage.html"));
        server.post("/submitcart", new SubmitCartHandler(siteUI));
        server.get("/buyerhome/chargedsuccess", new ChargedSuccess("static/chargedsuccess.html"));
        server.get("/wallet", new WalletPage(siteUI, "dynamic/getwallet.html"));
        server.post("/chargewallet", new ChargeWallet(siteUI));
        server.run();
    } 
    catch (Server::Exception e) {
        Server::Exception eTmp("Failed to run the server!\n");
        cerr << eTmp.getMessage() << endl;
        return 0;
    }
}