//-----------------------------------------------------------------------
// Description : Accounting System - Budget Master - Class
// Last Modified: 2019-04-26
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
#include "BudgetMaster.h"
#include "AccountMaster.h"
#include "Utility.h"
#include <bits/stdc++.h> 

using namespace std;

Utility utility1;
AccountMaster accountMaster1;

// Budget master record structure   (details definition: pls check header file)
struct BudgetMaster::BudgetMasterRecord bdgtRec1;
struct BudgetMaster::BudgetMasterFldLen bdgtFldLen1;
struct BudgetMaster::BudgetMasterFldChg bdgtFldChg1;

//vector<tuple<string, string, string, string> > recordList;
vector<tuple<string, string, string, string> > recordList_Budget;


//-------------------------------------------------------------------------------------//
// Sub-menu:  ACCOUNT CODE
//-------------------------------------------------------------------------------------//
void BudgetMaster::Menu()
{
    char selection;
    
    bdgtRec1.initialize();
    bdgtFldLen1.initialize();
    bdgtFldChg1.initialize();
    
    //-------------------
    // Loop: Display menu and selection option 
    //-------------------
    while (true)
    {
        // Display menu
        system("cls");
        cout << "|-------------------------------------------------------------------------|" << endl;
        cout << "|           ACCOUNTING SYSTEM - MAINTAIN BUDGET MASTER RECORDS            |" << endl;
        cout << "|-------------------------------------------------------------------------|" << endl;
        cout << "|***           Welcome to HKU Simple Accounting System (2019)          ***|" << endl;
        cout << "|***  This system is developed by ENGG1340 Class No.XXXXX Group No.XX  ***|" << endl;
        cout << "|-------------------------------------------------------------------------|" << endl;
        cout << "|                                                                         |" << endl;
        cout << "|  Options:                                                               |" << endl;
        cout << "|           1. Add New Budget Record                                      |" << endl;
        cout << "|           2. Change Budget Record                                       |" << endl;
        cout << "|           3. Delete Budget Record                                       |" << endl;
        cout << "|           4. Search / List Records                                      |" << endl;
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
                Add_BudgetMaster();
                continue;
            case '2' :
                cout.flush();
                cin.ignore();
                Change_BudgetMaster();
                continue;
            case '3' :
                cout.flush();
                cin.ignore();
                Delete_BudgetMaster();
                continue;
            case '4' :
                cout.flush();
                cin.ignore();
                Search_BudgetMaster();
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
// Add Budget Master Record
//-------------------------------------------------------------------------------------//
void BudgetMaster::Add_BudgetMaster()
{
  int counter1 = 0;
  string choice1 = "";
  string choice2 = "";
  string input1 = "";
  string AcctCode = "";
  string Year = "";
  string newValueA = "";
  int    numValue1 = 0;
  int    numValue2 = 0;
  int    numValue3 = 0;
  bdgtFldLen1.initialize();



  //----------
  // ADD - Account Code Record
  //----------
  while (true)
  {
    //----------
    // Input - Account Code
    //----------
    system("cls");
    counter1 = 1;
    bdgtRec1.initialize();   //clear all field values
    while (true)
    {
      // input Account code  (Primary Key)
      cout << "\n";
      cout << "Please enter below to create an Account code record." << endl;
      cout << counter1 << ") Account Code: ";
      getline (cin, AcctCode);
  
      if (AcctCode.length()<1)
      {
        cout << "> Invalid Account code.  Cannot be empty." << endl;
        cout << "Retry? (Y/N): ";
        getline (cin, choice1);
        if (choice1 == "N" || choice1 == "n")      return;                // exit
        else                                       continue;



        cout.flush();
        continue;
      }        
      if (AcctCode.length()!=bdgtFldLen1.acctCode)
      {
        cout << "> Invalid Account code. Input must be exactly " << bdgtFldLen1.acctCode << " characters. Please retry." << endl;
        cout.flush();
        continue;
      }        
      if (accountMaster1.isValid_AccountMasterKey2(AcctCode)==false)    
      {
        cout << "> Error - Account code is not valid. Please retry." << endl;
        cout.flush();
        continue;
      }
      bdgtRec1.acctCode = AcctCode;
      break;
    }
    
    //----------
    // Input - Budget Year
    //----------
    counter1++;
    while (true)
    {
      // input 
      cout << "\n";
      cout << counter1 << ") Budget Year (2019-2100): ";
      getline (cin, Year);
      
      Year = utility1.trim(Year);
      if (Year == "")
      {
        cout << "> Invalid Budget Year. Cannot be empty. Please retry." << endl;
        cout.flush();
        continue;
      }        
      if (Year.length()>bdgtFldLen1.year)
      {
        cout << "> Invalid Budget Year. Maxi. " << bdgtFldLen1.year << " characters. Please retry." << endl;
        cout.flush();
        continue;
      }
	  if (utility1.isNumber(Year, false, false)==false)
      {
        cout << "> Budget Year must be in numeric value. Please retry." << endl;
        cout.flush();
        continue;
      }   
      if (stoi(Year)<2019 || stoi(Year)>2100)
      {
        cout << "> Budget Year out of range. Please retry." << endl;
        cout.flush();
        continue;
      }        

      bdgtRec1.year = Year;
      break;
    }
    
    //----------
    // Check record existence by primary key 
    //----------
    if (isValid_BudgetMasterKey(AcctCode, Year))
    {
      cout << "> Error - Budget record already exists (Account code + Year)." << endl;
      cout << "Retry? (Y/N): ";
      getline (cin, choice1);
      if (choice1 == "N" || choice1 == "n")      return;                // exit
      else                                       continue;
    }
	
    
    //----------
    // Input - Budget Amount
    //----------
    counter1++;
    while (true)
    {
      // input 
      cout << "\n";
      cout << counter1 << ") Budget Amount (1-999999.99): ";
      getline (cin, input1);
      
      input1 = utility1.trim(input1);
      if (input1 == "")
      {
        cout << "> Invalid Budget Amount. Cannot be empty. Please retry." << endl;
        cout.flush();
        continue;
      }        
      if (input1.length()>bdgtFldLen1.amount)
      {
        cout << "> Invalid Budget Amount. Maxi. " << bdgtFldLen1.amount << " characters. Please retry." << endl;
        cout.flush();
        continue;
      }        
      if (utility1.isNumber(input1, false, true)==false)
      {
        cout << "> Budget Amount is not a numeric value. Please retry." << endl;
        cout.flush();
        continue;
      }   
      if (stod(input1)==0)
      {
        cout << "> Budget Amount must > 0. Please retry." << endl;
        cout.flush();
        continue;
      }        
      if (stod(input1)>999999.99)
      {
        cout << "> Budget Amount cannot exceed 999999.99. Please retry." << endl;
        cout.flush();
        continue;
      }

      bdgtRec1.amount = utility1.formatStringToDecimal(input1, 2);
      break;
    }
    
    //----------
    // Input - Alert
    //----------
    counter1++;
    while (true)
    {
      // input 
      cout << "\n";
      cout << counter1 << ") Display Over-budget Warning (Y/N): ";
      getline (cin, input1);
      
      input1 = utility1.trim(input1);
      if (input1 == "")
      {
        cout << "> Invalid Over-budget Alert Value. Cannot be empty. Please retry." << endl;
        cout.flush();
        continue;
      }        
      if (input1.length()>bdgtFldLen1.alert)
      {
        cout << "> Invalid Over-budget Alert Value. Maxi. " << bdgtFldLen1.alert << " characters. Please retry." << endl;
        cout.flush();
        continue;
      }
      if (input1 != "Y" && input1 != "N" && input1 != "y" && input1 != "n")
      {
        cout << "> Invalid Over-budget Alert Value. Must type 'Y' or 'N'. Please retry." << endl;
        cout.flush();
        continue;
      }
      if (input1 == "y")
      {
        input1 = "Y";
      }
      if (input1 == "n")
      {
        input1 = "N";
      }
      
      bdgtRec1.alert = input1;
      break;
    }
    
    //----------
    // Append data to file
    //----------
    choice1 = " ";
    while (true)
    {
      cout << "\nSAVE data?  (Y=create record, N=abandon): ";
      getline (cin, choice1);
  
      if (choice1!="Y" && choice1!="y" &&
          choice1!="N" && choice1!="n")
      {
        cout.flush();
        continue;
      }      
      else if (choice1=="N" || choice1=="n") 
      {
        cout << "\nAbandon confirm?  (Y/N): ";
        getline (cin, choice2);
        if (choice2=="Y" || choice2=="y")
        {
          break;
        }
      }
      else if (choice1=="Y" || choice1=="y")      
      {
        add_Record(bdgtRec1);
        break;
      }
    }  


    //----------
    // More to add?
    //----------
    choice1 = " ";
    while (true)
    {
      choice1 = " ";
      cout << "\nAdd another Record (Y/N): ";
      getline (cin, choice1);
  
      if (choice1!="Y" && choice1!="y" &&
          choice1!="N" && choice1!="n")
      {
        cout.flush();
        continue;
      }
      break;
    }
    if (choice1=="N" || choice1=="n")
    {
      break;          // exit ADD function
    }
  }
}

//-------------------------------------------------------------------------------------//
// Modify Budget Master Record
//-------------------------------------------------------------------------------------//
void BudgetMaster::Change_BudgetMaster()
{
  string choice1 = "";
  string choice2 = "";
  string input  = "";
  string accountCode = "";
  string targetYear = "";
  string newValueA = "";
  int    numValue1 = 0;
  int    numValue2 = 0;
  int    numValue3 = 0;
  bool   isDone;
  bdgtFldLen1.initialize();

  //----------
  // User selection
  //----------
  system("cls");
  while (true)
  {
    // clear all field values
    bdgtRec1.initialize();
            
    // How to search
    cout << "\n";
    cout << "List by:  1) Account Code,   L) List all records," << endl;
    cout << "          2) Year,           X) Exit" << endl;
    cout << "Selection: ";
    
    getline (cin, choice1);

    //
    if (choice1 != "1" &&
        choice1 != "2" &&
        choice1 != "L" && choice1 != "l" &&
        choice1 != "X" && choice1 != "x")
    {
      cout << "> Invalid choice1. Please try again." << endl;
      system("pause");
      system("cls");
      cout.flush();
      continue;
    }
    
    //----------
    // Exit
    //----------
    if (choice1=="X" ||
        choice1=="x")
    {
      cout << "\n";
      cout.flush();
      return;     // exit
    }
    
    //----------
    // List all records
    //----------
    if (choice1=="L" ||
        choice1=="l")
    {
      List_Records(false);         // list all records, do not show detail
    }
    //----------
    // List by Account Code  (Filter / Search)
    //----------
    else if (choice1=="1")
    {
      while (true)
      {
        cout << "Please enter Account Code to list. Enter 'X' to exit.: ";
      // read the input
      getline (cin, input);
      
      if (input=="X" ||
          input=="x")
      {
        cout << "\n";
        cout.flush();
        return;     // exit
      }
      
      // is valid input?
      if (utility1.trim(input)=="")
      {
        cout << "> Invalid account code.  Cannot be empty." << endl;
        cout << "Retry? (Y/N): ";
        getline (cin, choice2);
        if (choice2 == "N" || choice2 == "n")      return;                // exit
        else                                       continue;
      }
      
      // Lookup the Account Code
      if (accountMaster1.isValid_AccountMasterKey2(input)==false)
      {
        cout << "> Account Code not found." << endl;
        cout << "Retry? (Y/N): ";
        getline (cin, choice2);
        if (choice2 == "N" || choice2 == "n")      return;                // exit
        else                                       continue;
      }
      
      List_Records("AcctCode", input, false);        // list filter by AcctCode (Account Code), do not show detail
      break;
      }
    }
    //----------
    // List by Year  (Filter / Search)
    //----------
    else if (choice1=="2")
    {
      while (true)
      {
        cout << "Please enter Year to list: ";
        // read the input
        getline (cin, input);
    
        // is input valid?
        if (utility1.trim(input)=="")
        {
          cout << "> Invalid Year.  Cannot be empty." << endl;
          cout << "Retry? (Y/N): ";
          cin.ignore();
          getline (cin, choice1);
          if (choice1 == "N" || choice1 == "n")      break;                // exit
          else                                       continue;
        }
        
        List_Records("Year", input, false);        // list filter by Year, do not show detail
        break;
      }
    }
    
    //----------
    // Lookup Primary Key (Account Code and Year) to Edit
    //----------
    bdgtRec1.initialize();
    bdgtFldChg1.initialize();
    while (true)
    {
      cout << "Please select the account code and the year of the record to EDIT." << endl;
      cout << "Enter 'X' now to exit." << endl;
      cout << "Please enter Account Code: ";
      // read the input
      getline (cin, input);
      
      if (input=="X" ||
          input=="x")
      {
        cout << "\n";
        cout.flush();
        return;     // exit
      }
      
      // is valid input?
      if (utility1.trim(input)=="")
      {
        cout << "> Invalid account code.  Cannot be empty." << endl;
        cout << "Retry? (Y/N): ";
        getline (cin, choice2);
        if (choice2 == "N" || choice2 == "n")      return;                // exit
        else                                       continue;
      }
      
      // Lookup the Account Code
      if (accountMaster1.isValid_AccountMasterKey2(input)==false)
      {
        cout << "> Account Code not found." << endl;
        cout << "Retry? (Y/N): ";
        getline (cin, choice2);
        if (choice2 == "N" || choice2 == "n")      return;                // exit
        else                                       continue;
      }
      
      accountCode = input;
      
      cout << "Please also enter Year (2019 - 2100): ";
      // read the input
      getline (cin, input);
      
      // is valid input?
      if (utility1.trim(input)=="")
      {
        cout << "> Invalid year.  Cannot be empty." << endl;
        cout << "Retry? (Y/N): ";
        getline (cin, choice2);
        if (choice2 == "N" || choice2 == "n")      return;                // exit
        else                                       continue;
      }
      
      targetYear = input;
      
      // Lookup the Primary Key (Account Code + Year)
      if (isValid_BudgetMasterKey2(accountCode, targetYear)==false)
      {
        cout << "> Budget Record of Account Code entered not found." << endl;
        cout << "Retry? (Y/N): ";
        getline (cin, choice2);
        if (choice2 == "N" || choice2 == "n")      return;                // exit
        else                                       continue;
      }
      
      break;    
    }
    
    // Get the Account Code details
    getRec_by_BudgetMasterKey(accountCode, targetYear, bdgtRec1);
    
    //-----------
    // Start to EDIT...
    //-----------
    while (true)
    {
      system("cls");
      cout << "EDIT Budget record:" << endl;
      cout << "*****************************************************" << endl;
      cout <<                           "Account Code .................: " << bdgtRec1.acctCode    << endl;
      cout <<                           "Year .........................: " << bdgtRec1.year    << endl;
      cout << "" << endl;
      cout << bdgtFldChg1.amount   << " 1) Amount ...................: " << bdgtRec1.amount    << endl;
      cout << bdgtFldChg1.alert    << " 2) Over-budget Alert ........: " << bdgtRec1.alert     << endl;
      cout << "*****************************************************" << endl; 
      cout << "Select which field (1-2) to change and press <Enter>." << endl;
      cout << "Enter  S=save, X=exit/abort " << endl;
      cout << "Select: ";
      //
      //cin.ignore();
      getline (cin, choice2);
      
      //----------
      // Exit
      //----------
      if (choice2=="X" || choice2=="x")
      {
        cout << "\nExit now?  (Y/N): " << endl;
        getline (cin, choice2);
        if (choice2!="Y" && choice2!="y")
        {
          continue;
        }
        
        // Exit...
        cout << "\n";
        cout.flush();
        break;     // exit
      }

      //----------
      // Save new values
      //----------
      if (choice2=="S" || choice2=="s")
      {
        cout << "\nSave new values to file?  Please confirm.  (Y/N): " << endl;
        getline (cin, choice2);
        if (choice2!="Y" && choice2!="y")
        {
          continue;
        }
        
        // Save...
        cout << "\nSaving new values to file.  Please wait..." << endl;
        change_Record(bdgtRec1);


        cout << "New values are saved successfully to file." << endl;
        cout << "Press <Enter> to continue." << endl;
        getline (cin, choice2);
        cout << "\n";
        cout.flush();
        break;     // saved & exit
      }
      
      // is selected field number valid? 
      if (choice2.empty() ||
          utility1.isNumber(choice2, false, false)==false || 
          stoi(choice2) <= 0 || stoi(choice2) > 2)
      {
        cout << "> Invalid selection. Valid field number is (1-2).  Please <Enter> to retry." << endl;
        getline (cin, choice2);
        cout << "\n";
        continue;
      }
      
      //----------
      // Input new value
      //----------
      isDone = false;
      while (isDone==false)
      {
        switch (stoi(choice2))
        {
          case 1:
            cout << "Budget Amount ..............: " + bdgtRec1.amount << endl;
            cout << "Enter new value (1-999999.99): ";
            getline (cin, newValueA);
            newValueA = utility1.trim(newValueA);
            if (newValueA == "")
            {
              cout << "> Invalid Budget Amount. Cannot be empty. Please retry." << endl;
              cout.flush();
              continue;
            }        
            if (newValueA.length()>bdgtFldLen1.amount)
            {
              cout << "> Invalid Budget Amount. Maxi. " << bdgtFldLen1.amount << " characters. Please retry." << endl;
              cout.flush();
              continue;
            }        
            if (utility1.isNumber(newValueA, false, true)==false)
            {
              cout << "> Budget Amount is not a numeric value. Please retry." << endl;
              cout.flush();
              continue;
            }   
            if (stod(newValueA)==0)
            {
              cout << "> Budget Amount must > 0. Please retry." << endl;
              cout.flush();
              continue;
            }      
            if (stod(newValueA)>999999.99)
            {
              cout << "> Budget Amount cannot exceed 999999.99. Please retry." << endl;
              cout.flush();
              continue;
            }
            
            bdgtRec1.amount = utility1.formatStringToDecimal(newValueA, 2);
            bdgtFldChg1.amount = '*';
            isDone = true;
            break;

          case 2:
            cout << "Over-budget Alert ................: " + bdgtRec1.alert << endl;
            cout << "Enter new value (Y/N): ";
            getline (cin, newValueA);
            newValueA = utility1.trim(newValueA);
            if (newValueA.length()!=bdgtFldLen1.alert)
            {
              cout << "> Invalid Over-budget Alert Value. Input must be 'Y' or 'N'. Please retry." << endl;
              cout.flush();
              continue;
            }
      			if (newValueA != "Y" && newValueA != "N" && newValueA != "y" && newValueA != "n")
      			{
      				cout << "> Invalid Over-budget Alert Value. Must type 'Y' or 'N'. Please retry." << endl;
      				cout.flush();
      				continue;
      			}
      			if (newValueA == "y")
      			{
      				newValueA = "Y";
      			}
      			if (newValueA == "n")
      			{
      				newValueA = "N";
      			}
            
            bdgtRec1.alert = newValueA;
            bdgtFldChg1.alert = '*';
            isDone = true;
            break;
            
        }
      }
    }
    
    //----------
    // More to change?
    //----------
    choice2 = " ";
    while (true)
    {
      choice2 = " ";
      cout << "\nModify another Record (Y/N): ";
      getline (cin, choice2);
  
      if (choice2!="Y" && choice2!="y" &&
          choice2!="N" && choice2!="n")
      {
        cout.flush();
        continue;
      }      
      break;
    }
    if (choice2=="N" || choice2=="n")
    {
      break;          // exit Modify function
    }        

    system("cls");
    
  }   // loop: Select next Account Codeing record to modify
}

//-------------------------------------------------------------------------------------//
// Delete Budget Master Record
//-------------------------------------------------------------------------------------//
void BudgetMaster::Delete_BudgetMaster()
{
  string choice1 = "";
  string choice2 = "";
  string input  = "";
  string accountCode = "";
  string targetYear = "";
  bool   isDone;
  bdgtFldLen1.initialize();

  //----------
  // User selection
  //----------
  system("cls");
  while (true)
  {
    // clear all field values
    bdgtRec1.initialize();
            
    // How to search
    cout << "\n";
    cout << "List by:  1) Account Code,   L) List all records," << endl;
    cout << "          2) Year,           X) Exit" << endl;
    cout << "Selection: ";
    
    getline (cin, choice1);

    //
    if (choice1 != "1" &&
        choice1 != "2" &&
        choice1 != "L" && choice1 != "l" &&
        choice1 != "X" && choice1 != "x")
    {
      cout << "> Invalid choice1. Please try again." << endl;
      system("pause");
      system("cls");
      cout.flush();
      continue;
    }
    
    //----------
    // Exit
    //----------
    if (choice1=="X" ||
        choice1=="x")
    {
      cout << "\n";
      cout.flush();
      return;     // exit
    }
    
    //----------
    // List all records
    //----------
    if (choice1=="L" ||
        choice1=="l")
    {
      List_Records(false);         // list all records, do not show detail
    }
    //----------
    // List by Account Code  (Filter / Search)
    //----------
    else if (choice1=="1")
    {
      while (true)
      {
        cout << "Please enter Account Code to list. Enter 'X' to exit.: ";
      // read the input
      getline (cin, input);
      
      if (input=="X" ||
          input=="x")
      {
        cout << "\n";
        cout.flush();
        return;     // exit
      }
      
      // is valid input?
      if (utility1.trim(input)=="")
      {
        cout << "> Invalid account code.  Cannot be empty." << endl;
        cout << "Retry? (Y/N): ";
        getline (cin, choice2);
        if (choice2 == "N" || choice2 == "n")      return;                // exit
        else                                       continue;
      }
      
      // Lookup the Account Code
      if (accountMaster1.isValid_AccountMasterKey2(input)==false)
      {
        cout << "> Account Code not found." << endl;
        cout << "Retry? (Y/N): ";
        getline (cin, choice2);
        if (choice2 == "N" || choice2 == "n")      return;                // exit
        else                                       continue;
      }
      
      List_Records("AcctCode", input, false);        // list filter by AcctCode (Account Code), do not show detail
      break;
      }
    }
    //----------
    // List by Year  (Filter / Search)
    //----------
    else if (choice1=="2")
    {
      while (true)
      {
        cout << "Please enter Year to list: ";
        // read the input
        getline (cin, input);
    
        // is input valid?
        if (utility1.trim(input)=="")
        {
          cout << "> Invalid Year.  Cannot be empty." << endl;
          cout << "Retry? (Y/N): ";
          cin.ignore();
          getline (cin, choice1);
          if (choice1 == "N" || choice1 == "n")      break;                // exit
          else                                       continue;
        }
        
        List_Records("Year", input, false);        // list filter by Year, do not show detail
        break;
      }
    }
    
    //----------
    // Lookup Primary Key (Account Code and Year) to Delete
    //----------
    bdgtRec1.initialize();
    while (true)
    {
      cout << "Please select the account code and the year of the record to DELETE." << endl;
      cout << "Enter 'X' now to exit." << endl;
      cout << "Please enter Account Code: ";
      // read the input
      getline (cin, input);
      
      if (input=="X" ||
          input=="x")
      {
        cout << "\n";
        cout.flush();
        return;     // exit
      }
      
      // is valid input?
      if (utility1.trim(input)=="")
      {
        cout << "> Invalid account code.  Cannot be empty." << endl;
        cout << "Retry? (Y/N): ";
        getline (cin, choice2);
        if (choice2 == "N" || choice2 == "n")      return;                // exit
        else                                       continue;
      }
      
      // Lookup the Account Code
      if (accountMaster1.isValid_AccountMasterKey2(input)==false)
      {
        cout << "> Account Code not found." << endl;
        cout << "Retry? (Y/N): ";
        getline (cin, choice2);
        if (choice2 == "N" || choice2 == "n")      return;                // exit
        else                                       continue;
      }  
      
      accountCode = input;
      
      cout << "Please also enter Year (2019 - 2100): ";
      // read the input
      getline (cin, input);
      
      // is valid input?
      if (utility1.trim(input)=="")
      {
        cout << "> Invalid year.  Cannot be empty." << endl;
        cout << "Retry? (Y/N): ";
        getline (cin, choice2);
        if (choice2 == "N" || choice2 == "n")      return;                // exit
        else                                       continue;
      }
      
      targetYear = input;
      
      // Lookup the Primary Key (Account Code + Year)
      if (isValid_BudgetMasterKey2(accountCode, targetYear)==false)
      {
        cout << "> Budget Record of Account Code entered not found." << endl;
        cout << "Retry? (Y/N): ";
        getline (cin, choice2);
        if (choice2 == "N" || choice2 == "n")      return;                // exit
        else                                       continue;
      }
      
      break;    
    }
    
    // Get the Account Code details
    getRec_by_BudgetMasterKey(accountCode, targetYear, bdgtRec1);
    
    //-----------
    // Display
    //-----------
    while (true)
    {
      system("cls");
      cout << "DELETE Budget record:" << endl;
      cout << "*****************************************************" << endl;
      cout << "Account Code .................: " << bdgtRec1.acctCode << endl;
      cout << "Year .........................: " << bdgtRec1.year     << endl;
      cout << "Amount .......................: " << bdgtRec1.amount   << endl;
      cout << "Over-budget Alert ............: " << bdgtRec1.alert    << endl;
      cout << "*****************************************************" << endl; 
      cout << "Enter  D=delete record, X=exit/abort " << endl;
      cout << "Select: ";
      //
      //cin.ignore();
      getline (cin, choice2);
      
      //----------
      // Exit
      //----------
      if (choice2=="X" || choice2=="x")
      {
        cout << "\nExit now?  (Y/N): " << endl;
        getline (cin, choice2);
        if (choice2!="Y" && choice2!="y")
        {
          continue;
        }
        
        // Exit...
        cout << "\n";
        cout.flush();
        break;     // exit
      }

        


      
      // invalid selection
      if (choice2!="D" && choice2!="d")
      {
        cout << "> Invalid selection. Please <Enter> to retry." << endl;
        getline (cin, choice2);
        cout << "\n";
        continue;
      }
      
      //----------
      // DELETE record
      //----------

      cout << "\nDELETE confirm?  (Y/N): " << endl;
      getline (cin, choice2);
      if (choice2!="Y" && choice2!="y")
      {
        continue;
      }        
      
      // Delete...
      delete_Record(accountCode, targetYear);


      cout << "> Selected record is deleted." << endl;
      cout << "\n";
      cout.flush();
      
      break;
      
    }   // loop: Delete record
    
    //----------
    // More to delete?
    //----------
    choice2 = " ";
    while (true)
    {
      choice2 = " ";
      cout << "\nDelete another Record (Y/N): ";
      getline (cin, choice2);
  
      if (choice2!="Y" && choice2!="y" &&
          choice2!="N" && choice2!="n")
      {
        cout.flush();
        continue;
      }      
      break;
    }
    if (choice2=="N" || choice2=="n")
    {
      break;          // exit Modify function
    }        

    system("cls");
    
  }   // loop: Select next Account Codeing record to delete
}

//-------------------------------------------------------------------------------------//
// Search Budget Master Record
//-------------------------------------------------------------------------------------//
void BudgetMaster::Search_BudgetMaster()
{
  string choice1 = "";
  string choice2 = "";
  string input  = "";
  string accountCode = "";
  string targetYear = "";
  bdgtFldLen1.initialize();

  //----------
  // User selection
  //----------
  system("cls");
  while (true)
  {
    // clear all field values
    bdgtRec1.initialize();
            
    // How to search
    cout << "\n";
    cout << "Search by:  1) Account Code,   L) List all records," << endl;
    cout << "            2) Year,           X) Exit" << endl;
    cout << "Selection: ";
    
    getline (cin, choice1);

    //
    if (choice1 != "1" &&
        choice1 != "2" &&
        choice1 != "L" && choice1 != "l" &&
        choice1 != "X" && choice1 != "x")
    {
      cout << "> Invalid choice1. Please try again." << endl;
      system("pause");
      system("cls");
      cout.flush();
      continue;
    }
    
    //----------
    // Exit
    //----------
    if (choice1=="X" ||
        choice1=="x")
    {
      cout << "\n";
      cout.flush();
      return;     // exit
    }
    
    //----------
    // List all records
    //----------
    if (choice1=="L" ||
        choice1=="l")
    {
      List_Records(true);         // list all records, show detail
      continue;              // loop back to search menu
    }
    //----------
    // List by Account Code  (Filter / Search)
    //----------
    else if (choice1=="1")
    {
      while (true)
      {
        cout << "Please enter Account Code to list. Enter 'X' to exit.: ";
      // read the input
      getline (cin, input);
      
      if (input=="X" ||
          input=="x")
      {
        cout << "\n";
        cout.flush();
        return;     // exit
      }
      
      // is valid input?
      if (utility1.trim(input)=="")
      {
        cout << "> Invalid account code.  Cannot be empty." << endl;
        cout << "Retry? (Y/N): ";
        getline (cin, choice2);
        if (choice2 == "N" || choice2 == "n")      return;                // exit
        else                                       continue;
      }
      
      // Lookup the Account Code
      if (accountMaster1.isValid_AccountMasterKey2(input)==false)
      {
        cout << "> Account Code not found." << endl;
        cout << "Retry? (Y/N): ";
        getline (cin, choice2);
        if (choice2 == "N" || choice2 == "n")      return;                // exit
        else                                       continue;
      }
      
      List_Records("AcctCode", input, false);        // list filter by AcctCode (Account Code), do not show detail
      break;
      }
    }
    //----------
    // List by Year  (Filter / Search)
    //----------
    else if (choice1=="2")
    {
      while (true)
      {
        cout << "Please enter Year to list: ";
        // read the input
        getline (cin, input);
    
        // is input valid?
        if (utility1.trim(input)=="")
        {
          cout << "> Invalid Year.  Cannot be empty." << endl;
          cout << "Retry? (Y/N): ";
          cin.ignore();
          getline (cin, choice1);
          if (choice1 == "N" || choice1 == "n")      break;                // exit
          else                                       continue;
        }
        
        List_Records("Year", input, false);        // list filter by Year, do not show detail
        break;
      }
    }
    
    //----------
    // Lookup Primary Key (Account Code and Year) to display details
    //----------
    bdgtRec1.initialize();
    bdgtFldChg1.initialize();
    while (true)
    {
      cout << "Please select the account code and the year of the record to search." << endl;
      cout << "Enter 'X' now to exit." << endl;
      cout << "Please enter Account Code: ";
      // read the input
      getline (cin, input);
      
      if (input=="X" ||
          input=="x")
      {
        cout << "\n";
        cout.flush();
        return;     // exit
      }
      
      // is valid input?
      if (utility1.trim(input)=="")
      {
        cout << "> Invalid account code.  Cannot be empty." << endl;
        cout << "Retry? (Y/N): ";
        getline (cin, choice2);
        if (choice2 == "N" || choice2 == "n")      return;                // exit
        else                                       continue;
      }
      
      // Lookup the Account Code
      if (accountMaster1.isValid_AccountMasterKey2(input)==false)
      {
        cout << "> Account Code not found." << endl;
        cout << "Retry? (Y/N): ";
        getline (cin, choice2);
        if (choice2 == "N" || choice2 == "n")      return;                // exit
        else                                       continue;
      }  
      
      accountCode = input;
      
      cout << "Please also enter Year (2019 - 2100): ";
      // read the input
      getline (cin, input);
      
      // is valid input?
      if (utility1.trim(input)=="")
      {
        cout << "> Invalid year.  Cannot be empty." << endl;
        cout << "Retry? (Y/N): ";
        getline (cin, choice2);
        if (choice2 == "N" || choice2 == "n")      return;                // exit
        else                                       continue;
      }
      
      targetYear = input;
      
      // Lookup the Primary Key (Account Code + Year)
      if (isValid_BudgetMasterKey2(accountCode, targetYear)==false)
      {
        cout << "> Budget Record of Account Code entered not found." << endl;
        cout << "Retry? (Y/N): ";
        getline (cin, choice2);
        if (choice2 == "N" || choice2 == "n")      return;                // exit
        else                                       continue;
      }
      
      break;    
    }
    
    // Get the Account Code details
    getRec_by_BudgetMasterKey(accountCode, targetYear, bdgtRec1);
    
    //-----------
    // Display  (Found)
    //-----------
    while (true)
    {
      system("cls");
      cout << "Budget record details:" << endl;
      cout << "*****************************************************" << endl;
      cout << "Account Code .................: " << bdgtRec1.acctCode  << endl;
      cout << "Year .........................: " << bdgtRec1.year      << endl;
      cout << "Amount .......................: " << bdgtRec1.amount    << endl;
      cout << "Over-budget Alert ............: " << bdgtRec1.alert     << endl;
      cout << "*****************************************************" << endl; 
      cout << "Press <Enter> to continue." << endl;
      
      getline (cin, choice2);
      system("cls");
	    break;
	  }
  }   // loop to search next record
}

//-------------------------------------------------------------------------------------//
// Display Record in Detail
//-------------------------------------------------------------------------------------//
void BudgetMaster::Display_BudgetMaster(string accountCode, string targetYear)
{
  string  choice;
  bdgtRec1.initialize();

  getRec_by_BudgetMasterKey(accountCode, targetYear, bdgtRec1);
  if (utility1.trim(bdgtRec1.acctCode)=="")
  {
    cout << "> Invalid Account Code." << endl;
    system("pause");
    return;
  }
  if (utility1.trim(bdgtRec1.year)=="")
  {
    cout << "> Invalid Year." << endl;
    system("pause");
    return;
  }
  
  //----------
  // Display Budget Record detail
  //----------
  while (true) 
  {
    system("cls");
    cout << "Budget record details:" << endl;
    cout << "*****************************************************" << endl;
    cout << "Account Code .................: " << bdgtRec1.acctCode  << endl;
    cout << "Year .........................: " << bdgtRec1.year      << endl;
    cout << "Amount .......................: " << bdgtRec1.amount    << endl;
    cout << "Over-budget Alert ............: " << bdgtRec1.alert     << endl;
    cout << "*****************************************************" << endl; 
    cout.flush();
    cout << "Enter 'X' to exit: "; 
    //
    // read the input
    choice = "";
    getline (cin, choice);


    //----------
    // Exit
    //----------
    if (choice == "X" ||
        choice == "x" )
    {
      return;     // exit
    }
  }
  system("cls");
}

//-------------------------------------------------------------------------------------//
// Get Budget Master Record to Column Values 
//-------------------------------------------------------------------------------------//
bool BudgetMaster::getRec_by_BudgetMasterKey(string acctCode, string year, BudgetMasterRecord& bdgtRec1)
{
  string  dataRow;
  bdgtFldLen1.initialize();     // For Transaction.Alert_Budget
  
  try
  {
    ifstream file1 (filename_BudgetMaster);
    if (file1.is_open())
    {
      //----------
      // Loop to find the record...
      //----------
      while ( getline (file1, dataRow) )
      {
        if (utility1.trim(dataRow)=="")
        {
          continue;            // skip if space line
        }
        //
        // Split data line into column values
        split_DataRow_to_Fields(dataRow, bdgtRec1);
        //
        // is the account code matched?
        if (bdgtRec1.acctCode==acctCode &&
		    bdgtRec1.year==year)
        {
          file1.close();
          return true;
        }
      }
      bdgtRec1.initialize();
      file1.close();
    }    

    //----------
    // initialize with spaces
    //----------
    split_DataRow_to_Fields("     ", bdgtRec1);        // fill-up with spaces  (fixed length)
    return false;
  }
  catch (int e)
  {
      // exception handling at here
  }
}

//-------------------------------------------------------------------------------------//
// List Budget Records  (overload)
//-------------------------------------------------------------------------------------//
void BudgetMaster::List_Records(bool showDetail)
{
    List_Records("*ALL", "", showDetail);
}
void BudgetMaster::List_Records(string filterType, string filterValue, bool showDetail)
{
  string selection_acctcode;
  string selection_year;
  string valueToCheck;
  string dataRow;
  int reccount = 0;
  bdgtRec1.initialize();
  recordList_Budget.clear();


  while(true)
  {
    ifstream file1 (filename_BudgetMaster);
    if (file1.is_open())
    {
      //----------
      // Display column hedders
      //----------
      system("cls");
      cout << "List of Budget records:" << endl;
      cout << "************************************************************************" << endl;
      cout << " AcctCode     Year     Amount      Over-budget Alert  " << endl;
      cout << "-----------  ------  ----------  ---------------------" << endl;

      //----------
      // Loop to extract Account Codeing detail records to array...  (before sorting)
      //----------
      while ( getline (file1, dataRow) )
      {
        if (utility1.trim(dataRow)=="")
        {
          continue;    // skip if space line
        }
        //
        // Split data line into column values
        split_DataRow_to_Fields(dataRow, bdgtRec1);
        valueToCheck = "";
        if      (filterType=="AcctCode")        valueToCheck = bdgtRec1.acctCode;   
        else if (filterType=="Year")        valueToCheck = bdgtRec1.year;   
        else if (filterType=="Amount")        valueToCheck = bdgtRec1.amount;  
        //
        if (filterType!="*ALL" && 
            valueToCheck.find(filterValue) == string::npos)
        {
          continue;        // skip if not matche
        }
        //
        // display matched data...
        reccount++;
        recordList_Budget.push_back(make_tuple(
          bdgtRec1.acctCode, 
          bdgtRec1.year,
          bdgtRec1.amount,
          bdgtRec1.alert
          ));
      }
      file1.close();



      //----------
      // Sort Account Code list by first column (Account Code)
      //----------
      sort(recordList_Budget.begin(), recordList_Budget.end()); 



      //----------
      // Loop to display detail rows...  (sorted by Account Code)
      //----------
      for (int i = 0; i < recordList_Budget.size(); i++) 
      {
        cout << get<0>(recordList_Budget[i]) << "         "         // Account Code
             << get<1>(recordList_Budget[i]) << "    "         // Year
             << get<2>(recordList_Budget[i]) << "   "         // Account Type
             << "          " << get<3>(recordList_Budget[i]) << "          "         // Is Taxable
             << "\n";
      }
      recordList_Budget.clear();
    }    
    else
    {
      cout << "> Error!  Unable to open file";
    }  


    cout << "************************************************************************" << endl;
    if (reccount < 1)
    {
      // no record found, exit.
      cout << "\nNo Budget record is available.\n" << endl;
      system("pause");
      
      cout << "\n";
      system("cls");
      return;
    }
    
    // Exit after listed  
    if (showDetail==false)
    {
      return;
    }
    
    // Select Account Code record detail
    while (true)
    {
      // Futher selection_acctcode
      cout << "Please select the account code and the year of the record to search." << endl;
      cout << "Enter 'X' now to exit." << endl;
      cout << "Please enter Account Code: ";
      // read the input
      getline (cin, selection_acctcode);
      
      // Exit...
      if (selection_acctcode=="X" ||
          selection_acctcode=="x")
      {
        cout << "\n";
        system("cls");
        return;     // exit
      }
      
	  // Futher selection_acctcode
      cout << "Please also enter Year (2019 - 2100): ";
      // read the input
	  getline (cin, selection_year);
	  
      // Display Account Code detail
      if ((selection_acctcode.length()==4) && (selection_year.length()==bdgtFldLen1.year))
      {
        if (isValid_BudgetMasterKey2(selection_acctcode, selection_year))
        {
          Display_BudgetMaster(selection_acctcode, selection_year);
          break;
        }
      }
      
      
      // invalid input, retry
      cout << "\n>> Invalid input.  Please retry." << endl;
      system("pause");
    }
  }
      
  system("pause");
  return;
}

//-------------------------------------------------------------------------------------//
// Check if account code is in use
//-------------------------------------------------------------------------------------//
bool BudgetMaster::IsUsed_AccountCode(string acctCode)
{

  string  dataRow;
  bdgtRec1.initialize();
  bdgtFldLen1.initialize();     // For AccountMaster.Delete_AccountMaster()
  
  try
  {
    ifstream file1 (filename_BudgetMaster);
    if (file1.is_open())
    {
      //----------
      // Loop to find the record...
      //----------
      while ( getline (file1, dataRow) )
      {
        if (utility1.trim(dataRow)=="")
        {
          continue;            // skip if space line
        }
        //
        // Split data line into column values
        split_DataRow_to_Fields(dataRow, bdgtRec1);
        //
        // is the Account Code matched?
        if (bdgtRec1.acctCode==acctCode)
        {
          file1.close();
          return true;
        }
      }
      file1.close();
    }    
    return false;
  }
  catch (int e)
  {
      // exception handling at here
  }  
}



//----------------------------------Private Functions----------------------------------//



//-------------------------------------------------------------------------------------//
// ADD Record
//-------------------------------------------------------------------------------------//
void BudgetMaster::add_Record(BudgetMasterRecord bdgtRec1)
{
  double monthlyAmount;
  
  // Calculate monthly average
  monthlyAmount = stod(bdgtRec1.amount) / 12;
  monthlyAmount = stod( utility1.formatStringToDecimal(to_string(monthlyAmount), 2) );     // Correct monthly average to 2 decimal place
  bdgtRec1.amount_01 = utility1.formatStringToDecimal(to_string(monthlyAmount), 2);
  bdgtRec1.amount_02 = utility1.formatStringToDecimal(to_string(monthlyAmount), 2);
  bdgtRec1.amount_03 = utility1.formatStringToDecimal(to_string(monthlyAmount), 2);
  bdgtRec1.amount_04 = utility1.formatStringToDecimal(to_string(monthlyAmount), 2);
  bdgtRec1.amount_05 = utility1.formatStringToDecimal(to_string(monthlyAmount), 2);
  bdgtRec1.amount_06 = utility1.formatStringToDecimal(to_string(monthlyAmount), 2);
  bdgtRec1.amount_07 = utility1.formatStringToDecimal(to_string(monthlyAmount), 2);
  bdgtRec1.amount_08 = utility1.formatStringToDecimal(to_string(monthlyAmount), 2);
  bdgtRec1.amount_09 = utility1.formatStringToDecimal(to_string(monthlyAmount), 2);
  bdgtRec1.amount_10 = utility1.formatStringToDecimal(to_string(monthlyAmount), 2);
  bdgtRec1.amount_11 = utility1.formatStringToDecimal(to_string(monthlyAmount), 2);
  bdgtRec1.amount_12 = utility1.formatStringToDecimal( to_string(stod(bdgtRec1.amount) - (monthlyAmount * 11)), 2);
  
  ofstream outfile;
  outfile.open(filename_BudgetMaster, std::ios_base::app);
  
  //----------
  // Pad all fields with space to get maxi. length before writting to file
  //----------
  bdgtRec1.acctCode  = utility1.padRight(bdgtRec1.acctCode,   ' ', bdgtFldLen1.acctCode);
  bdgtRec1.year      = utility1.padRight(bdgtRec1.year,       ' ', bdgtFldLen1.year);
  bdgtRec1.amount    = utility1.padLeft( bdgtRec1.amount,     ' ', bdgtFldLen1.amount);
  bdgtRec1.amount_01 = utility1.padLeft( bdgtRec1.amount_01,  ' ', bdgtFldLen1.amount_01);
  bdgtRec1.amount_02 = utility1.padLeft( bdgtRec1.amount_02,  ' ', bdgtFldLen1.amount_02);
  bdgtRec1.amount_03 = utility1.padLeft( bdgtRec1.amount_03,  ' ', bdgtFldLen1.amount_03);
  bdgtRec1.amount_04 = utility1.padLeft( bdgtRec1.amount_04,  ' ', bdgtFldLen1.amount_04);
  bdgtRec1.amount_05 = utility1.padLeft( bdgtRec1.amount_05,  ' ', bdgtFldLen1.amount_05);
  bdgtRec1.amount_06 = utility1.padLeft( bdgtRec1.amount_06,  ' ', bdgtFldLen1.amount_06);
  bdgtRec1.amount_07 = utility1.padLeft( bdgtRec1.amount_07,  ' ', bdgtFldLen1.amount_07);
  bdgtRec1.amount_08 = utility1.padLeft( bdgtRec1.amount_08,  ' ', bdgtFldLen1.amount_08);
  bdgtRec1.amount_09 = utility1.padLeft( bdgtRec1.amount_09,  ' ', bdgtFldLen1.amount_09);
  bdgtRec1.amount_10 = utility1.padLeft( bdgtRec1.amount_10,  ' ', bdgtFldLen1.amount_10);
  bdgtRec1.amount_11 = utility1.padLeft( bdgtRec1.amount_11,  ' ', bdgtFldLen1.amount_11);
  bdgtRec1.amount_12 = utility1.padLeft( bdgtRec1.amount_12,  ' ', bdgtFldLen1.amount_12);  
  bdgtRec1.alert     = utility1.padRight(bdgtRec1.alert,      ' ', bdgtFldLen1.alert);
  //
  bdgtRec1._endSpace  = utility1.padRight(bdgtRec1._endSpace,  ' ', bdgtFldLen1._endSpace); 
  //
  outfile << bdgtRec1.acctCode
          << bdgtRec1.year
		      << bdgtRec1.amount
		      << bdgtRec1.amount_01
		      << bdgtRec1.amount_02
		      << bdgtRec1.amount_03
		      << bdgtRec1.amount_04
		      << bdgtRec1.amount_05
		      << bdgtRec1.amount_06
		      << bdgtRec1.amount_07
		      << bdgtRec1.amount_08
		      << bdgtRec1.amount_09
		      << bdgtRec1.amount_10
		      << bdgtRec1.amount_11
		      << bdgtRec1.amount_12
          << bdgtRec1.alert
          << bdgtRec1._endSpace
          << "\n";
  //
  outfile.close();
}

//-------------------------------------------------------------------------------------//
// UPDATE Record
//-------------------------------------------------------------------------------------//
void BudgetMaster::change_Record(BudgetMasterRecord bdgtRec1)
{
  string  dataRow;
  streampos lastPos;
  BudgetMasterRecord bdgtRec2;
  double monthlyAmount;
  
  // Calculate monthly average
  monthlyAmount = stod(bdgtRec1.amount) / 12;
  monthlyAmount = stod( utility1.formatStringToDecimal(to_string(monthlyAmount), 2) );     // Correct monthly average to 2 decimal place
  bdgtRec1.amount_01 = utility1.formatStringToDecimal(to_string(monthlyAmount), 2);
  bdgtRec1.amount_02 = utility1.formatStringToDecimal(to_string(monthlyAmount), 2);
  bdgtRec1.amount_03 = utility1.formatStringToDecimal(to_string(monthlyAmount), 2);
  bdgtRec1.amount_04 = utility1.formatStringToDecimal(to_string(monthlyAmount), 2);
  bdgtRec1.amount_05 = utility1.formatStringToDecimal(to_string(monthlyAmount), 2);
  bdgtRec1.amount_06 = utility1.formatStringToDecimal(to_string(monthlyAmount), 2);
  bdgtRec1.amount_07 = utility1.formatStringToDecimal(to_string(monthlyAmount), 2);
  bdgtRec1.amount_08 = utility1.formatStringToDecimal(to_string(monthlyAmount), 2);
  bdgtRec1.amount_09 = utility1.formatStringToDecimal(to_string(monthlyAmount), 2);
  bdgtRec1.amount_10 = utility1.formatStringToDecimal(to_string(monthlyAmount), 2);
  bdgtRec1.amount_11 = utility1.formatStringToDecimal(to_string(monthlyAmount), 2);
  bdgtRec1.amount_12 = utility1.formatStringToDecimal( to_string(stod(bdgtRec1.amount) - (monthlyAmount * 11)), 2);
  
  try
  {
    ifstream fileOld(filename_BudgetMaster);
    ofstream fileNew(filename_TempOutput);

    if (fileOld.is_open())
    {
      //----------
      // Loop to find the record...
      //----------
      while ( getline (fileOld, dataRow))
      {
        if (utility1.trim(dataRow)=="")
        {
          continue;            // skip if space line
        }
        //
        // Split data line into column values
        split_DataRow_to_Fields(dataRow, bdgtRec2);
        //
        // is the Budget Master key  matched?
        if (bdgtRec1.acctCode!=bdgtRec2.acctCode &&
		        bdgtRec1.year==bdgtRec2.year)
        {
          // copy line to new file if not matched
          fileNew << dataRow << "\n";
        }
        else
        {
          //----------
          // Budget Master record found, write new changed record
          //----------
          // Pad all fields with space to get maxi. length before writting to file
          bdgtRec1.acctCode  = utility1.padRight(bdgtRec1.acctCode,   ' ', bdgtFldLen1.acctCode);
          bdgtRec1.year      = utility1.padRight(bdgtRec1.year,       ' ', bdgtFldLen1.year);
          bdgtRec1.amount    = utility1.padLeft( bdgtRec1.amount,     ' ', bdgtFldLen1.amount);
          bdgtRec1.amount_01 = utility1.padLeft( bdgtRec1.amount_01,  ' ', bdgtFldLen1.amount_01);
          bdgtRec1.amount_02 = utility1.padLeft( bdgtRec1.amount_02,  ' ', bdgtFldLen1.amount_02);
          bdgtRec1.amount_03 = utility1.padLeft( bdgtRec1.amount_03,  ' ', bdgtFldLen1.amount_03);
          bdgtRec1.amount_04 = utility1.padLeft( bdgtRec1.amount_04,  ' ', bdgtFldLen1.amount_04);
          bdgtRec1.amount_05 = utility1.padLeft( bdgtRec1.amount_05,  ' ', bdgtFldLen1.amount_05);
          bdgtRec1.amount_06 = utility1.padLeft( bdgtRec1.amount_06,  ' ', bdgtFldLen1.amount_06);
          bdgtRec1.amount_07 = utility1.padLeft( bdgtRec1.amount_07,  ' ', bdgtFldLen1.amount_07);
          bdgtRec1.amount_08 = utility1.padLeft( bdgtRec1.amount_08,  ' ', bdgtFldLen1.amount_08);
          bdgtRec1.amount_09 = utility1.padLeft( bdgtRec1.amount_09,  ' ', bdgtFldLen1.amount_09);
          bdgtRec1.amount_10 = utility1.padLeft( bdgtRec1.amount_10,  ' ', bdgtFldLen1.amount_10);
          bdgtRec1.amount_11 = utility1.padLeft( bdgtRec1.amount_11,  ' ', bdgtFldLen1.amount_11);
          bdgtRec1.amount_12 = utility1.padLeft( bdgtRec1.amount_12,  ' ', bdgtFldLen1.amount_12);  
          bdgtRec1.alert     = utility1.padRight(bdgtRec1.alert,      ' ', bdgtFldLen1.alert);
          //
          bdgtRec1._endSpace  = utility1.padRight(bdgtRec1._endSpace,  ' ', bdgtFldLen1._endSpace); 
          //
          fileNew << bdgtRec1.acctCode
                  << bdgtRec1.year
        		      << bdgtRec1.amount
        		      << bdgtRec1.amount_01
        		      << bdgtRec1.amount_02
        		      << bdgtRec1.amount_03
        		      << bdgtRec1.amount_04
        		      << bdgtRec1.amount_05
        		      << bdgtRec1.amount_06
        		      << bdgtRec1.amount_07
        		      << bdgtRec1.amount_08
        		      << bdgtRec1.amount_09
        		      << bdgtRec1.amount_10
        		      << bdgtRec1.amount_11
        		      << bdgtRec1.amount_12
                  << bdgtRec1.alert
                  << bdgtRec1._endSpace
                  << "\n";
        }
      }
      fileNew.close();
      fileOld.close();
    }    

    //----------
    // rename file
    //----------
    // delete the original file
    remove(filename_BudgetMaster.c_str());
    // rename old to new
    rename(filename_TempOutput.c_str(), filename_BudgetMaster.c_str());

  }
  catch (int e)
  {
    // exception handling at here
  }
}

//-------------------------------------------------------------------------------------//
// DELETE Record
//-------------------------------------------------------------------------------------//
void BudgetMaster::delete_Record(std::string acctCode, string year)
{
  string  dataRow;
  BudgetMasterRecord bdgtRec2;

  try
  {
    ifstream fileOld(filename_BudgetMaster);
    ofstream fileNew(filename_TempOutput);

    if (fileOld.is_open())
    {
      //----------
      // Loop to copy record to new file, except the record to be deleted
      //----------
      while ( getline (fileOld, dataRow))
      {
        if (utility1.trim(dataRow)=="")
        {
          continue;            // skip if space line
        }
        //
        // Split data line into column values
        split_DataRow_to_Fields(dataRow, bdgtRec2);
        //
        // skip if the Budget Master Key matched (delete)?
        if (bdgtRec2.acctCode==acctCode &&
		        bdgtRec2.year==year)
        {
          continue;
        }
        // copy line to new file
        fileNew << dataRow << "\n";                
      }
      fileNew.close();
      fileOld.close();
    }    

    //----------
    // rename file
    //----------
    // delete the original file
    remove(filename_BudgetMaster.c_str());
    // rename old to new
    rename(filename_TempOutput.c_str(), filename_BudgetMaster.c_str());

  }
  catch (int e)
  {
      // exception handling at here
  }
}

//-------------------------------------------------------------------------------------//
// Split Budget Master Record to Column Values 
//-------------------------------------------------------------------------------------//
bool BudgetMaster::split_DataRow_to_Fields(string DataRow, BudgetMasterRecord& bdgtRec1)
{
  string* values = new string[bdgtFldLen1._numOfFields];
  int    strPos = 0;
  int    endPos = -1;
  //BudgetMasterFldLen bdgtFldLen1;

  // load field length values into array for extraing field values
  // (check header file for correct field length values)
  //bdgtFldLen1.initialize();
  for (int i=0; i<bdgtFldLen1._numOfFields; i++)
  {
    values[i] = "";
    strPos = endPos+1;
    endPos = strPos + bdgtFldLen1._val[i] - 1;
    //
    if (DataRow.length() >= endPos)       values[i] = DataRow.substr(strPos,    bdgtFldLen1._val[i]);
    else                                  values[i] = utility1.padLeft("", ' ', bdgtFldLen1._val[i]);
  }
 
  //----------
  // Loading data into struct
  //----------
  bdgtRec1.acctCode  = values[0];
  bdgtRec1.year      = values[1];
  bdgtRec1.amount    = values[2];
  bdgtRec1.amount_01 = values[3];
  bdgtRec1.amount_02 = values[4];
  bdgtRec1.amount_03 = values[5];
  bdgtRec1.amount_04 = values[6];
  bdgtRec1.amount_05 = values[7];
  bdgtRec1.amount_06 = values[8];
  bdgtRec1.amount_07 = values[9];
  bdgtRec1.amount_08 = values[10];
  bdgtRec1.amount_09 = values[11];
  bdgtRec1.amount_10 = values[12];
  bdgtRec1.amount_11 = values[13];
  bdgtRec1.amount_12 = values[14];
  bdgtRec1.alert     = values[15];
  
  return true;
}

//-------------------------------------------------------------------------------------//
// Is valid Budget Master Key  (with struct initialization)
//-------------------------------------------------------------------------------------//
bool BudgetMaster::isValid_BudgetMasterKey2(string acctCode, string year)
{
    bdgtRec1.initialize();
    bdgtFldLen1.initialize();
    bdgtFldChg1.initialize();

	return isValid_BudgetMasterKey(acctCode, year);
}

//-------------------------------------------------------------------------------------//
// Is valid Budget Master Key  
//-------------------------------------------------------------------------------------//
bool BudgetMaster::isValid_BudgetMasterKey(string acctCode, string year)
{
  string  dataRow;
  BudgetMasterRecord bdgtRec2;
  bdgtRec2.initialize();


  try
  {
    ifstream file1 (filename_BudgetMaster);
    if (file1.is_open())
    {
      //----------
      // Loop to find the record...
      //----------
      while ( getline (file1, dataRow) )
      {
        if (utility1.trim(dataRow)=="")
        {
          continue;            // skip if space line
        }
        //
        // Split data line into column values
        split_DataRow_to_Fields(dataRow, bdgtRec2);
        //
        // Budget Master record found
        if (bdgtRec2.acctCode==acctCode &&
		        bdgtRec2.year==year)
        {
          file1.close();
          return true;
        }
      }
      file1.close();
    }    
    // Budget Master record not found
    return false;
  }
  catch (int e)
  {
    // exception handling at here
  }  
}

