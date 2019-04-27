//-----------------------------------------------------------------------
// Description : Accounting System - Account Code - Class
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
#include "AccountMaster.h"
#include "BudgetMaster.h"
#include "Transaction.h"
#include "Utility.h"
#include <bits/stdc++.h> 

using namespace std;

extern Utility utility1;
extern BudgetMaster budgetMaster1;
extern Transaction transaction1;

// Account code record structure   (details definition: pls check header file)
struct AccountMaster::AccountMasterRecord acctRec1;
struct AccountMaster::AccountMasterFldLen acctFldLen1;
struct AccountMaster::AccountMasterFldChg acctFldChg1;

vector<tuple<string, string, string, string> > recordList_Account; 


//-------------------------------------------------------------------------------------//
// Sub-menu:  ACCOUNT CODE
//-------------------------------------------------------------------------------------//
void AccountMaster::Menu()
{
    char selection;
    //AccountMaster accountCode1;
    Utility utility1;
    
    acctRec1.initialize();
    acctFldLen1.initialize();
    acctFldChg1.initialize();
    
    //-------------------
    // Loop: Display menu and selection option 
    //-------------------
    while (true)
    {
        // Display menu
        system("cls");
        cout << "|-------------------------------------------------------------------------|" << endl;
        cout << "|            ACCOUNTING SYSTEM - MAINTAIN ACCOUNT CODE RECORDS            |" << endl;
        cout << "|-------------------------------------------------------------------------|" << endl;
        cout << "|***           Welcome to HKU Simple Accounting System (2019)          ***|" << endl;
        cout << "|***  This system is developed by ENGG1340 Class No.XXXXX Group No.XX  ***|" << endl;
        cout << "|-------------------------------------------------------------------------|" << endl;
        cout << "|                                                                         |" << endl;
        cout << "|  Options:                                                               |" << endl;
        cout << "|           1. Add New Account Code                                       |" << endl;
        cout << "|           2. Change Account Code                                        |" << endl;
        cout << "|           3. Delete Account Code                                        |" << endl;
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
                Add_AccountMaster();
                continue;
            case '2' :
                cout.flush();
                cin.ignore();
                Change_AccountMaster();
                continue;
            case '3' :
                cout.flush();
                cin.ignore();
                Delete_AccountMaster();
                continue;
            case '4' :
                cout.flush();
                cin.ignore();
                Search_AccountMaster();
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
// Add Account Code Record
//-------------------------------------------------------------------------------------//
void AccountMaster::Add_AccountMaster()
{
  int counter1 = 0;
  string choice1 = "";
  string choice2 = "";
  string input1 = "";
  string accountCode = "";
  string newValueA = "";
  int    numValue1 = 0;
  int    numValue2 = 0;
  int    numValue3 = 0;
  acctFldLen1.initialize();



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
    acctRec1.initialize();   //clear all field values
    while (true)
    {
      // input account code  (Primary Key)
      cout << "\n";
      cout << "Please enter below to create a account code record." << endl;
      cout << counter1 << ") Account Code: ";
      getline (cin, accountCode);
  
      if (accountCode.length()<1)
      {
        cout << "> Invalid account code.  Cannot be empty." << endl;
        cout << "Retry? (Y/N): ";
        getline (cin, choice1);
        if (choice1 == "N" || choice1 == "n")      return;                // exit
        else                                       continue;



        cout.flush();
        continue;
      }        
      if (accountCode.length()!=acctFldLen1.acctCode)
      {
        cout << "> Invalid account code. Input must be exactly " << acctFldLen1.acctCode << " characters. Please retry." << endl;
        cout.flush();
        continue;
      }        
      if (isValid_AccountMasterKey(accountCode))
      {
        cout << "> Error - Account code is already existed. Please use another number." << endl;
        cout.flush();
        continue;
      }

      acctRec1.acctCode = accountCode;
      break;
    }
    
    //----------
    // Input - Account Description
    //----------
    counter1++;
    while (true)
    {
      // input 
      cout << "\n";
      cout << counter1 << ") Account Description.: ";
      getline (cin, input1);
      
      input1 = utility1.trim(input1);
      if (input1 == "")
      {
        cout << "> Invalid Account Description. Cannot be empty. Please retry." << endl;
        cout.flush();
        continue;
      }        
      if (input1.length()>acctFldLen1.acctDesc)
      {
        cout << "> Invalid Account Description. Maxi. " << acctFldLen1.acctDesc << " characters. Please retry." << endl;
        cout.flush();
        continue;
      }        

      acctRec1.acctDesc = input1;
      break;
    }
    
    //----------
    // Input - Account type
    //----------
    counter1++;
    while (true)
    {
      // input 
      cout << "\n";
      cout << counter1 << ") Account Type (I/E): ";
      getline (cin, input1);
      
      input1 = utility1.trim(input1);
      if (input1 == "")
      {
        cout << "> Invalid Account Type. Cannot be empty. Please retry." << endl;
        cout.flush();
        continue;
      }        
      if (input1.length()>acctFldLen1.acctType)
      {
        cout << "> Invalid Account Type. Maxi. " << acctFldLen1.acctType << " characters. Please retry." << endl;
        cout.flush();
        continue;
      }
      if (input1 != "I" && input1 != "E" && input1 != "i" && input1 != "e")
      {
        cout << "> Invalid Account Type. Must type 'I' or 'E'. Please retry." << endl;
        cout.flush();
        continue;
      }
      if (input1 == "i")
      {
        input1 = "I";
      }
      if (input1 == "e")
      {
        input1 = "E";
      }
      
      acctRec1.acctType = input1;
      break;
    }
    
    //----------
    // Input - Taxable
    //----------
    counter1++;
    while (true)
    {
      // input 
      cout << "\n";
      cout << counter1 << ") Taxable (Y/N): ";
      getline (cin, input1);
      
      input1 = utility1.trim(input1);
      if (input1 == "")
      {
        cout << "> Invalid Taxable Value. Cannot be empty. Please retry." << endl;
        cout.flush();
        continue;
      }        
      if (input1.length()>acctFldLen1.Taxable)
      {
        cout << "> Invalid Taxable Value. Maxi. " << acctFldLen1.Taxable << " characters. Please retry." << endl;
        cout.flush();
        continue;
      }
      if (input1 != "Y" && input1 != "N" && input1 != "y" && input1 != "n")
      {
        cout << "> Invalid Taxable Value. Must type 'Y' or 'N'. Please retry." << endl;
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
      
      acctRec1.Taxable = input1;
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
        add_Record(acctRec1);
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
// Modify Account Code Record
//-------------------------------------------------------------------------------------//
void AccountMaster::Change_AccountMaster()
{
  string choice1 = "";
  string choice2 = "";
  string input  = "";
  string accountCode = "";
  string newValueA = "";
  int    numValue1 = 0;
  int    numValue2 = 0;
  int    numValue3 = 0;
  bool   isDone;
  acctFldLen1.initialize();

  //----------
  // User selection
  //----------
  system("cls");
  while (true)
  {
    // clear all field values
    acctRec1.initialize();
            
    // How to search
    cout << "\n";
    cout << "Edit by:  1) Account Code,          L) List all records," << endl;
    cout << "          2) Account Description,   X) Exit" << endl;
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
    // List by Account Description  (Filter / Search)
    //----------
    else if (choice1=="2")
    {
      while (true)
      {
        cout << "Please enter Account Description to list: ";
        // read the input
        getline (cin, input);
    
        // is input valid?
        if (utility1.trim(input)=="")
        {
          cout << "> Invalid Account Description.  Cannot be empty." << endl;
          cout << "Retry? (Y/N): ";
          cin.ignore();
          getline (cin, choice1);
          if (choice1 == "N" || choice1 == "n")      break;                // exit
          else                                       continue;
        }
        
        List_Records("AcctDesc", input, false);        // list filter by Account Description, do not show detail
        break;
      }
    }
    
    //----------
    // Lookup Account Code to Edit
    //----------
    acctRec1.initialize();
    acctFldChg1.initialize();
    while (true)
    {
      cout << "Please enter Account Code to EDIT. Enter 'X' to exit.: ";
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
      if (isValid_AccountMasterKey(input)==false)
      {
        cout << "> Account Code not found." << endl;
        cout << "Retry? (Y/N): ";
        getline (cin, choice2);
        if (choice2 == "N" || choice2 == "n")      return;                // exit
        else                                       continue;
      }
      
      break;    
    }
    
    // Get the Account Code details
    accountCode = input;
    getRec_by_AccountMasterKey(accountCode, acctRec1);
    
    //-----------
    // Start to EDIT...
    //-----------
    while (true)
    {
      system("cls");
      cout << "EDIT Account Code record:" << endl;
      cout << "*****************************************************" << endl;
      cout <<                           "Account Code .................: " << acctRec1.acctCode    << endl;
      cout << "" << endl;
      cout << acctFldChg1.acctDesc   << "1) Account Description .......: " << acctRec1.acctDesc    << endl;
      cout << acctFldChg1.acctType   << "2) Account Type ..............: " << acctRec1.acctType    << endl;
      cout << acctFldChg1.Taxable    << "3) Is Taxable ................: " << acctRec1.Taxable     << endl;
      cout << "*****************************************************" << endl; 
      cout << "Select which field (1-3) to change and press <Enter>." << endl;
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
        change_Record(acctRec1);


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
          stoi(choice2) <= 0 || stoi(choice2) > 3)
      {
        cout << "> Invalid selection. Valid field number is (1-3).  Please <Enter> to retry." << endl;
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
            cout << "Account Description .......: " + acctRec1.acctDesc << endl;
            cout << "Enter new value: ";
            getline (cin, newValueA);
            newValueA = utility1.trim(newValueA);
            if (newValueA == "")
            {
              cout << "> Invalid Account Description. Cannot be empty. Please retry." << endl;
              cout.flush();
              continue;
            }        
            if (newValueA.length()>acctFldLen1.acctDesc)
            {
              cout << "> Invalid Account Description. Maxi. " << acctFldLen1.acctDesc << " characters. Please retry." << endl;
              cout.flush();
              continue;
            }        
            acctRec1.acctDesc = newValueA;
            acctFldChg1.acctDesc = '*';
            isDone = true;
            break;

          case 2:
            cout << "Account Type ..............: " + acctRec1.acctType << endl;
            cout << "Enter new value (I/E): ";
            getline (cin, newValueA);
            newValueA = utility1.trim(newValueA);
            if (newValueA == "")
            {
              cout << "> Invalid Account Type. Cannot be empty. Please retry." << endl;
              cout.flush();
              continue;
            }        
            if (newValueA.length()>acctFldLen1.acctType)
            {
              cout << "> Invalid Account Type. Maxi. " << acctFldLen1.acctType << " characters. Please retry." << endl;
              cout.flush();
              continue;
            }        
      			if (newValueA != "I" && newValueA != "E" && newValueA != "i" && newValueA != "e")
      			{
      				cout << "> Invalid Account Type. Must type 'I' or 'E'. Please retry." << endl;
      				cout.flush();
      				continue;
      			}
      			if (newValueA == "i")
      			{
      				newValueA = "I";
      			}
      			if (newValueA == "e")
      			{
      				newValueA = "E";
      			}
      			
            acctRec1.acctType = newValueA;
            acctFldChg1.acctType = '*';
            isDone = true;
            break;

          case 3:
            cout << "Is Taxable ................: " + acctRec1.Taxable << endl;
            cout << "Enter new value (Y/N): ";
            getline (cin, newValueA);
            newValueA = utility1.trim(newValueA);
            if (newValueA.length()!=acctFldLen1.Taxable)
            {
              cout << "> Invalid Is Taxable Value. Input must be 'Y' or 'N'. Please retry." << endl;
              cout.flush();
              continue;
            }
      			if (newValueA != "Y" && newValueA != "N" && newValueA != "y" && newValueA != "n")
      			{
      				cout << "> Invalid Is Taxable Value. Must type 'Y' or 'N'. Please retry." << endl;
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
            
            acctRec1.Taxable = newValueA;
            acctFldChg1.Taxable = '*';
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
// Delete Account Code Record
//-------------------------------------------------------------------------------------//
void AccountMaster::Delete_AccountMaster()
{
  string choice1 = "";
  string choice2 = "";
  string input  = "";
  string accountCode = "";
  bool   isDone;
  acctFldLen1.initialize();

  //----------
  // User selection
  //----------
  system("cls");
  while (true)
  {
    // clear all field values
    acctRec1.initialize();
            
    // How to search
    cout << "\n";
    cout << "DELETE by:  1) Account Code,          L) List all records," << endl;
    cout << "            2) Account Description,   X) Exit" << endl;
    cout << "Selection: ";
    
    getline (cin, choice1);

    //
    if (choice1 != "1" &&
        choice1 != "2" &&
        choice1 != "L" && choice1 != "l" &&
        choice1 != "X" && choice1 != "x")
    {
      cout << "> Invalid choice1. Please try again." << endl;
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
    // List by Account Description  (Filter / Search)
    //----------
    else if (choice1=="2")
    {
      while (true)
      {
        cout << "Please enter Account Description to list: ";
        // read the input
        getline (cin, input);
    
        // is input valid?
        if (utility1.trim(input)=="")
        {
          cout << "> Invalid Account Description.  Cannot be empty." << endl;
          cout << "Retry? (Y/N): ";
          cin.ignore();
          getline (cin, choice1);
          if (choice1 == "N" || choice1 == "n")      break;                // exit
          else                                       continue;
        }
        
        List_Records("AcctDesc", input, false);        // list filter by Account Description, do not show detail
        break;
      }
    }
    
    //----------
    // Lookup Account Code to DELETE
    //----------
    acctRec1.initialize();
    while (true)
    {
      cout << "Please enter Account Code to DELETE. Enter 'X' to exit.: ";
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
      if (isValid_AccountMasterKey(input)==false)
      {
        cout << "> Account Code not found." << endl;
        cout << "Retry? (Y/N): ";
        getline (cin, choice2);
        if (choice2 == "N" || choice2 == "n")      return;                // exit
        else                                       continue;
      }
      
      // If account code used by 1 or more transaction records, stop
      if (transaction1.IsUsed_AccountCode(input) == true)
      {
        cout << "> Account Code currently used in transaction. Cannot delete." << endl;
        system("PAUSE");
        return;
      }
      
      // If account code used by 1 or more budget records, stop
      if (budgetMaster1.IsUsed_AccountCode(input) == true)
      {
        cout << "> Account Code currently used in budget master. Cannot delete." << endl;
        system("PAUSE");
        return;
      }
      
      break;    
    }
    
    // Get the Account Code details
    accountCode = input;
    getRec_by_AccountMasterKey(accountCode, acctRec1);
    
    //-----------
    // Display
    //-----------
    while (true)
    {
      system("cls");
      cout << "DELETE Account Code record:" << endl;
      cout << "*****************************************************" << endl;
      cout <<                           "Account Code .................: " << acctRec1.acctCode    << endl;
      cout << "" << endl;
      cout << " 1) Account Description .......: " << acctRec1.acctDesc    << endl;
      cout << " 2) Account Type ..............: " << acctRec1.acctType    << endl;
      cout << " 3) Is Taxable ................: " << acctRec1.Taxable     << endl;
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
      delete_Record(acctRec1.acctCode);


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
// Display Record in Detail
//-------------------------------------------------------------------------------------//
void AccountMaster::Display_AccountMaster(string accountCode)
{
  string  choice;
  acctRec1.initialize();

  getRec_by_AccountMasterKey(accountCode, acctRec1);
  if (utility1.trim(acctRec1.acctCode)=="")
  {
    cout << "> Invalid Account Code." << endl;
    system("pause");
    return;
  }
  
  //----------
  // Display Account Code detail
  //----------
  while (true) 
  {
    system("cls");
    cout << "Account Code record details:" << endl;
    cout << "*****************************************************" << endl;
    cout << "Account Code .................: " << acctRec1.acctCode  << endl;
    cout << "Account Description ..........: " << acctRec1.acctDesc  << endl;
    cout << "Account Type .................: " << acctRec1.acctType  << endl;
    cout << "Is Taxable ...................: " << acctRec1.Taxable   << endl;
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
// List Account Code Records  (overload)
//-------------------------------------------------------------------------------------//
void AccountMaster::List_Records(bool showDetail)
{
    List_Records("*ALL", "", showDetail);
}
void AccountMaster::List_Records(string filterType, string filterValue, bool showDetail)
{
  string selection;
  string valueToCheck;
  string dataRow;
  int reccount = 0;
  acctRec1.initialize();
  recordList_Account.clear();


  while(true)
  {
    ifstream file1 (filename_AccountMaster);
    if (file1.is_open())
    {
      //----------
      // Display column hedders
      //----------
      system("cls");
      cout << "List of Account Code records:" << endl;
      cout << "************************************************************************" << endl;
      cout << " AcctCode              Description           Type  Taxable" << endl;
      cout << "-----------  ------------------------------  ----  -------" << endl;

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
        split_DataRow_to_Fields(dataRow, acctRec1);
        valueToCheck = "";
        if      (filterType=="AcctCode")        valueToCheck = acctRec1.acctCode;   
        else if (filterType=="AcctDesc")        valueToCheck = acctRec1.acctDesc;   
        else if (filterType=="AcctType")        valueToCheck = acctRec1.acctType;  
        //
        if (filterType!="*ALL" && 
            valueToCheck.find(filterValue) == string::npos)
        {
          continue;        // skip if not matche
        }
        //
        // display matched data...
        reccount++;
        recordList_Account.push_back(make_tuple(
          acctRec1.acctCode, 
          acctRec1.acctDesc,
          acctRec1.acctType,
          acctRec1.Taxable
          ));
      }
      file1.close();



      //----------
      // Sort Account Code list by first column (Account Code)
      //----------
      sort(recordList_Account.begin(), recordList_Account.end()); 



      //----------
      // Loop to display detail rows...  (sorted by Account Code)
      //----------
      for (int i = 0; i < recordList_Account.size(); i++) 
      {
        cout << get<0>(recordList_Account[i]) << "         "         // Account Code
             << get<1>(recordList_Account[i]) << "    "         // Account Description
             << get<2>(recordList_Account[i]) << "      "         // Account Type
             << get<3>(recordList_Account[i]) << ""         // Is Taxable
             << "\n";
      }
      recordList_Account.clear();
    }    
    else
    {
      cout << "> Error!  Unable to open file";
    }  


    cout << "************************************************************************" << endl;
    if (reccount < 1)
    {
      // no record found, exit.
      cout << "\nNo Account Code record is available.\n" << endl;
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
      // Futher selection
      cout << "Enter 'Account Code' for detail, or 'X' to exit." << endl;
      cout << "Selection: ";
      // read the input
      getline (cin, selection);
      
      // Exit...
      if (selection=="X" ||
          selection=="x")
      {
        cout << "\n";
        system("cls");
        return;     // exit
      }
      
      // Display Account Code detail
      if (selection.length()>0)
      {
        if (isValid_AccountMasterKey(selection))
        {
          Display_AccountMaster(selection);
          break;
        }
      }
      
      
      // invalid input, retry
      cout << "\n>> Invalid input.  Please retry.";
      system("pause");
    }
  }
      
  system("pause");
  return;
}

//-------------------------------------------------------------------------------------//
// Search Account Code Record
//-------------------------------------------------------------------------------------//
void AccountMaster::Search_AccountMaster()
{
  string choice1 = "";
  string choice2 = "";
  string input  = "";
  string accountCode = "";
  acctRec1.initialize();


  //----------
  // User selection
  //----------
  system("cls");
  while (true)
  {
    // How to search
    cout << "\n";
    cout << "Search by:  1) Account Code,          L) List all records," << endl;
    cout << "            2) Account Description,   X) Exit" << endl;
    cout << "Selection: ";
    // read the input
    getline (cin, choice1);

    //
    if (choice1 != "1" &&
        choice1 != "2" &&
        choice1 != "L" && choice1 != "l" &&
        choice1 != "X" && choice1 != "x")
    {
      cout << "> Invalid choice1. Please try again." << endl;
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
      List_Records(true);         // list all records, with details
      continue;
    }


    //----------
    // List by Account Description  (Filter / Search)
    //----------
    if (choice1=="2")
    {
      cout << "Please enter Account Description to search: ";
      // read the input
      getline (cin, input);

      // is input valid?
      if (utility1.trim(input)=="")
      {
        cout << "> Invalid Account Description.  Cannot be empty." << endl;
        cout << "Search again? (Y/N): ";
        getline (cin, choice1);
        if (choice1 == "N" || choice1 == "n")      return;                // exit
        else                                     continue;
      }


      List_Records("AcctDesc", input, true);        // list filter by Account Description, with details
      continue;
    }


    //----------
    // Search by Account Code
    //----------
    if (choice1=="1")
    {
      acctRec1.initialize();
      
      // Inpiut Account Code to search
      while (true)
      {
        cout << "Please enter Account Code to search. Enter 'X' to exit: ";
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
          cout << "> Invalid Account Code.  Cannot be empty." << endl;
          cout << "Search again? (Y/N): ";
          getline (cin, choice2);
          if (choice2 == "N" || choice2 == "n" )      return;                // exit
          else                                      continue;
        }
            
        // Search the Account Codeing no.
        if (isValid_AccountMasterKey(input)==false)
        {
          cout << "> Account Code not found." << endl;
          cout << "Search again? (Y/N): ";
          getline (cin, choice2);
          if (choice2 == "N" || choice2 == "n" )      return;                // exit
          else                                      continue;
        }
        
        // Get the Account Code details
        accountCode = input;
        getRec_by_AccountMasterKey(accountCode, acctRec1);

        //----------
        // Display  (Found)
        //----------
        system("cls");
        cout << "Account Code record details:" << endl;
        cout << "*****************************************************" << endl;
        cout << "Account Code .................: " << acctRec1.acctCode  << endl;
        cout << "Account Description ..........: " << acctRec1.acctDesc  << endl;
        cout << "Account Type .................: " << acctRec1.acctType  << endl;
        cout << "Is Taxable ...................: " << acctRec1.Taxable   << endl;
        cout << "*****************************************************" << endl; 
        cout << "Press <Enter> to continue." << endl;
        
        getline (cin, choice1);
        system("cls");
        break;
      }
    }

  }   // loop to search next record
}

//-------------------------------------------------------------------------------------//
// Get Account Code Record to Column Values 
//-------------------------------------------------------------------------------------//
bool AccountMaster::getRec_by_AccountMasterKey(string accountCode, AccountMasterRecord& acctRec1)
{
  string  dataRow;
  
  try
  {
    ifstream file1 (filename_AccountMaster);
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
        split_DataRow_to_Fields(dataRow, acctRec1);
        //
        // is the account code matched?
        if (acctRec1.acctCode==accountCode)
        {
          file1.close();
          return true;
        }
      }
      acctRec1.initialize();
      file1.close();
    }    

    //----------
    // initialize with spaces
    //----------
    split_DataRow_to_Fields("     ", acctRec1);        // fill-up with spaces  (fixed length)
    return false;
  }
  catch (int e)
  {
      // exception handling at here
  }
}

//-------------------------------------------------------------------------------------//
// Split Account Code Record to Column Values 
//-------------------------------------------------------------------------------------//
bool AccountMaster::split_DataRow_to_Fields(string dataRow, AccountMasterRecord& acctRec1)
{
  acctFldLen1.initialize();
  
  string* values = new string[acctFldLen1._numOfFields];
  int    strPos = 0;
  int    endPos = -1;
  //AccountMasterFldLen acctFldLen1;

  // load field length values into array for extraing field values
  // (check header file for correct field length values)
  //acctFldLen1.initialize();
  for (int i=0; i<acctFldLen1._numOfFields; i++)
  {
    values[i] = "";
    strPos = endPos+1;
    endPos = strPos + acctFldLen1._val[i] - 1;
    //
    if (dataRow.length() >= endPos)       values[i] = dataRow.substr(strPos,    acctFldLen1._val[i]);
    else                                  values[i] = utility1.padLeft("", ' ', acctFldLen1._val[i]);
  }
 
  //----------
  // Loading data into struct
  //----------
  acctRec1.acctCode     = values[0];
  acctRec1.acctDesc     = values[1];
  acctRec1.acctType     = values[2];
  acctRec1.Taxable      = values[3];
  
  return true;
}



//----------------------------------Private Functions----------------------------------//



//-------------------------------------------------------------------------------------//
// ADD Record
//-------------------------------------------------------------------------------------//
void AccountMaster::add_Record(AccountMasterRecord acctRec1)
{
  ofstream outfile;
  outfile.open(filename_AccountMaster, std::ios_base::app);
  
  //----------
  // Pad all fields with space to get maxi. length before writting to file
  //----------
  acctRec1.acctCode     = utility1.padRight(acctRec1.acctCode,     ' ', acctFldLen1.acctCode);
  acctRec1.acctDesc   = utility1.padRight(acctRec1.acctDesc,   ' ', acctFldLen1.acctDesc);
  acctRec1.acctType  = utility1.padRight(acctRec1.acctType,  ' ', acctFldLen1.acctType);
  acctRec1.Taxable   = utility1.padRight(acctRec1.Taxable,   ' ', acctFldLen1.Taxable);
  //
  acctRec1._endSpace  = utility1.padRight(acctRec1._endSpace,  ' ', acctFldLen1._endSpace); 
  //
  outfile << acctRec1.acctCode
          << acctRec1.acctDesc
          << acctRec1.acctType
          << acctRec1.Taxable
          << acctRec1._endSpace
          << "\n";
  //
  outfile.close(); 
}

//-------------------------------------------------------------------------------------//
// UPDATE Record
//-------------------------------------------------------------------------------------//
void AccountMaster::change_Record(AccountMasterRecord acctRec1)
{
  string  dataRow;
  streampos lastPos;
  AccountMasterRecord acctRec2;

  try
  {
    ifstream fileOld(filename_AccountMaster);
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
        split_DataRow_to_Fields(dataRow, acctRec2);
        //
        // is the Account Codeing number matched?
        if (acctRec1.acctCode!=acctRec2.acctCode)
        {
          // copy line to new file if not matched
          fileNew << dataRow << "\n";
        }
        else
        {
          //----------
          // Account Code record found, write new changed record
          //----------
          // Pad all fields with space to get maxi. length before writting to file
          acctRec1.acctCode  = utility1.padRight(acctRec1.acctCode, ' ', acctFldLen1.acctCode);
          acctRec1.acctDesc  = utility1.padRight(acctRec1.acctDesc, ' ', acctFldLen1.acctDesc);
          acctRec1.acctType  = utility1.padRight(acctRec1.acctType, ' ', acctFldLen1.acctType);
          acctRec1.Taxable   = utility1.padRight(acctRec1.Taxable,  ' ', acctFldLen1.Taxable );
          //
          acctRec1._endSpace  = utility1.padRight(acctRec1._endSpace,  ' ', acctFldLen1._endSpace); 
          //
          fileNew << acctRec1.acctCode
                  << acctRec1.acctDesc
                  << acctRec1.acctType
                  << acctRec1.Taxable
                  << acctRec1._endSpace
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
    remove(filename_AccountMaster.c_str());
    // rename old to new
    rename(filename_TempOutput.c_str(), filename_AccountMaster.c_str());

  }
  catch (int e)
  {
      // exception handling at here
  }
}

//-------------------------------------------------------------------------------------//
// DELETE Record
//-------------------------------------------------------------------------------------//
void AccountMaster::delete_Record(std::string accountCode)
{
  string  dataRow;
  AccountMasterRecord acctRec2;

  try
  {
    ifstream fileOld(filename_AccountMaster);
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
        split_DataRow_to_Fields(dataRow, acctRec2);
        //
        // skip if the Account Code matched (delete)?
        if (acctRec2.acctCode==accountCode)
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
    remove(filename_AccountMaster.c_str());
    // rename old to new
    rename(filename_TempOutput.c_str(), filename_AccountMaster.c_str());

  }
  catch (int e)
  {
      // exception handling at here
  }
}

//-------------------------------------------------------------------------------------//
// Is valid Account Code Record  (with struct initialization)
//-------------------------------------------------------------------------------------//
bool AccountMaster::isValid_AccountMasterKey2(string accountCode)
{
    acctRec1.initialize();
    acctFldLen1.initialize();
    acctFldChg1.initialize();
    
    return isValid_AccountMasterKey(accountCode);
}

//-------------------------------------------------------------------------------------//
// Is valid Account Code Record  
//-------------------------------------------------------------------------------------//
bool AccountMaster::isValid_AccountMasterKey(string accountCode)
{
  string  dataRow;
  acctRec1.initialize();


  try
  {
    ifstream file1 (filename_AccountMaster);
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
        split_DataRow_to_Fields(dataRow, acctRec1);
        //
        // Account code found
        if (acctRec1.acctCode==accountCode)
        {
          file1.close();
          return true;
        }
      }
      file1.close();
    }    
    // Account code not found
    return false;
  }
  catch (int e)
  {
    // exception handling at here
  }
}

