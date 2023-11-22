#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;

struct transactionData
{
    string firstName;
    string lastName;
    string streetAddress;
    string city;
    string state;
    string zipCode;
    
    double transAmount;
    double currentBalance;
};

void writeLetter(transactionData record, string templateFile, string currentDate);
string replace ( string data, string search, int len, string replacement );
bool getClient( istream *inputFile, transactionData *record );
string getDate();
string currency( double value );
