#include "siteInterface.hpp"
#include "CommentEvaluatorAI.hpp"

using namespace std;

int main()
{
    SiteInterface interface(PC_FILE_PATH, TRAIN_DATA_FILE_PATH, TEST_DATA_FILE_PATH);
    while(getline(cin, interface.command))
    {
        interface.parsedCommand.clear();
        try{
            interface.parseCommand();
        }
        catch (std::exception& e){
            cerr << e.what() << endl;
            continue;
        }
        try {
            if(interface.parsedCommand[0] == "POST")
                interface.executePostCommand();
            if(interface.parsedCommand[0] == "GET")
                interface.executeGetCommand();  
        }
        catch (std::exception& e){
            cerr << e.what() << endl; 
            continue;
        }
    }
    return 0;
}