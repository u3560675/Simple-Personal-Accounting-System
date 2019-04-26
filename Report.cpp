//-----------------------------------------------------------------------
// Description : Accounting System - Transaction - Class
// Last Modified: 2019-04-22
//
//-----------------------------------------------------------------------
// 
//-----------------------------------------------------------------------
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <conio.h>
#include "AccountMaster.h"
#include "BudgetMaster.h"
#include "Report.h"
#include "Transaction.h"
#include "Utility.h"
#include <bits/stdc++.h> 

using namespace std;

extern Utility utility1;
extern AccountMaster accountMaster1;
extern BudgetMaster budgetMaster1;
Transaction transaction1;

extern struct AccountMaster::AccountMasterRecord acctRec1;
extern struct AccountMaster::AccountMasterFldLen acctFldLen1;

extern struct BudgetMaster::BudgetMasterRecord bdgtRec1;
extern struct BudgetMaster::BudgetMasterFldLen bdgtFldLen1;

extern struct Transaction::TransactionRecord transRec1;
extern struct Transaction::TransactionFldLen transFldLen1;

vector<tuple<string, string, string, string> > reportRecord_MS;
vector<tuple<string, string, string, string, string> > reportRecord_MT;
vector<tuple<string, string, string, string, string, string, string> > reportRecord_BC;     // account, description, actual total amount, budget, difference, percentage


//-------------------------------------------------------------------------------------//
// Sub-menu:  REPORT
//-------------------------------------------------------------------------------------//
void Report::Menu()
{
  char selection;
  
  //-------------------
  // Loop: Display menu and selection option 
  //-------------------
  while(true)
  {
    // Display menu
    system("cls");
    cout << "|-------------------------------------------------------------------------|" << endl;
    cout << "|                 ACCOUNTING SYSTEM - STATISTICAL REPORTS                 |" << endl;
    cout << "|-------------------------------------------------------------------------|" << endl;
    cout << "|***           Welcome to HKU Simple Accounting System (2019)          ***|" << endl;
    cout << "|***  This system is developed by ENGG1340 Class No.XXXXX Group No.XX  ***|" << endl;
    cout << "|-------------------------------------------------------------------------|" << endl;
    cout << "|                                                                         |" << endl;
    cout << "|  Options:                                                               |" << endl;
    cout << "|           1. Monthly / Yearly Statistics Report (EXPENSE)               |" << endl;
    cout << "|           2. Monthly / Yearly Statistics Report (INCOME)                |" << endl;
    cout << "|           3. Monthly / Annual Transaction Details                       |" << endl;
    cout << "|           4. Monthly / Yearly Budget Control Statistics (EXPENSE)       |" << endl;
    cout << "|           5. Monthly / Yearly Budget Control Statistics (INCOME)        |" << endl;
    cout << "|                                                                         |" << endl;
    cout << "|           X. Exit                                                       |" << endl;
    cout << "|-------------------------------------------------------------------------|" << endl;
    cout << "\n Select: ";
    // read the input
    cin >> selection;
    
    switch(selection)
    {
      case '1' :
        cout.flush();
        system("cls");
        cin.ignore();
        MonthStat_Report("E");
        continue;
      case '2' :
        cout.flush();
        system("cls");
        cin.ignore();
        MonthStat_Report("I");
        continue;
      case '3' :
        cout.flush();
        system("cls");
        cin.ignore();
        MonthTrans_Report();
        continue;
      case '4' :
        cout.flush();
        system("cls");
        cin.ignore();
        BdgtCtrl_Report("E");
        continue;
      case '5' :
        cout.flush();
        system("cls");
        cin.ignore();
        BdgtCtrl_Report("I");
        continue;
      case 'X' :
      case 'x' :
        cout << "\nExit...\n";
        return;
      default : 
        cout << "\n>> Invalid selection.  Please retry.\n";
        system("PAUSE");
        continue;
        // no break in the default case
    }
  }
   
  return;
}


