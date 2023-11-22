#define CATCH_CONFIG_RUNNER
#include "..\\catch.hpp"
#include "thpef.h"
#include "ourDate.h"

const bool RUNCATCH = true;

int main( int argc, char **argv )
{
    Catch::Session session;
    int result;
    
    if( RUNCATCH )
    {
        result = session.run();
        if( result != 0 )
        {
            cout << "Test cases didn't pass." << endl;
            return result;
        }
    }
    

    transactionData record = {"", "", "", "", "", "", 0, 0};
    if ( argc == 5 )
    {
        ifstream inputFile (argv[1], fstream::in);
        
        if(inputFile.is_open() == false)
        {
            cout << "Unable to open the input file: " << argv[2] << endl;
            return 0;
        }
        
        while(inputFile.good() == true)
        {
            if(getClient(&inputFile, &record) )
            {
                record.currentBalance += record.transAmount;
                if(record.transAmount > 0)
                {
                    writeLetter(record, argv[2], getDate());
                }
                else if(record.transAmount < 0)
                {
                    record.transAmount = abs(record.transAmount);
                    writeLetter(record, argv[3], getDate() );
                }
                else if(record.transAmount == 0 && record.currentBalance != 0 )
                {
                    writeLetter(record, argv[4], getDate() );
                }
                
                    
            }
           
        }
        inputFile.close();
    }
    else
    {
        cout << "Usage: thpef.exe datafile template1 template2 template3" << endl;
        cout << "       datafile --name of input data file" << endl;
        cout << "       template1 --name of purchase template file" << endl;
        cout << "       template2 --name of payment template file" << endl;
        cout << "       template3 --name of overdue template file" << endl;
        return 0;
    }
    
    return 0;
}

TEST_CASE("getClient - matches expected")
{
    istringstream ss("Heidi,Anderson,2801 S. West Ave,Sioux Falls,SD,57105,64.43,1201.67\n");
    transactionData record = {"", "", "", "", "", "", 0, 0};
    
    getClient(&ss, &record);
    
    REQUIRE(record.firstName == "Heidi");
    REQUIRE(record.lastName == "Anderson");
    REQUIRE(record.streetAddress == "2801 S. West Ave");
    REQUIRE(record.city == "Sioux Falls");
    REQUIRE(record.state == "SD");
    REQUIRE(record.zipCode == "57105");
}

TEST_CASE("getClient - matches expected again")
{
    istringstream ss("Olivia,Stelzer,207 E. Saint Joseph St.,Rapid City,SD,57701,-124.34, 0\n");
    transactionData record = {"", "", "", "", "", "", 0, 0};
    
    getClient(&ss, &record);
    
    REQUIRE(record.firstName == "Olivia");
    REQUIRE(record.lastName == "Stelzer");
    REQUIRE(record.streetAddress == "207 E. Saint Joseph St.");
    REQUIRE(record.city == "Rapid City");
    REQUIRE(record.state == "SD");
    REQUIRE(record.zipCode == "57701");
}

TEST_CASE("getDate - checking output")
{
    string ans = getDate();
    
    REQUIRE(ans == "25 Dec, 2021");
}

TEST_CASE("writeLetter - matches expected")
{
    string templateFile = "template2";
    string currentDate = getDate();
    istringstream ss("Olivia,Stelzer,207 E. Saint Joseph St.,Rapid City,SD,57701,-124.34, 0\n");
    transactionData record = {"", "", "", "", "", "", 0, 0};
    
    getClient(&ss, &record);
    
    REQUIRE(record.firstName == "Olivia");
    REQUIRE(record.lastName == "Stelzer");
    REQUIRE(record.streetAddress == "207 E. Saint Joseph St.");
    REQUIRE(record.city == "Rapid City");
    REQUIRE(record.state == "SD");
    REQUIRE(record.zipCode == "57701");
}
    