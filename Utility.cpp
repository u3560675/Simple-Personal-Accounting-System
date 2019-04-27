//-----------------------------------------------------------------------
// Description : Accounting System - Utility - Class
// Last Modified: 2019-04-22
//
//-----------------------------------------------------------------------
// 
//-----------------------------------------------------------------------
#include<fstream>
#include <iostream>
#include <iomanip>  // setprecision
#include <sstream> // stringstream
#include <string>
#include <conio.h>
#include <ctime>
#include <io.h>
#include "Utility.h"
#include "BudgetMaster.h"
#include "AccountMaster.h"
#include "Transaction.h"

using namespace std;

const int MAX_VALID_YEAR = 9999; 
const int MIN_VALID_YEAR = 1900;

extern AccountMaster accountMaster1;
extern BudgetMaster budgetMaster1;
extern Transaction transaction1;


//======================================================================
// Display double with thousand separators (xxx,xxx,xxx.xx)
//======================================================================
string Utility::formatDouble(double value, int decimalPlace)
{
    
    //-----
    // Step-1: Format value with exact decimal place
    //-----
    stringstream ss; 
    ss.str("");
    ss << fixed << setprecision( decimalPlace ) << value;
    string strValue = ss.str();

    //-----
    // Step-2: Calc. no. of thousand separators
    //-----
    int digitsFront = strValue.find('.');                         // get decimal point position
    int sepCount    = digitsFront / 3;                            // no. of separator before decimal point
    if ((digitsFront % 3)==0)
    {
        sepCount--;
    }

    //-----
    // Step-3: Insert thousand separators (from right to left)
    //-----
    for ( int i = 1; i <= sepCount; i++ )
    {
       strValue.insert( digitsFront - (i*3), 1, ',' );   // separators before point
    }

    return strValue;
}

//-------------------------------------------------------------------------------------//
// 
//-------------------------------------------------------------------------------------//
string Utility::formatStringToDecimal(string source, int numOfDecimal)
{
	stringstream stream1;
	stream1 << fixed << setprecision(numOfDecimal) << stod(source);
	return stream1.str();
}

//-------------------------------------------------------------------------------------//
// 
//-------------------------------------------------------------------------------------//
string Utility::getDateTime(string format)
{
	time_t rawtime;
	struct tm * timeinfo;
	char char80[80];
	string string1;
	
	time (&rawtime);
	timeinfo = localtime(&rawtime);										// Get system time
	
	string1 = "";
	//----------
	// get date-time in 'yyyymmdd_HHMMSS'  (24 hrs)
	//----------
	if (format=="yyyymmdd_HHMMSS")
	{
		strftime(char80,sizeof(char80),"%Y%m%d_%H%M%S", timeinfo);			// <-- Format time as string
		string1 = string(char80);
	}
	
	return string1;
}

//-------------------------------------------------------------------------------------//
// 
//-------------------------------------------------------------------------------------//
bool Utility::isFileEmpty(string fileName)
{
	bool isEmpty = true;
	string dataRow;
	
    ifstream inFile(fileName);
    if (inFile.is_open())
    {
        while ( getline (inFile, dataRow) )
        {
        	if (dataRow=="")
            {
            	continue;
            }
       	    isEmpty = false;
       	    break;
	    }
        inFile.close();
    }
	return isEmpty; 
}

//-------------------------------------------------------------------------------------//
// 
//-------------------------------------------------------------------------------------//
bool Utility::isNumber(string str1, bool haveSign, bool hasDecimal)
{
  int counterDecimal = 0;
  
  for (int i = 0; i < str1.length(); i++) 
  {
  	if (haveSign && (str1[i]=='+' || str1[i]=='-'))
		{
			if (i > 0)    return false;         // Signs must be at front
      else          continue;
		}
		if (str1[i]=='.')
		{
		  if (hasDecimal==false)     return false;
		  if (counterDecimal>0)      return false;
		  counterDecimal++;
		  continue;
    }
    if (isdigit(str1[i]) == false) 
    {
    	return false;
	  }
  }
	return true; 
}