//-------------------------------------------------------------------------------------//
// Generate and Display Monthly / Yearly Statistics
//-------------------------------------------------------------------------------------//
void Report::MonthStat_Report(string accountType)
{
  string choice1 = "";
  string input1 = "";
  string accountCode = "";
  string monthYear = "";
  string month = "";
  string dataRow = "";
  string grandTotal2 = "";
  double grandTotal1 = 0;
  acctFldLen1.initialize();
  
  reportRecord_MS.clear();
  
  //---------------
  // User selection
  //---------------
  while (true)
  {
    // select report type
    system("cls");
    cout << "\n";
  	cout << "Select a report type:" << endl;
  	cout << "                     1) Monthly Statistics" << endl;
    cout << "                     2) Yearly Statistics" << endl;
  	cout << "                     X) Exit" << endl;
    
	
    cout << "Selection: ";
    
    getline (cin, choice1);
    
    // Exit
    if (choice1=="X" ||
        choice1=="x")
    {
      //recordList_Trans.clear();
      cout << "\n";
      cout.flush();
      return;     // exit
    }
    
    //--------------------
    // Monthly Statistics
    //--------------------
	  if (choice1 == "1")
	  {
	    // Get mm-yyyy
      cout << "Please enter a month and a year (mm-yyyy): ";
      getline(cin, input1);
      
      // is valid input?
      if (input1.length()!=7)
      {
        cout << "> Invalid Input. Input must be exactly 7 characters. Please retry." << endl;
        cout << "Retry? (Y/N): ";
        getline (cin, choice1);
        if (choice1 == "N" || choice1 == "n")      return;                // exit
        else                                       continue;

        cout.flush();
        continue;
      }        
      // Is input numeric?
      if (input1.substr(2,1)!="-")
      {
    	  cout << "> Invalid Date separator. Valid: '-'. Please retry." << endl;
        cout << "Retry? (Y/N): ";
        getline (cin, choice1);
        if (choice1 == "N" || choice1 == "n")      return;                // exit
        else                                       continue;
        
    		cout.flush();
    		continue;
      }
      if (utility1.isNumber(input1.substr(0, 2), false, false)==false ||
    	    utility1.isNumber(input1.substr(3, 4), false, false)==false)
      {
      	cout << "> Invalid Date numeric value. Please retry." << endl;
		    cout << "Retry? (Y/N): ";
        getline (cin, choice1);
        if (choice1 == "N" || choice1 == "n")      return;                // exit
        else                                       continue;
    	cout.flush();
    	continue;
      }
      // Is it a valid year?
      if (utility1.isValidDate(01, stoi(input1.substr(0, 2)), stoi(input1.substr(3, 4)))==false)    // dummy day that always exist, as filtering by month + year
      {
        cout << "> Invalid value. Please retry." << endl;
        cout << "Retry? (Y/N): ";
        getline (cin, choice1);
        if (choice1 == "N" || choice1 == "n")      return;                // exit
        else                                       continue;
        cout.flush();
        continue;
      }        
      monthYear = input1;
      cout.flush();
    }
	  
	  //-------------------
    // Yearly Statistics
    //-------------------
	  else if (choice1 == "2")
	  {
	    // Get yyyy
      cout << "Please enter a year (yyyy): ";
      getline(cin, input1);
      
      // is valid input?
      if (input1.length()!=4)
      {
        cout << "> Invalid Transaction Year. Input must be exactly 4 characters. Please retry." << endl;
        cout << "Retry? (Y/N): ";
        getline (cin, choice1);
        if (choice1 == "N" || choice1 == "n")      return;                // exit
        else                                       continue;

        cout.flush();
        continue;
      }        
      // Is input numeric?
      if (utility1.isNumber(input1, false, false)==false)     // no need to use substring
      {
        cout << "> Invalid Year numeric value. Please retry." << endl;
        cout << "Retry? (Y/N): ";
        getline (cin, choice1);
        if (choice1 == "N" || choice1 == "n")      return;                // exit
        else                                       continue;
        cout.flush();
        continue;
      }
      // Is it a valid year?
      if (utility1.isValidDate(01, 01, stoi(input1))==false)    // dummy day and month that always exist, as only filtering by year
      {
        cout << "> Invalid Year value. Please retry." << endl;
        cout << "Retry? (Y/N): ";
        getline (cin, choice1);
        if (choice1 == "N" || choice1 == "n")      return;                // exit
        else                                       continue;
        cout.flush();
        continue;
      }        
      monthYear = input1;
      cout.flush();
    }
    
    else
    {
      cout << "> Invalid input. Please retry." << endl;
      cout << "Retry? (Y/N): ";
      getline (cin, choice1);
      if (choice1 == "N" || choice1 == "n")      return;                // exit
      else                                       continue;
      cout.flush();
      continue;
    }
    
    break;
  }
	  
  //----------------
  // Get data
  //----------------
  
  // Get list of account code from account master
  acctRec1.initialize();
  
  ifstream file1 (accountMaster1.filename_AccountMaster);
  if (file1.is_open())
  {
    // Loop to extract Account Code records to array...  (before sorting)
    while ( getline (file1, dataRow) )
    {
      if (utility1.trim(dataRow)=="")
      {
        continue;    // skip if space line
      }
      //
      // Split data line into column values
      accountMaster1.split_DataRow_to_Fields(dataRow, acctRec1);
      
      if (acctRec1.acctType != accountType)
      {
        continue;        // skip if not matched
      }
      
      //
      // matched data...
      reportRecord_MS.push_back(make_tuple(
        acctRec1.acctCode, 
        acctRec1.acctDesc,
        "0",                                 // Dummy
        ""                                   // Empty
        ));
    }
    file1.close();
    
    // Sort Account Code list by first column (Account Code)
    sort(reportRecord_MS.begin(), reportRecord_MS.end());
  }
  else
  {
    cout << "> Error!  Unable to open file";
    system("PAUSE");
    return;
  }
  
  // Get account total transaction amount by month / year
  for (int i = 0; i < reportRecord_MS.size(); i++)
  {
    get<2>(reportRecord_MS[i]) = to_string(get_accountTotal(get<0>(reportRecord_MS[i])  , monthYear));
    get<2>(reportRecord_MS[i]) = utility1.formatStringToDecimal(get<2>(reportRecord_MS[i]), 2);
    grandTotal1 += stod(get<2>(reportRecord_MS[i]));
  }
  
  grandTotal2 = utility1.formatStringToDecimal(  to_string( grandTotal1 ), 2);
  
  //-------------
  // Calculate %
  //-------------
  for (int i = 0; i < reportRecord_MS.size(); i++)
  {
    if (grandTotal1 > 0)
    {
      get<3>(reportRecord_MS[i]) = to_string(stod(get<2>(reportRecord_MS[i])) / stod(grandTotal2) * 100);    
      get<3>(reportRecord_MS[i]) = utility1.formatStringToDecimal(get<3>(reportRecord_MS[i]),  2);
    }
    else
    {
      get<3>(reportRecord_MS[i]) = "0.00";
    }
  }
  
  
  //----------
  // Display report
  //----------
  system("cls");
  if (accountType == "E")     cout << "MONTHLY STATISTICS EXPENSE REPORT (Period: " << monthYear << "):" << endl;
  else                        cout << "MONTHLY STATISTICS INCOME REPORT (Period: " << monthYear << "):" << endl;
  cout << "****************************************************************************************" << endl;
  cout << "ACCOUNT  DESCRIPTION                       TOTAL AMOUNT    (%)" << endl;
  cout << "-------  ------------------------------  --------------  ------" << endl;
  
  for (int i = 0; i < reportRecord_MS.size(); i++)
  {
    get<1>(reportRecord_MS[i]) = utility1.padRight( get<1>(reportRecord_MS[i]) , ' ', acctFldLen1.acctDesc);
    get<2>(reportRecord_MS[i]) = utility1.padLeft ( utility1.formatDouble(  stod( get<2>(reportRecord_MS[i]) ),  2) , ' ', 14);     // move space to left + display with thousand separators (xxx,xxx,xxx.xx)
    get<3>(reportRecord_MS[i]) = utility1.padLeft ( get<3>(reportRecord_MS[i]) , ' ', 6);
    
    cout << get<0>(reportRecord_MS[i]) << "     "     // acctCode
  			 << get<1>(reportRecord_MS[i]) << "  "       // acctDesc
         << get<2>(reportRecord_MS[i]) << "  "       // Total amount
         << get<3>(reportRecord_MS[i]) << ""         // Percentage
         << "\n";
  }
  grandTotal2             = utility1.padLeft ( utility1.formatDouble( stod(grandTotal2), 2) , ' ', 14);                           // move space to left + display with thousand separators (xxx,xxx,xxx.xx)
  cout << "-------  ------------------------------  --------------  ------\n"
       << "                            Grand total  " << grandTotal2 << "  " << "100.00%" << "\n"
       << "                                         ==============  ======" << endl;
  
  //--------
  // Exit
  //--------
  while (true)
  {
    cout << "Enter X to exit." << endl;
    getline (cin, choice1);
    // Exit
    if (choice1=="X" ||
        choice1=="x")
    {
      //recordList_Trans.clear();
      cout << "\n";
      cout.flush();
      return;     // exit
    }
  }
}


