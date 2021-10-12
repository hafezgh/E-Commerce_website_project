#include <iostream>
#include <string>
#include "domainAndAI/exceptions.hpp"

using namespace std;

int main()
{
    try {
        throw BadRequestException();
    } catch(exception& e)
    {
        cerr << e.what() << endl;
        string s = e.what(); 
        cout << s << endl;
    }
    return 0;
}