bool Utility::isValidDate(int dd, int mm, int yyyy) 
{ 
    // If year, month and day are out of expected range 
    if (yyyy > MAX_VALID_YEAR ||  
        yyyy < MIN_VALID_YEAR)      return false; 
    if (mm < 1 || mm > 12)          return false; 
    if (dd < 1 || dd > 31)          return false; 
  
    // Handle February in leap year 
    if (mm == 2) 
    { 
        if (isLeapYear(yyyy))    return (dd <= 29); 
        else                     return (dd <= 28); 
    } 
  
    // Check for Months which only have 30 days
    if (mm == 4 || mm == 6 || 
        mm == 9 || mm == 11) 
    {
        return (dd <= 30); 
    }
  
    // date is valid
    return true; 
} 

bool Utility::isLeapYear(int year) 
{ 
    return (((year % 4 == 0) && (year % 100 != 0)) ||       // year is dividable by 4 except every 100 years
            (year % 400 == 0));                             // (but every 400 year is a leap year)
}

bool Utility::isValidTime(int hh, int mm) 
{ 
    if (hh<0 || hh>23)		return false;
    if (mm<0 || mm>59)		return false;
    //
    return true;
}

//-------------------------------------------------------------------------------------//
// 
//-------------------------------------------------------------------------------------//
string Utility::padLeft(string str, char c, int len)       // Pad all extra spaces of the record.valuetype to the leftmost side of the pre-assigned slot
{
    if (str.length()<len)
    {
        return std::string(len-str.length(), c).append(str);
    }
    else
    {
        return str;
    }
}

//-------------------------------------------------------------------------------------//
// 
//-------------------------------------------------------------------------------------//
string Utility::padRight(string str, char c, int len)
{
    if (str.length()<len)
    {
        return str.append(std::string(len-str.length(), c));
    }
    else
    {
        return str;
    }
}


//-------------------------------------------------------------------------------------//
// Trim White Space - String
//-------------------------------------------------------------------------------------//
string Utility::trim(string source)
{
    return trimRight(trimLeft(source));
}
//-------------------------------------------------------------------------------------//
// Left Trim White Space - String
//-------------------------------------------------------------------------------------//
string Utility::trimLeft(string source)
{
    for (int i=0; i<source.length(); i++)
    {
        if (source.substr(i, 1)==" ")
        {
            continue;
        }
        return source.substr(i);
    }
    return source;
}
//-------------------------------------------------------------------------------------//
// Right Trim White Space - String
//-------------------------------------------------------------------------------------//
string Utility::trimRight(string source)
{
    for (int i=source.length(); i>-1; i--)
    {
        if (source.substr(i, 1)==" ")
        {
            continue;
        }
        return source.substr(0, i);
    }
    return source;
}

//-------------------------------------------------------------------------------------//
// Left Replace String - Char
//-------------------------------------------------------------------------------------//
string Utility::replaceLeft(string source, char fromChar, char toChar)
{
    for (int i=0; i<source.length(); i++)
    {
        if (source[i]==fromChar)
        {
            source[i] = toChar;
            continue;
        }
        return source;
    }
    return source;
}

//-------------------------------------------------------------------------------------//
// Right Replace String - Char
//-------------------------------------------------------------------------------------//
string Utility::replaceRight(string source, char fromChar, char toChar)
{
    for (int i=source.length(); i>-1; i--)
    {
        if (source[i]==fromChar)
        {
            source[i] = toChar;
            continue;
        }
        return source;
    }
    return source;
}