//-------------------------------------------------------------------------------------//
// Generate and Display Monthly / Yearly Transaction Details
//-------------------------------------------------------------------------------------//
void Report::MonthTrans_Report()
{
  string choice1 = "";
  string input1 = "";
  string accountCode = "";
  string monthYear = "";
  string month = "";
  string dataRow = "";
  string grandTotal2 = "";
  double grandTotal1 = 0;
  transFldLen1.initialize();
  
  reportRecord_MT.clear();
  
  //---------------
  // User selection
  //---------------
  while (true)
  {
    // select report type
    system("cls");
    cout << "\n";
  	cout << "Select a report type:" << endl;
  	cout << "                     1) Monthly Statistics" << endl;
    cout << "                     2) Yearly Statistics" << endl;
  	cout << "                     X) Exit" << endl;
    
	
    cout << "Selection: ";
    
    getline (cin, choice1);
    
    // Exit
    if (choice1=="X" ||
        choice1=="x")
    {
      //recordList_Trans.clear();
      cout << "\n";
      cout.flush();
      return;     // exit
    }
    
    //--------------------
    // Monthly Statistics
    //--------------------
	  if (choice1 == "1")
	  {
	    // Get mm-yyyy
      cout << "Please enter a month and a year (mm-yyyy): ";
      getline(cin, input1);
      
      // is valid input?
      if (input1.length()!=7)
      {
        cout << "> Invalid Input. Input must be exactly 7 characters. Please retry." << endl;
        cout << "Retry? (Y/N): ";
        getline (cin, choice1);
        if (choice1 == "N" || choice1 == "n")      return;                // exit
        else                                       continue;

        cout.flush();
        continue;
      }        
      // Is input numeric?
      if (input1.substr(2,1)!="-")
      {
    	  cout << "> Invalid Date separator. Valid: '-'. Please retry." << endl;
        cout << "Retry? (Y/N): ";
        getline (cin, choice1);
        if (choice1 == "N" || choice1 == "n")      return;                // exit
        else                                       continue;
        
    		cout.flush();
    		continue;
      }
      if (utility1.isNumber(input1.substr(0, 2), false, false)==false ||
    	    utility1.isNumber(input1.substr(3, 4), false, false)==false)
      {
      	cout << "> Invalid Date numeric value. Please retry." << endl;
		    cout << "Retry? (Y/N): ";
        getline (cin, choice1);
        if (choice1 == "N" || choice1 == "n")      return;                // exit
        else                                       continue;
    	cout.flush();
    	continue;
      }
      // Is it a valid year?
      if (utility1.isValidDate(01, stoi(input1.substr(0, 2)), stoi(input1.substr(3, 4)))==false)    // dummy day that always exist, as filtering by month + year
      {
        cout << "> Invalid value. Please retry." << endl;
        cout << "Retry? (Y/N): ";
        getline (cin, choice1);
        if (choice1 == "N" || choice1 == "n")      return;                // exit
        else                                       continue;
        cout.flush();
        continue;
      }        
      monthYear = input1;
      cout.flush();
    }
	  
	  //-------------------
    // Yearly Statistics
    //-------------------
	  else if (choice1 == "2")
	  {
	    // Get yyyy
      cout << "Please enter a year (yyyy): ";
      getline(cin, input1);
      
      // is valid input?
      if (input1.length()!=4)
      {
        cout << "> Invalid Transaction Year. Input must be exactly 4 characters. Please retry." << endl;
        cout << "Retry? (Y/N): ";
        getline (cin, choice1);
        if (choice1 == "N" || choice1 == "n")      return;                // exit
        else                                       continue;

        cout.flush();
        continue;
      }        
      // Is input numeric?
      if (utility1.isNumber(input1, false, false)==false)     // no need to use substring
      {
        cout << "> Invalid Year numeric value. Please retry." << endl;
        cout << "Retry? (Y/N): ";
        getline (cin, choice1);
        if (choice1 == "N" || choice1 == "n")      return;                // exit
        else                                       continue;
        cout.flush();
        continue;
      }
      // Is it a valid year?
      if (utility1.isValidDate(01, 01, stoi(input1))==false)    // dummy day and month that always exist, as only filtering by year
      {
        cout << "> Invalid Year value. Please retry." << endl;
        cout << "Retry? (Y/N): ";
        getline (cin, choice1);
        if (choice1 == "N" || choice1 == "n")      return;                // exit
        else                                       continue;
        cout.flush();
        continue;
      }        
      monthYear = input1;
      cout.flush();
    }
    
    else
    {
      cout << "> Invalid input. Please retry." << endl;
      cout << "Retry? (Y/N): ";
      getline (cin, choice1);
      if (choice1 == "N" || choice1 == "n")      return;                // exit
      else                                       continue;
      cout.flush();
      continue;
    }
    
    //-------------------
    //  Get account code
    //-------------------
    // input Account code  (Primary Key)
    cout << "\n";
    cout << "Please enter an Account Code to list." << endl;
    cout << "Account Code: ";
    getline (cin, input1);

    if (input1.length()<1)
    {
      cout << "> Invalid Account code.  Cannot be empty." << endl;
      cout << "Retry? (Y/N): ";
      getline (cin, choice1);
      if (choice1 == "N" || choice1 == "n")      return;                // exit
      else                                       continue;
      
      cout.flush();
      continue;
    }        
    if (input1.length()!=transFldLen1.acctCode1)
    {
      cout << "> Invalid Account code. Input must be exactly " << transFldLen1.acctCode1 << " characters. Please retry." << endl;
      cout << "Retry? (Y/N): ";
      getline (cin, choice1);
      if (choice1 == "N" || choice1 == "n")      return;                // exit
      else                                       continue;
      
      cout.flush();
      continue;
    }        
    if (accountMaster1.isValid_AccountMasterKey2(input1)==false)    
    {
      cout << "> Error - Account code is not valid. Please retry." << endl;
      cout << "Retry? (Y/N): ";
      getline (cin, choice1);
      if (choice1 == "N" || choice1 == "n")      return;                // exit
      else                                       continue;
      
      cout.flush();
      continue;
    }
    accountCode = input1;
    
    break;
  }
  
  //----------------
  // Get data
  //----------------
  acctRec1.initialize();
  transRec1.initialize();
  
  //Get acconut type
  accountMaster1.getRec_by_AccountMasterKey(accountCode, acctRec1);
  
  //--- Get list of transactioln records from transaction ---//
  ifstream file1 (transaction1.filename_Transaction);
  if (file1.is_open())
  {
    // Loop to extract Transaction records to array...  (before sorting)
    while ( getline (file1, dataRow) )
    {
      if (utility1.trim(dataRow)=="")
      {
        continue;    // skip if space line
      }
      //
      // Split data line into column values
      transaction1.split_DataRow_to_Fields(dataRow, transRec1);
      
      if (transRec1.acctCode1 != accountCode && transRec1.acctCode2 != accountCode)     continue;
      if (monthYear.length() == 7 && transRec1.transDate.substr(3, 7) != monthYear)     continue;
      if (monthYear.length() == 4 && transRec1.transDate.substr(6, 4) != monthYear)     continue;
      
      //
      // matched data...
      reportRecord_MT.push_back(make_tuple(
        transRec1.transDate, 
        transRec1.amount,
        transRec1.refNbr,
        transRec1.transType,
        transRec1.transDesc
        ));
      
      grandTotal1 += stod(transRec1.amount);
    }
    file1.close();
    
    // Sort Account Code list by first column (Trans Date)
    sort(reportRecord_MT.begin(), reportRecord_MT.end());
  }
  else
  {
    cout << "> Error!  Unable to open file";
    system("PAUSE");
    return;
  }
  
  // Correct to 2 decimal place
  grandTotal2 = utility1.formatStringToDecimal(  to_string( grandTotal1 ), 2);
  
  //----------
  // Display report
  //----------
  system("cls");
  cout << "ACCOUNT MONTHLY TRANSACTION DETAILS (Period: " << monthYear << "):" << endl;
  cout << "**************************************************************************************************" << endl;
  cout <<                                   "Account Code :   " << accountCode << endl;
  if (acctRec1.acctType == "E")     cout << "Account Type :   Expense" << endl;
  else                              cout << "Account Type :   Expense" << endl;
  cout << "**************************************************************************************************" << endl;
  cout << "Line  Trans Date      Amount          Ref. No.        Category          Description/Narration" << endl;
  cout << "----  ----------  --------------  ---------------  ---------------  ------------------------------" << endl;
  
  for (int i = 0; i < reportRecord_MT.size(); i++)
  {
    get<0>(reportRecord_MT[i]) = utility1.padLeft( get<0>(reportRecord_MT[i]) , ' ', transFldLen1.transDate);
    get<1>(reportRecord_MT[i]) = utility1.padLeft ( utility1.formatDouble(  stod( get<1>(reportRecord_MT[i]) ),  2) , ' ', transFldLen1.amount);     // move space to left + display with thousand separators (xxx,xxx,xxx.xx)
    get<2>(reportRecord_MT[i]) = utility1.padLeft ( get<2>(reportRecord_MT[i]) , ' ', transFldLen1.refNbr);
    get<3>(reportRecord_MT[i]) = utility1.padLeft ( get<3>(reportRecord_MT[i]) , ' ', transFldLen1.transType);
    get<4>(reportRecord_MT[i]) = utility1.padRight ( get<4>(reportRecord_MT[i]) , ' ', transFldLen1.transDesc);
    
    cout << utility1.padLeft(to_string(i+1), '0', 4) << "  "
         << get<0>(reportRecord_MT[i]) << "      "     // transDate
  			 << get<1>(reportRecord_MT[i]) << "  "         // amount
         << get<2>(reportRecord_MT[i]) << "  "         // refNbr
         << get<3>(reportRecord_MT[i]) << "  "         // TransType
         << get<3>(reportRecord_MT[i]) << "  "         // TransDesc
         << "\n";
  }
  grandTotal2             = utility1.padLeft ( utility1.formatDouble( stod(grandTotal2), 2) , ' ', 14);                                             // move space to left + display with thousand separators (xxx,xxx,xxx.xx)
  cout << "--------------------------------------------------------------------------------------------------\n"
       << "           Total: " << grandTotal2 << "\n"
       << "                  ==============" << endl;
  
  //--------
  // Exit
  //--------
  while (true)
  {
    cout << "Enter X to exit." << endl;
    getline (cin, choice1);
    // Exit
    if (choice1=="X" ||
        choice1=="x")
    {
      //recordList_Trans.clear();
      cout << "\n";
      cout.flush();
      return;     // exit
    }
  }
}


