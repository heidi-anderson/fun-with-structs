/** **********************************************************************
 * @file thpe2
 ************************************************************************/
#include "thpef.h"
#include "ourDate.h"

using namespace std;
/** **********************************************************************
 *  @author Heidi Anderson
 *
 *  @par Description
 *  This function replaces strings with the data needed.
 *
 *  @param[str] data
 *  @param[str] search
 *  @param[int] length
 *  @param[str] replacement
 *              
 *
 *  @returns data that was replaced
 *
 *  @par Example
 *  @verbatim

    readLine = replace( readLine, "#CITY", 5, record.city );
    
    returns whatever the city is in the data set.

    @endverbatim
 ************************************************************************/
string replace ( string data, string search, int len, string replacement )
{
   string::size_type pos;
   
    pos = data.find( search );
    if( pos != string::npos )
    {
        data.replace(pos, len, replacement);
    } 

    return data;
}

string currency( double value )
{
    ostringstream myStream;
    
    myStream << fixed << setprecision(2) << value;
    
    return myStream.str();
}
/** **********************************************************************
 *  @author Heidi Anderson
 *
 *  @par Description
 *  This function will write a letter based on the data set given
 *
 *  @param[struct] record
 *  @param[str] templateFile
 *  @param[str] currentDate
 *              
 *
 *  @returns nothing
 *
 *  @par Example
 *  @verbatim

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

    @endverbatim
 ************************************************************************/
void writeLetter( transactionData record, string templateFile, string currentDate )
{
    string readLine;
    ifstream inputFile (templateFile, fstream::in);
    ofstream outputFile (record.firstName + "." + record.lastName + ".txt", fstream::out);
    
    if( inputFile.is_open() == false )
    {
        cout << "Unable to open the template file: " << templateFile << endl;
        if(outputFile.is_open())
        {
            outputFile.close();
        }
        return;
    }   
    else if( outputFile.is_open() == false )
    {
        cout << "Unable to open the output file: " << record.firstName + "." + record.lastName + ".txt" << endl;
        return;
    }
    
    while(inputFile.good() == true)
    {
        
        if( getline( inputFile, readLine ) )
        {
            readLine = replace( readLine, "#FULLNAME", 9, record.firstName + " " + record.lastName );
            readLine = replace( readLine, "#ADDRESS", 8, record.streetAddress );
            readLine = replace( readLine, "#CITY", 5, record.city );
            readLine = replace( readLine, "#STATE", 6, record.state );
            readLine = replace( readLine, "#ZIP", 4, record.zipCode ); 
            readLine = replace( readLine, "#FIRST", 6, record.firstName );    
            readLine = replace( readLine, "#LAST", 5, record.lastName );
            readLine = replace( readLine, "#DATE", 5, currentDate );   
            readLine = replace( readLine, "#TRANSACTION", 12, currency( record.transAmount ) ); 
            readLine = replace( readLine, "#BALANCE", 8, currency( record.currentBalance ) );        
            outputFile << readLine << endl;
        }
        
    }
    
    inputFile.close();
    outputFile.close();
}
/** **********************************************************************
 *  @author Heidi Anderson
 *
 *  @par Description
 *  Given an opened input file stream and a customer record to be filled in
 *  this function will read a line from the input file and fill the fields
 *  of the record.
 *
 *  @param[istr] inputFile
 *  @param[struct] record
 *              
 *
 *  @returns true on success, false if no data is read
 *
 *  @par Example
 *  @verbatim

    istringstream ss("Heidi,Anderson,2801 S. West Ave,Sioux Falls,SD,57105,64.43,1201.67\n");
    transactionData record = {"", "", "", "", "", "", 0, 0};
    
    getClient(&ss, &record);
    
    REQUIRE(record.firstName == "Heidi");
    REQUIRE(record.lastName == "Anderson");
    REQUIRE(record.streetAddress == "2801 S. West Ave");
    REQUIRE(record.city == "Sioux Falls");
    REQUIRE(record.state == "SD");
    REQUIRE(record.zipCode == "57105");

    @endverbatim
 ************************************************************************/
bool getClient( istream *inputFile, transactionData *record )
{
    int j = 0;
    string readLine;
    if( getline(*inputFile, readLine) )
    {
        istringstream commaLine(readLine);
        while(getline(commaLine, readLine, ','))
        {
            switch(j)
            {
                case 0:
                    record->firstName = readLine;
                    break;
                case 1:
                    record->lastName = readLine;
                    break;
                case 2:
                    record->streetAddress = readLine;
                    break;
                case 3:
                    record->city = readLine;
                    break;
                case 4:
                    record->state = readLine;
                    break;
                case 5:
                    record->zipCode = readLine;
                    break;                        
                case 6:
                    record->transAmount = stod(readLine);
                    break;
                case 7:
                    record->currentBalance = stod(readLine);
                    break;
            }
                    
            j++;
        }
        return j == 8;
    }
    return false;
}
/** **********************************************************************
 *  @author Heidi Anderson
 *
 *  @par Description
 *  Formats dates into this format "25 Dec, 2021"
 *
 *  @param[] none
 *              
 *
 *  @returns the date
 *
 *  @par Example
 *  @verbatim

    string ans = getDate();
    
    REQUIRE(ans == "25 Dec, 2021");

    @endverbatim
 ************************************************************************/
string getDate()
{
    if( currDate.empty() )
    {
        time_t myTimeT = time(nullptr);
        string currentTime = ctime( &myTimeT );
        
        return currentTime.substr(8, 2) + " " + currentTime.substr(4,3) + ", " + currentTime.substr(20, 4);
    }
    else
    {
        return currDate;
    }
}