//-------------------------------------------------------------------------------------//
// Backup Files
//-------------------------------------------------------------------------------------//
void Utility::Backup_Files()
{
    string choice1;
    string dataRow;
    string subfolder;
    string source_AccountMaster;
    string source_BudgetMaster;
    string source_Transaction;
    string backup_AccountMaster;
    string backup_BudgetMaster;
    string backup_Transaction;
    int posBegin;

    subfolder = ".\\backup_" + getDateTime("yyyymmdd_HHMMSS"); 
    //--------------------
    // Get backup file name
    //--------------------
    source_AccountMaster = accountMaster1.filename_AccountMaster;
    source_BudgetMaster  = budgetMaster1.filename_BudgetMaster;
    source_Transaction   = transaction1.filename_Transaction;
    //
    backup_AccountMaster = source_AccountMaster.substr(0, (source_AccountMaster.length()-4)) + ".bak";
    backup_BudgetMaster  = source_BudgetMaster.substr( 0, (source_BudgetMaster.length()-4)) + ".bak"; 
    backup_Transaction   = source_Transaction.substr(  0, (source_Transaction.length()-4)) + ".bak";
    //
    posBegin = backup_AccountMaster.find_last_of("\\");
    backup_AccountMaster = subfolder + backup_AccountMaster.substr(posBegin);
    
    posBegin = backup_BudgetMaster.find_last_of("\\");
    backup_BudgetMaster = subfolder + backup_BudgetMaster.substr(posBegin);
    
    posBegin = backup_Transaction.find_last_of("\\");
    backup_Transaction = subfolder + backup_Transaction.substr(posBegin);

    // 
    system("cls");
    cout << "===============================================================================" << endl;
    cout << "                                                                               " << endl;
    cout << " This function will copy files to backup subfolder:                            " << endl;
    cout << " " << subfolder << "                                                           " << endl;
    cout << "                                                                               " << endl;
    cout << "===============================================================================" << endl;


    //--------------------
    // User confirmation
    //--------------------
    while (true)
    {
        cout << "Enter--> Y=proceed,  X=exit " << endl;
        cout << "Select: ";
        // read the input
        getline (cin, choice1);
        
        // Exit...
        if (choice1=="X" || choice1=="x")
        {
            cout << "\n";
            return;     // exit
        }        
        if (choice1=="Y" || choice1=="y")
        {
            break; 
        }        
        cout << "\n";
    }


    // create the backup folder
    mkdir(subfolder.c_str());

    
    //--------------------
    // Backup - Account Master
    //--------------------
    ifstream file_Source1(source_AccountMaster);
    ofstream file_Backup1(backup_AccountMaster);
    if (file_Source1.is_open()==false)
    {
        cout << "> Unable to open file "       << source_AccountMaster << ".  It might be either missing or corrupted." << endl;
        cout << "Press <Enter> to continue."   << endl;
        getline (cin, choice1);
        cout.flush();
        return;
    }
    // Copy file...
    cout << "> Copying file: Account Master" << endl;
    file_Backup1 << file_Source1.rdbuf() ;
    file_Source1.close();
    file_Backup1.close();

    //--------------------
    // Backup - Budget Master
    //--------------------
    ifstream file_Source2 (source_BudgetMaster);
    ofstream file_Backup2 (backup_BudgetMaster);
    if (file_Source2.is_open()==false)
    {
        cout << "> Unable to open file "       << source_BudgetMaster << ".  It might be either missing or corrupted." << endl;
        cout << "Press <Enter> to continue."   << endl;
        getline (cin, choice1);
        cout.flush();
        return;
    }
    // Copy file...
    cout << "> Copying file: Budget Master" << endl;
    file_Backup2 << file_Source2.rdbuf() ;
    file_Source2.close();
    file_Backup2.close();

    //--------------------
    // Backup - Transaction file
    //--------------------
    ifstream file_Source3(source_Transaction);
    ofstream file_Backup3(backup_Transaction);
    if (file_Source3.is_open()==false)
    {
        cout << "> Unable to open file "       << source_Transaction << ".  It might be either missing or corrupted." << endl;
        cout << "Press <Enter> to continue."   << endl;
        getline (cin, choice1);
        cout.flush();
        return;
    }
    // Copy file...
    cout << "> Copying file: Transaction" << endl;
    file_Backup3 << file_Source3.rdbuf() ;
    file_Source3.close();
    file_Backup3.close();


    cout << "" << endl;
    cout << "===============================================================================" << endl;
    cout << "BACKUP COMPLETE." << endl;
    cout << "===============================================================================" << endl;

    // Return to main menu after completion
    cout << "Press any key to return to main menu." << endl;
    getline (cin, choice1);
    cout.flush();
}