//-------------------------------------------------------------------------------------//
// Generate and Display Monthly / Yearly Budget Control Statistics
//-------------------------------------------------------------------------------------//
void Report::BdgtCtrl_Report(string accountType)
{
  string choice1 = "";
  string input1 = "";
  string accountCode = "";
  string monthYear = "";
  string month = "";
  string dataRow = "";
  string grandTotal1s = "";     // For total transaction amount (string)
  string grandTotal2s = "";     // For total budget amount      (string)
  string grandTotal3s = "";     // For total difference         (string)
  double grandTotal1d = 0;      // For total transaction amount (double)
  double grandTotal2d = 0;      // For total budget amount      (double)
  double grandTotal3d = 0;      // For total difference         (double)
  double percentage;
  acctFldLen1.initialize();
  bdgtFldLen1.initialize();
  
  reportRecord_BC.clear();
  
  //---------------
  // User selection
  //---------------
  while (true)
  {
    // select report type
    system("cls");
    cout << "\n";
  	cout << "Select a report type:" << endl;
  	cout << "                     1) Monthly Statistics" << endl;
    cout << "                     2) Yearly Statistics" << endl;
  	cout << "                     X) Exit" << endl;
    
	
    cout << "Selection: ";
    
    getline (cin, choice1);
    
    // Exit
    if (choice1=="X" ||
        choice1=="x")
    {
      //recordList_Trans.clear();
      cout << "\n";
      cout.flush();
      return;     // exit
    }
    
    //--------------------
    // Monthly Statistics
    //--------------------
	  if (choice1 == "1")
	  {
	    // Get mm-yyyy
      cout << "Please enter a month and a year (mm-yyyy): ";
      getline(cin, input1);
      
      // is valid input?
      if (input1.length()!=7)
      {
        cout << "> Invalid Input. Input must be exactly 7 characters. Please retry." << endl;
        cout << "Retry? (Y/N): ";
        getline (cin, choice1);
        if (choice1 == "N" || choice1 == "n")      return;                // exit
        else                                       continue;

        cout.flush();
        continue;
      }        
      // Is input numeric?
      if (input1.substr(2,1)!="-")
      {
    	  cout << "> Invalid Date separator. Valid: '-'. Please retry." << endl;
        cout << "Retry? (Y/N): ";
        getline (cin, choice1);
        if (choice1 == "N" || choice1 == "n")      return;                // exit
        else                                       continue;
        
    		cout.flush();
    		continue;
      }
      if (utility1.isNumber(input1.substr(0, 2), false, false)==false ||
    	    utility1.isNumber(input1.substr(3, 4), false, false)==false)
      {
      	cout << "> Invalid Date numeric value. Please retry." << endl;
		    cout << "Retry? (Y/N): ";
        getline (cin, choice1);
        if (choice1 == "N" || choice1 == "n")      return;                // exit
        else                                       continue;
    	cout.flush();
    	continue;
      }
      // Is it a valid year?
      if (utility1.isValidDate(01, stoi(input1.substr(0, 2)), stoi(input1.substr(3, 4)))==false)    // dummy day that always exist, as filtering by month + year
      {
        cout << "> Invalid value. Please retry." << endl;
        cout << "Retry? (Y/N): ";
        getline (cin, choice1);
        if (choice1 == "N" || choice1 == "n")      return;                // exit
        else                                       continue;
        cout.flush();
        continue;
      }        
      monthYear = input1;
      cout.flush();
    }
	  
	  //-------------------
    // Yearly Statistics
    //-------------------
	  else if (choice1 == "2")
	  {
	    // Get yyyy
      cout << "Please enter a year (yyyy): ";
      getline(cin, input1);
      
      // is valid input?
      if (input1.length()!=4)
      {
        cout << "> Invalid Transaction Year. Input must be exactly 4 characters. Please retry." << endl;
        cout << "Retry? (Y/N): ";
        getline (cin, choice1);
        if (choice1 == "N" || choice1 == "n")      return;                // exit
        else                                       continue;

        cout.flush();
        continue;
      }        
      // Is input numeric?
      if (utility1.isNumber(input1, false, false)==false)     // no need to use substring
      {
        cout << "> Invalid Year numeric value. Please retry." << endl;
        cout << "Retry? (Y/N): ";
        getline (cin, choice1);
        if (choice1 == "N" || choice1 == "n")      return;                // exit
        else                                       continue;
        cout.flush();
        continue;
      }
      // Is it a valid year?
      if (utility1.isValidDate(01, 01, stoi(input1))==false)    // dummy day and month that always exist, as only filtering by year
      {
        cout << "> Invalid Year value. Please retry." << endl;
        cout << "Retry? (Y/N): ";
        getline (cin, choice1);
        if (choice1 == "N" || choice1 == "n")      return;                // exit
        else                                       continue;
        cout.flush();
        continue;
      }        
      monthYear = input1;
      cout.flush();
    }
    
    else
    {
      cout << "> Invalid input. Please retry." << endl;
      cout << "Retry? (Y/N): ";
      getline (cin, choice1);
      if (choice1 == "N" || choice1 == "n")      return;                // exit
      else                                       continue;
      cout.flush();
      continue;
    }
    
    break;
  }
  
  
  //----------------
  // Get data
  //----------------
  
  // Get list of budgets + account descriptions
  acctRec1.initialize();
  transRec1.initialize();
  bdgtRec1.initialize();
  
  //--- Acct Code + Desc ---//
  ifstream file1 (accountMaster1.filename_AccountMaster);
  if (file1.is_open())
  {
    // Loop to extract Account Code records to array...  (before sorting)
    while ( getline (file1, dataRow) )
    {
      if (utility1.trim(dataRow)=="")
      {
        continue;    // skip if space line
      }
      //
      // Split data line into column values
      accountMaster1.split_DataRow_to_Fields(dataRow, acctRec1);
      
      if (acctRec1.acctType != accountType)
      {
        continue;        // skip if not matched
      }
      
      //
      // matched data...
      reportRecord_BC.push_back(make_tuple(
        acctRec1.acctCode, 
        acctRec1.acctDesc,
        "0.00",
        "0.00",
        "0.00",
        "0.00",
        ""
        ));
    }
    file1.close();
    
    // Sort Account Code list by first column (Account Code)
    sort(reportRecord_BC.begin(), reportRecord_BC.end());
  }
  else
  {
    cout << "> Error!  Unable to open file";
    system("PAUSE");
    return;
  }
  
  //--- Transaction Amount ---//
  // Get account total transaction amount by month / year
  for (int i = 0; i < reportRecord_BC.size(); i++)
  {
    get<2>(reportRecord_BC[i]) = to_string(get_accountTotal(get<0>(reportRecord_BC[i])  , monthYear));
    get<2>(reportRecord_BC[i]) = utility1.formatStringToDecimal(get<2>(reportRecord_BC[i]), 2);
    
    // Accumulate total transaction amount for display
    grandTotal1d += stod(get<2>(reportRecord_BC[i]));
  }
  
  grandTotal1s = utility1.formatStringToDecimal(  to_string( grandTotal1d ), 2);
  
  
  //--- Budget ---//
  ifstream file2 (budgetMaster1.filename_BudgetMaster);
  if (file2.is_open())
  {
    //----------
    // Loop to find the record...
    //----------
    while ( getline (file2, dataRow) )
    {
      if (utility1.trim(dataRow)=="")
      {
        continue;            // skip if space line
      }
      //
      // Split data line into column values
      budgetMaster1.split_DataRow_to_Fields(dataRow, bdgtRec1);
      
      if (monthYear.length() == 7 && bdgtRec1.year != monthYear.substr(3, 4))                 continue;
      if (monthYear.length() == 4 && bdgtRec1.year != monthYear)                              continue;
      
      for (int i = 0; i < reportRecord_BC.size(); i++)
      {
        if (bdgtRec1.acctCode == get<0>(reportRecord_BC[i]))
        {
          if (monthYear.length() == 7)
          {
            // Store month to be compared
            if(monthYear.substr(0,2) == "01")          get<3>(reportRecord_BC[i]) = bdgtRec1.amount_01;
            else if(monthYear.substr(0,2) == "02")     get<3>(reportRecord_BC[i]) = bdgtRec1.amount_02;
            else if(monthYear.substr(0,2) == "03")     get<3>(reportRecord_BC[i]) = bdgtRec1.amount_03;
            else if(monthYear.substr(0,2) == "04")     get<3>(reportRecord_BC[i]) = bdgtRec1.amount_04;
            else if(monthYear.substr(0,2) == "05")     get<3>(reportRecord_BC[i]) = bdgtRec1.amount_05;
            else if(monthYear.substr(0,2) == "06")     get<3>(reportRecord_BC[i]) = bdgtRec1.amount_06;
            else if(monthYear.substr(0,2) == "07")     get<3>(reportRecord_BC[i]) = bdgtRec1.amount_07;
            else if(monthYear.substr(0,2) == "08")     get<3>(reportRecord_BC[i]) = bdgtRec1.amount_08;
            else if(monthYear.substr(0,2) == "09")     get<3>(reportRecord_BC[i]) = bdgtRec1.amount_09;
            else if(monthYear.substr(0,2) == "10")     get<3>(reportRecord_BC[i]) = bdgtRec1.amount_10;
            else if(monthYear.substr(0,2) == "11")     get<3>(reportRecord_BC[i]) = bdgtRec1.amount_11;
            else if(monthYear.substr(0,2) == "12")     get<3>(reportRecord_BC[i]) = bdgtRec1.amount_12;
          }
          
          else
          {
            get<3>(reportRecord_BC[i]) = bdgtRec1.amount;
          }
          
          get<6>(reportRecord_BC[i]) = bdgtRec1.alert;
          
          // Accumulate total budget amount for display
          grandTotal2d += stod(get<3>(reportRecord_BC[i]));
          break;
        }
      }
    }
    
    grandTotal2s = utility1.formatStringToDecimal(  to_string( grandTotal2d ), 2);
    
    
    // Calculate difference (budget - actual) and percentage
    for (int i = 0; i < reportRecord_BC.size(); i++)
    {
      // Difference
      get<4>(reportRecord_BC[i]) = to_string( stod(get<3>(reportRecord_BC[i])) - stod(get<2>(reportRecord_BC[i])) );
      get<4>(reportRecord_BC[i]) = utility1.formatStringToDecimal(get<4>(reportRecord_BC[i]), 2);
      
      // Accumulate total difference for display
      grandTotal3d += stod(get<4>(reportRecord_BC[i]));
      
      // Percentage (actual amount / budget)
      if (stod(get<3>(reportRecord_BC[i])) > 0)
      {
        percentage = 100 * ( stod(get<2>(reportRecord_BC[i])) / stod(get<3>(reportRecord_BC[i])));
        
        if (percentage < 1000)     // If percentage > 1000%, stop showing '.'
        {
          get<5>(reportRecord_BC[i]) = to_string(percentage);
          get<5>(reportRecord_BC[i]) = utility1.formatStringToDecimal(get<5>(reportRecord_BC[i]), 2);
        }
        else if (percentage < 1000000)     // If percentage > 1000000%
        {
          get<5>(reportRecord_BC[i]) = to_string(int(percentage));
        }
        else
        {
          get<5>(reportRecord_BC[i]) = "******";
        }
      }
    }
    
    grandTotal3s = utility1.formatStringToDecimal(  to_string( grandTotal3d ), 2);
    
    
    file2.close();
    
    // Sort Account Code list by first column (Account Code)
    sort(reportRecord_BC.begin(), reportRecord_BC.end());
  }
  else
  {
    cout << "> Error!  Unable to open file";
    system("PAUSE");
    return;
  }
  
  
  //----------
  // Display report
  //----------
  system("cls");
  if (accountType == "E")     cout << "MONTHLY BUDGET CONTROL REPORT - EXPENSES (Period: " << monthYear << "):" << endl;
  else                        cout << "MONTHLY BUDGET CONTROL REPORT - INCOMES (Period: " << monthYear << "):" << endl;
  cout << "***********************************************************************************************************" << endl;
  cout << "ACCOUNT  DESCRIPTION                          ACTUAL(a)       BUDGET(b)      DIFF.(b-a)  (a/b%)  SHOW ALERT" << endl;
  cout << "-------  ------------------------------  --------------  --------------  --------------  ------  ----------" << endl;
  
  for (int i = 0; i < reportRecord_BC.size(); i++)
  {
    get<1>(reportRecord_BC[i]) = utility1.padRight( get<1>(reportRecord_BC[i]) , ' ', acctFldLen1.acctDesc);
    get<2>(reportRecord_BC[i]) = utility1.padLeft ( utility1.formatDouble(  stod( get<2>(reportRecord_BC[i]) ),  2) , ' ', 14);
    get<3>(reportRecord_BC[i]) = utility1.padLeft ( utility1.formatDouble(  stod( get<3>(reportRecord_BC[i]) ),  2) , ' ', 14);     // move space to left + display with thousand separators (xxx,xxx,xxx.xx)
    get<4>(reportRecord_BC[i]) = utility1.padLeft ( utility1.formatDouble(  stod( get<4>(reportRecord_BC[i]) ),  2) , ' ', 14);     // move space to left + display with thousand separators (xxx,xxx,xxx.xx)
    get<5>(reportRecord_BC[i]) = utility1.padLeft ( get<5>(reportRecord_BC[i]) , ' ', 6);      // move space to left + display with thousand separators (xxx,xxx,xxx.xx)
    
    cout << get<0>(reportRecord_BC[i]) << "     "       // acctCode
  			 << get<1>(reportRecord_BC[i]) << "  "          // acctDesc
         << get<2>(reportRecord_BC[i]) << "  "          // Actual total amount
         << get<3>(reportRecord_BC[i]) << "  "          // Budget
         << get<4>(reportRecord_BC[i]) << "  "          // Difference
         << get<5>(reportRecord_BC[i]) << "      "     // Percentage
         << get<6>(reportRecord_BC[i]) << ""            // Alert Value
         << "\n";
  }
  grandTotal1s             = utility1.padLeft ( utility1.formatDouble(  stod(grandTotal1s), 2) , ' ', 14);                     // move space to left + display with thousand separators (xxx,xxx,xxx.xx)
  grandTotal2s             = utility1.padLeft ( utility1.formatDouble(  stod(grandTotal2s), 2) , ' ', 14);                     // move space to left + display with thousand separators (xxx,xxx,xxx.xx)
  grandTotal3s             = utility1.padLeft ( utility1.formatDouble(  stod(grandTotal3s), 2) , ' ', 14);                     // move space to left + display with thousand separators (xxx,xxx,xxx.xx)
  cout << "-----------------------------------------------------------------------------------------------------------\n"
       << "                                  Total: " << grandTotal1s << "  " << grandTotal2s << "  " << grandTotal3s << "\n"
       << "                                         ==============  ==============  ==============\n"
       << "Note: '******' = perceentage >= 1000000%" << endl;
  
  
  //--------
  // Exit
  //--------
  while (true)
  {
    cout << "Enter X to exit." << endl;
    getline (cin, choice1);
    // Exit
    if (choice1=="X" ||
        choice1=="x")
    {
      //recordList_Trans.clear();
      cout << "\n";
      cout.flush();
      return;     // exit
    }
  }
}


//-------------------------------------------------------------------------------------//
// Generate Total Amount
//-------------------------------------------------------------------------------------//
double Report::get_accountTotal(string accountCode, string monthYear)
{
  string dataRow;
  double totalAmount = 0;
  transRec1.initialize();
  transFldLen1.initialize();
  
  ifstream file1 (transaction1.filename_Transaction);
  if (file1.is_open())
  {
    //----------
    // Loop to extract Transaction total to array...
    //----------
    
    while ( getline (file1, dataRow) )
    {
      if (utility1.trim(dataRow)=="")
      {
        continue;    // skip if space line
      }
      //
      // Split data line into column values
      transaction1.split_DataRow_to_Fields(dataRow, transRec1);
      
      if (transRec1.acctCode1 != accountCode && transRec1.acctCode2 != accountCode)     continue;
      if (monthYear.length() == 7 && transRec1.transDate.substr(3, 7) != monthYear)     continue;
      if (monthYear.length() == 4 && transRec1.transDate.substr(6, 4) != monthYear)     continue;
      //
      // accumulate total
      totalAmount += stod(transRec1.amount);
    }
    file1.close();
  }    
  else
  {
    cout << "> Error!  Unable to open file" << transaction1.filename_Transaction << endl;
    return 0;
  }
  
  return totalAmount;
}
