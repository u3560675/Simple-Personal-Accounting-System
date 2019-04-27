//-----------------------------------------------------------------------
// Description : Accounting System - Transaction - Class
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
#include "Transaction.h"
#include "Utility.h"
#include <bits/stdc++.h> 

using namespace std;

extern Utility utility1;
extern AccountMaster accountMaster1;
BudgetMaster budgetMaster1;

// Transaction record structure   (details definition: pls check header file)
struct Transaction::TransactionRecord transRec1;
struct Transaction::TransactionFldLen transFldLen1;
struct Transaction::TransactionFldChg transFldChg1;

extern struct BudgetMaster::BudgetMasterRecord bdgtRec1;

vector<tuple<string, string, string, string, string, string, string, string, string> > recordList_Trans; 


//-------------------------------------------------------------------------------------//
// Sub-menu:  ACCOUNT CODE
//-------------------------------------------------------------------------------------//
void Transaction::Menu()
{
  char selection;
    
    transRec1.initialize();
    transFldLen1.initialize();
    transFldChg1.initialize();
    
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
      cout << "|           1. Add New Transection                                        |" << endl;
      cout << "|           2. Change Transection                                         |" << endl;
      cout << "|           3. Delete Transection                                         |" << endl;
      cout << "|           4. Search / List Transection                                  |" << endl;
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
          Add_Transaction();
          continue;
        case '2' :
          cout.flush();
          cin.ignore();
          Change_Transaction();
          continue;
        case '3' :
          cout.flush();
          cin.ignore();
          Delete_Transaction();
          continue;
        case '4' :
          cout.flush();
          cin.ignore();
          Search_Transaction(true, true);
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
// Add Transaction Record
//-------------------------------------------------------------------------------------//
void Transaction::Add_Transaction()
{
  int counter1 = 0;
  string choice1 = "";
  string choice2 = "";
  string input1 = "";
  string TransDate = "";
  string newValueA = "";
  int    dd = 0;
  int    mm = 0;
  int    yyyy = 0;
  transFldLen1.initialize();



  //----------
  // ADD - Transaction Record
  //----------
  while (true)
  {
    //----------
    // Input - Transaction Date
    //----------
    system("cls");
    counter1 = 1;
    transRec1.initialize();   //clear all field values
    while (true)
    {
      // input Transaction Date  (Primary Key)
      cout << "\n";
      cout << "Please enter date of the transaction record." << endl;
      cout << counter1 << ") Transaction Date (dd-mm-yyyy): ";
      getline (cin, TransDate);
  
      if (TransDate.length()!=transFldLen1.transDate)
      {
        cout << "> Invalid Transaction Date. Input must be exactly " << transFldLen1.transDate << " characters. Please retry." << endl;
        cout << "Retry? (Y/N): ";
        getline (cin, choice1);
        if (choice1 == "N" || choice1 == "n")      return;                // exit
        else                                       continue;



        cout.flush();
        continue;
      }        
      if (TransDate.substr(2,1)!="-" ||
          TransDate.substr(5,1)!="-")
    	{
    		cout << "> Invalid Date separator. Valid: '-'. Please retry." << endl;
    		cout.flush();
    		continue;
    	}
    	if (utility1.isNumber(TransDate.substr(0,2), false, false)==false ||
    		utility1.isNumber(TransDate.substr(3,2), false, false)==false ||
    		utility1.isNumber(TransDate.substr(6,4), false, false)==false)
    	{
    		cout << "> Invalid Date numeric value. Please retry." << endl;
    		cout.flush();
    		continue;
    	}
    	dd   = stoi(TransDate.substr(0,2));
    	mm   = stoi(TransDate.substr(3,2));
    	yyyy = stoi(TransDate.substr(6,4));
    	if (utility1.isValidDate(dd, mm, yyyy)==false)
    	{
    		cout << "> Invalid Transaction Date value. Please retry." << endl;
    		cout.flush();
    		continue;
    	}        
      transRec1.transDate = TransDate;
      break;
    }
    
	//----------
    // Input - Account Code 1 (Debit)
    //----------
	counter1++;
    while (true)
    {
      // input Account code
      cout << "\n";
      cout << counter1 << ") Account Code (Debit): ";
      getline (cin, input1);
  
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
        cout.flush();
        continue;
      }
      transRec1.acctCode1 = input1;
      break;
    }
	
	//----------
    // Input - Account Code 2 (Credit)
    //----------
	counter1++;
    while (true)
    {
      // input Account code
      cout << "\n";
      cout << counter1 << ") Account Code (Credit): ";
      getline (cin, input1);
  
      if (input1.length()!=transFldLen1.acctCode2)
      {
        cout << "> Invalid Account code. Input must be exactly " << transFldLen1.acctCode2 << " characters. Please retry." << endl;
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
        cout.flush();
        continue;
      }
      transRec1.acctCode2 = input1;
      break;
    }
	
    //----------
    // Input - Transaction Amount
    //----------
    counter1++;
    while (true)
    {
      // input 
      cout << "\n";
      cout << counter1 << ") Transaction Amount (1-999999.99): ";
      getline (cin, input1);
      
      input1 = utility1.trim(input1);
      if (input1 == "")
      {
        cout << "> Invalid Transaction Amount. Cannot be empty. Please retry." << endl;
        cout.flush();
        continue;
      }        
      if (input1.length()>transFldLen1.amount)
      {
        cout << "> Invalid Transaction Amount. Maxi. " << transFldLen1.amount << " characters. Please retry." << endl;
        cout.flush();
        continue;
      }        
      if (utility1.isNumber(input1, false, true)==false)
      {
        cout << "> Transaction Amount is not a numeric value. Please retry." << endl;
        cout.flush();
        continue;
      }   
      if (stod(input1)==0)
      {
        cout << "> Transaction Amount must > 0. Please retry." << endl;
        cout.flush();
        continue;
      }        
      if (stod(input1)>999999.99)
      {
        cout << "> Transaction Amount cannot exceed 999999.99. Please retry." << endl;
        cout.flush();
        continue;
      }

      transRec1.amount = utility1.formatStringToDecimal(input1, 2);
      break;
    }
    
    //----------
    // Input - Reference Number
    //----------
    counter1++;
    while (true)
    {
      // input 
      cout << "\n";
      cout << counter1 << ") Reference Number: ";
      getline (cin, input1);
      
      input1 = utility1.trim(input1);
      if (input1 == "")
      {
        cout << "> Invalid Reference Number. Cannot be empty. Please retry." << endl;
        cout.flush();
        continue;
      }        
      if (input1.length()>transFldLen1.refNbr)
      {
        cout << "> Invalid Reference Number. Maxi. " << transFldLen1.refNbr << " characters. Please retry." << endl;
        cout.flush();
        continue;
      }
	  
      transRec1.refNbr = input1;
      break;
    }
    
    //----------
    // Input - Transaction Type
    //----------
    counter1++;
    while (true)
    {
      // input 
      cout << "\n";
      cout << counter1 << ") Transaction Type: ";
      getline (cin, input1);
      
      input1 = utility1.trim(input1);
      if (input1 == "")
      {
        cout << "> Invalid Transaction Type. Cannot be empty. Please retry." << endl;
        cout.flush();
        continue;
      }        
      if (input1.length()>transFldLen1.transType)
      {
        cout << "> Invalid Transaction Type. Maxi. " << transFldLen1.transType << " characters. Please retry." << endl;
        cout.flush();
        continue;
      }
	  
      transRec1.transType = input1;
      break;
    }
    
    //----------
    // Input - Description
    //----------
    counter1++;
    while (true)
    {
      // input 
      cout << "\n";
      cout << counter1 << ") Description: ";
      getline (cin, input1);
      
      input1 = utility1.trim(input1);
      if (input1 == "")
      {
        cout << "> Invalid Description. Cannot be empty. Please retry." << endl;
        cout.flush();
        continue;
      }        
      if (input1.length()>transFldLen1.transDesc)
      {
        cout << "> Invalid Description. Maxi. " << transFldLen1.transDesc << " characters. Please retry." << endl;
        cout.flush();
        continue;
      }
	  
      transRec1.transDesc = input1;
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
        add_Record(transRec1);
        break;
      }
    }  
    
    //-------------------
    // Budget Alert Check
    //-------------------
    Alert_Budget(transRec1.acctCode1, transRec1.transDate, true);
    
    if (transRec1.acctCode1 != transRec1.acctCode2)
    {
      Alert_Budget(transRec1.acctCode2, transRec1.transDate, true);
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
// Modify Transaction Record
//-------------------------------------------------------------------------------------//
void Transaction::Change_Transaction()
{
  string choice1 = "";
  string choice2 = "";
  string input  = "";
  string lineNum = "";
  string newValueA = "";
  int    numValue1 = 0;
  int    numValue2 = 0;
  int    numValue3 = 0;
  int    dd = 0;
  int    mm = 0;
  int    yyyy = 0;
  bool   isDone;
  transFldLen1.initialize();
  
  //----------
  // User selection
  //----------
  system("cls");
  while (true)
  {
    // List records according to different methods
    Search_Transaction(false, false); // do not show detail, do not loop in search function
    
    //----------
    // Exit
    //----------
    if (recordList_Trans.size()==0)
    {
      cout << "\n";
      cout.flush();
      return;     // exit
    }
    
    //----------
    // Lookup Primary Key (LineID) to Edit
    //----------
  	transRec1.initialize();
    transFldChg1.initialize();
  	while (true)
    {
      // Futher selection_lineNum
      cout << "Please select the line number of the record to EDIT." << endl;
      cout << "(Line number can be found at the first column of above list)" << endl;
      cout << "Enter 'X' now to exit." << endl;
      cout << "Please enter line number (1-" << recordList_Trans.size() << "): ";     // recordList_Trans.size() for getting the number of records written in the file
      // read the input
      getline (cin, lineNum);
      
      // Exit...
      if (lineNum=="X" ||
          lineNum=="x")
      {
        cout << "\n";
        system("cls");
        return;     // exit
      }
      
      // Display Transaction Record detail
      if (utility1.isNumber(lineNum, false, false)==true && stoi(lineNum) > 0 && stoi(lineNum) <= recordList_Trans.size())
      {
        // Get Record details
    		getRec_by_TransactionLineID(get<1>(recordList_Trans[stoi(lineNum) - 1]), transRec1);
    		break;
      }
  	  cout << "\n>> Invalid input.  Please retry." << endl;
  	  system("pause");
  	  continue;
    }
	
    //-----------
    // Start to EDIT...
    //-----------
    while (true)
    {
      system("cls");
      cout << "EDIT Transaction record:" << endl;
      cout << "*****************************************************" << endl;
  	  cout << transFldChg1.transDate   << " 1) Transaction Date .........: " << transRec1.transDate << endl;
      cout << transFldChg1.acctCode1   << " 2) Account Code (Debit) .....: " << transRec1.acctCode1 << endl;
      cout << transFldChg1.acctCode2   << " 3) Account Code (Credit).....: " << transRec1.acctCode2 << endl;
      cout << transFldChg1.amount      << " 4) Transaction Amount........: " << transRec1.amount    << endl; 
      cout << transFldChg1.refNbr      << " 5) Reference Number .........: " << transRec1.refNbr    << endl;
      cout << transFldChg1.transType   << " 6) Transaction Type..........: " << transRec1.transType << endl;
      cout << transFldChg1.transDesc   << " 7) Description ..............: " << transRec1.transDesc << endl;
      cout << "*****************************************************" << endl; 
      cout << "Select which field (1-7) to change and press <Enter>." << endl;
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
        change_Record(transRec1);
        

        cout << "New values are saved successfully to file." << endl;
        
        // Budget Alert Check
        Alert_Budget(transRec1.acctCode1, transRec1.transDate, true);
        
        if (transRec1.acctCode1 != transRec1.acctCode2)
        {
          Alert_Budget(transRec1.acctCode2, transRec1.transDate, true);
        }
        
        cout << "Press <Enter> to continue." << endl;
        getline (cin, choice2);
        cout << "\n";
        cout.flush();
        break;     // saved & exit
      }
      // is selected field number valid? 
      if (choice2.empty() ||
          utility1.isNumber(choice2, false, false)==false || 
          stoi(choice2) <= 0 || stoi(choice2) > 7)
      {
        cout << "> Invalid selection. Valid field number is (1-7).  Please <Enter> to retry." << endl;
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
            cout << "Transaction Date ................: " + transRec1.transDate << endl;
    		    cout << "Transaction Date (dd-mm-yyyy): ";
            // read the input
            getline (cin, newValueA);
            
            if (newValueA=="X" ||
                newValueA=="x")
            {
              cout << "\n";
              cout.flush();
              return;     // exit
            }
            
            // is valid input?
            if (newValueA.length()!=transFldLen1.transDate)
            {
              cout << "> Invalid Transaction Date. Input must be exactly " << transFldLen1.transDate << " characters. Please retry." << endl;
              cout << "Retry? (Y/N): ";
              getline (cin, choice1);
              if (choice1 == "N" || choice1 == "n")      return;                // exit
              else                                       continue;
              
              cout.flush();
              continue;
            }        
            if (newValueA.substr(2,1)!="-" ||
                newValueA.substr(5,1)!="-")
            {
          	  cout << "> Invalid Date separator. Valid: '-'. Please retry." << endl;
              cout << "Retry? (Y/N): ";
              getline (cin, choice1);
              if (choice1 == "N" || choice1 == "n")      return;                // exit
              else                                       continue;
              
          		cout.flush();
          		continue;
            }
            if (utility1.isNumber(newValueA.substr(0,2), false, false)==false ||
          	    utility1.isNumber(newValueA.substr(3,2), false, false)==false ||
          	    utility1.isNumber(newValueA.substr(6,4), false, false)==false)
            {
            	cout << "> Invalid Date numeric value. Please retry." << endl;
      		    cout << "Retry? (Y/N): ";
              getline (cin, choice1);
              if (choice1 == "N" || choice1 == "n")      return;                // exit
              else                                       continue;
          	cout.flush();
          	continue;
            }
            dd   = stoi(newValueA.substr(0,2));
            mm   = stoi(newValueA.substr(3,2));
            yyyy = stoi(newValueA.substr(6,4));
            if (utility1.isValidDate(dd, mm, yyyy)==false)
            {
      		    cout << "> Invalid Transaction Date value. Please retry." << endl;
      		    cout << "Retry? (Y/N): ";
              getline (cin, choice1);
              if (choice1 == "N" || choice1 == "n")      return;                // exit
              else                                       continue;
        		  cout.flush();
        		  continue;
        	  }        
        	  
        	  transRec1.transDate = newValueA;
      			transFldChg1.transDate = '*';
        		isDone = true;
          	break;
          	
          case 2:
            cout << "Account Code (Debit) ................: " + transRec1.acctCode1 << endl;
            cout << "Enter new Debit Account Code: ";
      			getline (cin, newValueA);
      			newValueA = utility1.trim(newValueA);
            if (newValueA.length()!=transFldLen1.acctCode1)
      			{
      			  cout << "> Invalid Account code. Input must be exactly " << transFldLen1.acctCode1 << " characters. Please retry." << endl;
      			  cout.flush();
              continue;
      			}
      			if (accountMaster1.isValid_AccountMasterKey2(newValueA)==false)    
      			{
      			  cout << "> Error - Account code is not valid. Please retry." << endl;
      			  cout.flush();
      			  continue;
      			}
      			transRec1.acctCode1 = newValueA;
      			transFldChg1.acctCode1 = '*';
            isDone = true;
      			break;

          case 3:
            cout << "Account Code (Credit) ................: " + transRec1.acctCode2 << endl;
            cout << "Enter new Credit Account Code: ";
      			getline (cin, newValueA);
      			newValueA = utility1.trim(newValueA);
            if (newValueA.length()!=transFldLen1.acctCode2)
      			{
      			  cout << "> Invalid Account code. Input must be exactly " << transFldLen1.acctCode2 << " characters. Please retry." << endl;
      			  cout.flush();
                    continue;
      			}
      			if (accountMaster1.isValid_AccountMasterKey2(newValueA)==false)    
      			{
      			  cout << "> Error - Account code is not valid. Please retry." << endl;
      			  cout.flush();
      			  continue;
      			}
      			transRec1.acctCode2 = newValueA;
      			transFldChg1.acctCode2 = '*';
            isDone = true;
      			break;

		      case 4:
			      cout << "Transaction Amount ..............: " + transRec1.amount << endl;
            cout << "Enter new value (1-999999.99): ";
            getline (cin, newValueA);
            newValueA = utility1.trim(newValueA);
            if (newValueA == "")
            {
              cout << "> Invalid Transaction Amount. Cannot be empty. Please retry." << endl;
              cout.flush();
              continue;
            }        
            if (newValueA.length()>transFldLen1.amount)
            {
              cout << "> Invalid Transaction Amount. Maxi. " << transFldLen1.amount << " characters. Please retry." << endl;
              cout.flush();
              continue;
            }        
            if (utility1.isNumber(newValueA, false, true)==false)
            {
              cout << "> Transaction Amount is not a numeric value. Please retry." << endl;
              cout.flush();
              continue;
            }   
            if (stod(newValueA)==0)
            {
              cout << "> Transaction Amount must > 0. Please retry." << endl;
              cout.flush();
              continue;
            }      
            if (stod(newValueA)>999999.99)
            {
              cout << "> Transaction Amount cannot exceed 999999.99. Please retry." << endl;
              cout.flush();
              continue;
            }
            transRec1.amount = utility1.formatStringToDecimal(newValueA, 2);
            transFldChg1.amount = '*';
            isDone = true;
            break;

	        case 5:
		        cout << "Reference Number ................: " + transRec1.refNbr << endl;
            cout << "Enter new Credit Account Code: ";
      			getline (cin, newValueA);
      			newValueA = utility1.trim(newValueA);
      			if (newValueA == "")
    		    {
      			  cout << "> Invalid Reference Number. Cannot be empty. Please retry." << endl;
      			  cout.flush();
      			  continue;
    		    }
            if (newValueA.length()>transFldLen1.refNbr)
			      {
      			  cout << "> Invalid Reference Number. Maxi. " << transFldLen1.refNbr << " characters. Please retry." << endl;
      			  cout.flush();
              continue;
      			}
      			transRec1.refNbr = newValueA;
      			transFldChg1.refNbr = '*';
            isDone = true;
		      	break;

		      case 6:
      			cout << "Transaction Type ................: " + transRec1.transType << endl;
            cout << "Enter new Credit Account Code: ";
      			getline (cin, newValueA);
      			
      			newValueA = utility1.trim(newValueA);
      			if (newValueA == "")
      	    {
        		  cout << "> Invalid Transaction Type. Cannot be empty. Please retry." << endl;
        		  cout.flush();
        		  continue;
      	    }
            if (newValueA.length()>transFldLen1.transType)
      			{
      			  cout << "> Invalid Transaction Type. Maxi. " << transFldLen1.transType << " characters. Please retry." << endl;
      			  cout.flush();
              continue;
      			}
      			transRec1.transType = newValueA;
      			transFldChg1.transType = '*';
            isDone = true;
      			break;

    		  case 7:
      			cout << "Description ................: " + transRec1.transDesc << endl;
            cout << "Enter new Credit Account Code: ";
      			getline (cin, newValueA);
      			
      			newValueA = utility1.trim(newValueA);
      			if (newValueA == "")
      	    {
        		  cout << "> Invalid Description. Cannot be empty. Please retry." << endl;
        		  cout.flush();
        		  continue;
      	    }
            if (newValueA.length()>transFldLen1.transDesc)
      			{
      			  cout << "> Invalid Description. Maxi. " << transFldLen1.transDesc << " characters. Please retry." << endl;
      			  cout.flush();
              continue;
      			}
      			transRec1.transDesc = newValueA;
      			transFldChg1.transDesc = '*';
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
// Delete Transaction Record
//-------------------------------------------------------------------------------------//
void Transaction::Delete_Transaction()
{
  string choice1 = "";
  string choice2 = "";
  string input  = "";
  string lineNum = "";
  bool   isDone;
  transFldLen1.initialize();
  
  //----------
  // User selection
  //----------
  system("cls");
  while (true)
  {
    // List methods
    Search_Transaction(false, false); // do not show detail, do not loop in search function
    
    //----------
    // Exit
    //----------
    if (recordList_Trans.size()==0)
    {
      cout << "\n";
      cout.flush();
      return;     // exit
    }
    
    //----------
    // Lookup Primary Key (LineID) to Delete
    //----------
  	transRec1.initialize();
  	while (true)
    {
      // Futher selection_lineNum
      cout << "Please select the line number of the record to DELETE." << endl;
      cout << "(Line number can be found at the first column of above list)" << endl;
      cout << "Enter 'X' now to exit." << endl;
      cout << "Please enter line number (1-" << recordList_Trans.size() << "): ";     // recordList_Trans.size() for getting the number of records written in the file
      // read the input
      getline (cin, lineNum);
      
      // Exit...
      if (lineNum=="X" ||
          lineNum=="x")
      {
        cout << "\n";
        system("cls");
        return;     // exit
      }
      
      // Display Transaction Record detail
      if (utility1.isNumber(lineNum, false, false)==true && stoi(lineNum) > 0 && stoi(lineNum) <= recordList_Trans.size())
      {
        // Get Record details
    		getRec_by_TransactionLineID(get<1>(recordList_Trans[stoi(lineNum) - 1]), transRec1);
    		break;
      }
  	  cout << "\n>> Invalid input.  Please retry." << endl;
  	  system("pause");
  	  continue;
    }
	
    //-----------
    // Start to DELETE...
    //-----------
    while (true)
    {
      system("cls");
      cout << "DELETE Transaction record:" << endl;
      cout << "*****************************************************"  << endl;
  	  cout << "Transaction Date .............: " << transRec1.transDate << endl;
      cout << "Account Code (Debit) .........: " << transRec1.acctCode1 << endl;
      cout << "Account Code (Credit).........: " << transRec1.acctCode2 << endl;
      cout << "Transaction Amount............: " << transRec1.amount    << endl; 
      cout << "Reference Number .............: " << transRec1.refNbr    << endl;
      cout << "Transaction Type..............: " << transRec1.transType << endl;
      cout << "Description ..................: " << transRec1.transDesc << endl;
      cout << "*****************************************************"  << endl; 
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
      delete_Record(transRec1);


      cout << "> Selected record is deleted." << endl;
      cout << "\n";
      cout.flush();
      
      break;
      
    }
	
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
      break;          // exit Delete function
    }
    
    system("cls");
    
  }   // loop: Select next Account Codeing record to modify
}

//-------------------------------------------------------------------------------------//
// Search Transaction Record
//-------------------------------------------------------------------------------------//
void Transaction::Search_Transaction(bool showDetail, bool Loop)
{
  string choice1 = "";
  string choice2 = "";
  string input1  = "";
  string lineNum = "";
  int    dd = 0;
  int    mm = 0;
  int    yyyy = 0;
  transFldLen1.initialize();

  //----------
  // User selection
  //----------
  system("cls");
  while (true)
  {
    // clear all field values
    transRec1.initialize();
            
    // How to search
    cout << "\n";
  	cout << "Search by:  1) Transaction Date" << endl;
    cout << "            2) Month" << endl;
  	cout << "            3) Year" << endl;
  	cout << "            4) Account Code (Debit / Credit)" << endl;
  	cout << "            5) Amount" << endl;
  	cout << "            6) Reference Number" << endl;
  	cout << "            7) Transaction Type" << endl;
  	cout << "            8) Description" << endl;
  	cout << "            L) List all records" << endl;
  	cout << "            X) Exit" << endl;
	
	
    cout << "Selection: ";
    
    getline (cin, choice1);

    //
    if (choice1 != "1" &&
        choice1 != "2" &&
    		choice1 != "3" &&
    		choice1 != "4" &&
    		choice1 != "5" &&
    		choice1 != "6" &&
    		choice1 != "7" &&
    		choice1 != "8" &&
    		choice1 != "9" &&
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
      recordList_Trans.clear();
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
      List_Records(showDetail);         // list all records, show detail
      if(Loop == false)     return;       // exit
      else                  continue;     // loop back to search menu
    }
    //----------
    // List by Transaction Date
    //----------
    else if (choice1=="1")
    {
      while (true)
      {
        cout << "Please enter Transaction Date to list. Enter 'X' to exit.";
		    cout << "Transaction Date (dd-mm-yyyy): ";
        // read the input
        getline (cin, input1);
        
        if (input1=="X" ||
            input1=="x")
        {
          cout << "\n";
          cout.flush();
          return;     // exit
        }
        
        // is valid input?
        if (input1.length()!=transFldLen1.transDate)
        {
          cout << "> Invalid Transaction Date. Input must be exactly " << transFldLen1.transDate << " characters. Please retry." << endl;
          cout << "Retry? (Y/N): ";
          getline (cin, choice1);
          if (choice1 == "N" || choice1 == "n")      return;                // exit
          else                                       continue;
          
          cout.flush();
          continue;
        }        
        if (input1.substr(2,1)!="-" ||
            input1.substr(5,1)!="-")
        {
      	  cout << "> Invalid Date separator. Valid: '-'. Please retry." << endl;
          cout << "Retry? (Y/N): ";
          getline (cin, choice1);
          if (choice1 == "N" || choice1 == "n")      return;                // exit
          else                                       continue;
          
      		cout.flush();
      		continue;
        }
        if (utility1.isNumber(input1.substr(0,2), false, false)==false ||
      	  utility1.isNumber(input1.substr(3,2), false, false)==false ||
      	  utility1.isNumber(input1.substr(6,4), false, false)==false)
        {
        	cout << "> Invalid Date numeric value. Please retry." << endl;
  		    cout << "Retry? (Y/N): ";
          getline (cin, choice1);
          if (choice1 == "N" || choice1 == "n")      return;                // exit
          else                                       continue;
      	cout.flush();
      	continue;
        }
        dd   = stoi(input1.substr(0,2));
        mm   = stoi(input1.substr(3,2));
        yyyy = stoi(input1.substr(6,4));
        if (utility1.isValidDate(dd, mm, yyyy)==false)
        {
  		    cout << "> Invalid Transaction Date value. Please retry." << endl;
  		    cout << "Retry? (Y/N): ";
          getline (cin, choice1);
          if (choice1 == "N" || choice1 == "n")      return;                // exit
          else                                       continue;
    		  cout.flush();
    		  continue;
    	  }        
		
        List_Records("TransDate", input1, showDetail);        // list with detail
        break;
      }
    }
    //----------
    // List by Transaction Month
    //----------
    else if (choice1=="2")
    {
      while (true)
      {
        cout << "Please enter Transaction Month to list. Enter 'X' to exit.";
		    cout << "Transaction Month (mm-yyyy): ";
        // read the input
        getline (cin, input1);
        
        if (input1=="X" ||
            input1=="x")
        {
          cout << "\n";
          cout.flush();
          return;     // exit
        }
        
        // is valid input?
        if (input1.length()!=7)
        {
          cout << "> Invalid Transaction Month. Input must be exactly 7 characters. Please retry." << endl;
          cout << "Retry? (Y/N): ";
          getline (cin, choice1);
          if (choice1 == "N" || choice1 == "n")      return;                // exit
          else                                       continue;
  
          cout.flush();
          continue;
        }        
        if (input1.substr(2,1)!="-")
        {
        	cout << "> Invalid Month separator. Valid: '-'. Please retry." << endl;
          cout << "Retry? (Y/N): ";
          getline (cin, choice1);
          if (choice1 == "N" || choice1 == "n")      return;                // exit
          else                                       continue;
    
      		cout.flush();
      		continue;
        }
        if (utility1.isNumber(input1.substr(0,2), false, false)==false ||
      	  utility1.isNumber(input1.substr(3,4), false, false)==false)
        {
      	  cout << "> Invalid Month numeric value. Please retry." << endl;
  		    cout << "Retry? (Y/N): ";
          getline (cin, choice1);
          if (choice1 == "N" || choice1 == "n")      return;                // exit
          else                                       continue;
      	  cout.flush();
      	  continue;
        }
        mm   = stoi(input1.substr(0,2));
        yyyy = stoi(input1.substr(3,4));
        if (utility1.isValidDate(01, mm, yyyy)==false)    // dummy day that always exists, as only filtering by month and year
        {
      		cout << "> Invalid Transaction Month value. Please retry." << endl;
      		cout << "Retry? (Y/N): ";
          getline (cin, choice1);
          if (choice1 == "N" || choice1 == "n")      return;                // exit
          else                                       continue;
      		cout.flush();
      		continue;
  	    }        
  		
        List_Records("*Month", input1, showDetail);        // list with detail
        break;
      }
    }
    //----------
    // List by Transaction Year
    //----------
    else if (choice1=="3")
    {
      while (true)
      {
        cout << "Please enter Transaction Year to list. Enter 'X' to exit.";
		    cout << "Transaction Year (yyyy): ";
        // read the input
        getline (cin, input1);
        
        if (input1=="X" ||
            input1=="x")
        {
          cout << "\n";
          cout.flush();
          return;     // exit
        }
        
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
        yyyy = stoi(input1);                                 // no need to use substring
        if (utility1.isValidDate(01, 01, yyyy)==false)    // dummy day and month that always exist, as only filtering by year
        {
      		cout << "> Invalid Transaction Year value. Please retry." << endl;
      		cout << "Retry? (Y/N): ";
          getline (cin, choice1);
          if (choice1 == "N" || choice1 == "n")      return;                // exit
          else                                       continue;
      		cout.flush();
      		continue;
  	    }        
  		
        List_Records("*Year", input1, showDetail);        // list with detail
        break;
      }
    }
	  //----------
    // List by Account Code (Debit / Credit)
    //----------
    else if (choice1=="4")
    {
      while (true)
      {
        cout << "Please enter an Account Code to list. Enter 'X' to exit.";
		    cout << "Account Code: ";
        // read the input
        getline (cin, input1);
        
        if (input1=="X" ||
            input1=="x")
        {
          cout << "\n";
          cout.flush();
          return;     // exit
        }
        
        // is valid input?
        if (input1.length()!=transFldLen1.acctCode1)     // transFldLen1.acctCode1 = transFldLen1.acctCode2
        {
          cout << "> Invalid Account Code. Input must be exactly " << transFldLen1.acctCode1 << " characters. Please retry." << endl;
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
  		
        List_Records("*AcctCode", input1, showDetail);        // list with detail
        break;
      }
    }
	  //----------
    // List by Transaction Amount
    //----------
    else if (choice1=="5")
    {
      while (true)
      {
        cout << "Please enter an Transaction Amount to list. Enter 'X' to exit.";
		    cout << "Transaction Amount  (1-999999.99): ";
        // read the input
        getline (cin, input1);
        
        if (input1=="X" ||
            input1=="x")
        {
          cout << "\n";
          cout.flush();
          return;     // exit
        }
        
        // is valid input?
  	    input1 = utility1.trim(input1);
        if (input1 == "")
        {
          cout << "> Invalid Transaction Amount. Cannot be empty. Please retry." << endl;
  		    cout << "Retry? (Y/N): ";
          getline (cin, choice1);
          if (choice1 == "N" || choice1 == "n")      return;                // exit
          else                                       continue;
  
          cout.flush();
          continue;
        }        
        if (input1.length()>transFldLen1.amount)
        {
          cout << "> Invalid Transaction Amount. Maxi. " << transFldLen1.amount << " characters. Please retry." << endl;
  		    cout << "Retry? (Y/N): ";
          getline (cin, choice1);
          if (choice1 == "N" || choice1 == "n")      return;                // exit
          else                                       continue;
  
          cout.flush();
          continue;
        }        
        if (utility1.isNumber(input1, false, true)==false)
        {
          cout << "> Transaction Amount is not a numeric value. Please retry." << endl;
  		    cout << "Retry? (Y/N): ";
          getline (cin, choice1);
          if (choice1 == "N" || choice1 == "n")      return;                // exit
          else                                       continue;
  
          cout.flush();
          continue;
        }   
        if (stod(input1)==0)
        {
          cout << "> Transaction Amount must > 0. Please retry." << endl;
  		    cout << "Retry? (Y/N): ";
          getline (cin, choice1);
          if (choice1 == "N" || choice1 == "n")      return;                // exit
          else                                       continue;
  
          cout.flush();
          continue;
        }        
        if (stod(input1)>999999.99)
        {
          cout << "> Transaction Amount cannot exceed 999999.99. Please retry." << endl;
  		    cout << "Retry? (Y/N): ";
          getline (cin, choice1);
          if (choice1 == "N" || choice1 == "n")      return;                // exit
          else                                       continue;
  
          cout.flush();
          continue;
        }
	  
        List_Records("Amount", input1, showDetail);        // list with detail
        break;
      }
    }
	  //----------
    // List by Reference Number
    //----------
    else if (choice1=="6")
    {
      while (true)
      {
        cout << "Please enter a Reference Number to list. Enter 'X' to exit.";
		    cout << "Reference Number: ";
        // read the input
        getline (cin, input1);
        
        if (input1=="X" ||
            input1=="x")
        {
          cout << "\n";
          cout.flush();
          return;     // exit
        }
        
        // is valid input?
  	     input1 = utility1.trim(input1);
        if (input1 == "")
        {
          cout << "> Invalid Reference Number. Cannot be empty. Please retry." << endl;
  		    cout << "Retry? (Y/N): ";
          getline (cin, choice1);
          if (choice1 == "N" || choice1 == "n")      return;                // exit
          else                                       continue;
  
          cout.flush();
          continue;
        }        
        if (input1.length()>transFldLen1.refNbr)
        {
          cout << "> Invalid Reference Number. Maxi. " << transFldLen1.refNbr << " characters. Please retry." << endl;
  		    cout << "Retry? (Y/N): ";
          getline (cin, choice1);
          if (choice1 == "N" || choice1 == "n")      return;                // exit
          else                                       continue;
  
          cout.flush();
          continue;
        }
      
        List_Records("RefNbr", input1, showDetail);        // list with detail
        break;
      }
    }
	  //----------
    // List by Transaction Type
    //----------
    else if (choice1=="7")
    {
      while (true)
      {
        cout << "Please enter a Transaction Type to list. Enter 'X' to exit.";
		    cout << "Transaction Type: ";
        // read the input
        getline (cin, input1);
        
        if (input1=="X" ||
            input1=="x")
        {
          cout << "\n";
          cout.flush();
          return;     // exit
        }
        
        // is valid input?
  	    input1 = utility1.trim(input1);
        if (input1 == "")
        {
          cout << "> Invalid Transaction Type. Cannot be empty. Please retry." << endl;
  	  	  cout << "Retry? (Y/N): ";
          getline (cin, choice1);
          if (choice1 == "N" || choice1 == "n")      return;                // exit
          else                                       continue;
  
          cout.flush();
          continue;
        }        
        if (input1.length()>transFldLen1.transType)
        {
          cout << "> Invalid Transaction Type. Maxi. " << transFldLen1.transType << " characters. Please retry." << endl;
      		cout << "Retry? (Y/N): ";
          getline (cin, choice1);
          if (choice1 == "N" || choice1 == "n")      return;                // exit
          else                                       continue;
  
          cout.flush();
          continue;
        }
      
        List_Records("TransType", input1, showDetail);        // list with detail
        break;
      }
    }
	  //----------
    // List by Description
    //----------
    else if (choice1=="8")
    {
      while (true)
      {
        cout << "Please enter a Description to list. Enter 'X' to exit.";
		    cout << "Description: ";
        // read the input
        getline (cin, input1);
        
        if (input1=="X" ||
            input1=="x")
        {
          cout << "\n";
          cout.flush();
          return;     // exit
        }
        
        // is valid input?
  	    input1 = utility1.trim(input1);
        if (input1 == "")
        {
          cout << "> Invalid Description. Cannot be empty. Please retry." << endl;
  	     	cout << "Retry? (Y/N): ";
          getline (cin, choice1);
          if (choice1 == "N" || choice1 == "n")      return;                // exit
          else                                       continue;
  
          cout.flush();
          continue;
        }        
        if (input1.length()>transFldLen1.transDesc)
        {
          cout << "> Invalid Description. Maxi. " << transFldLen1.transDesc << " characters. Please retry." << endl;
  	     	cout << "Retry? (Y/N): ";
          getline (cin, choice1);
          if (choice1 == "N" || choice1 == "n")      return;                // exit
          else                                       continue;
  
          cout.flush();
          continue;
        }
      
        List_Records("TransDesc", input1, showDetail);        // list with detail
        break;
      }
    }
	
  	if(Loop == false)
  	{
  	  return;
    }
	
  }   // loop to search next record
}

//-------------------------------------------------------------------------------------//
// Display Record in Detail
//-------------------------------------------------------------------------------------//
void Transaction::Display_Transaction(string lineID)
{
  string  choice;
  transRec1.initialize();

  getRec_by_TransactionLineID(lineID, transRec1);
  if (utility1.trim(transRec1.lineID)=="")
  {
    cout << "> Invalid line number." << endl;
    system("pause");
    return;
  }
  
  //----------
  // Display Transaction Record detail
  //----------
  while (true) 
  {
    system("cls");
    cout << "Transaction record details:" << endl;
    cout << "*****************************************************"   << endl;
    cout << "Transaction Date .............: " << transRec1.transDate << endl;
    cout << "Account Code (Debit) .........: " << transRec1.acctCode1 << endl;
    cout << "Account Code (Credit).........: " << transRec1.acctCode2 << endl;
    cout << "Transaction Amount............: " << transRec1.amount    << endl; 
    cout << "Reference Number .............: " << transRec1.refNbr    << endl;
    cout << "Transaction Type..............: " << transRec1.transType << endl;
    cout << "Description ..................: " << transRec1.transDesc << endl;
    cout << "*****************************************************"   << endl; 
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
// List Transaction Records  (overload)
//-------------------------------------------------------------------------------------//
void Transaction::List_Records(bool showDetail)
{
    List_Records("*ALL", "", showDetail);
}
void Transaction::List_Records(string filterType, string filterValue, bool showDetail)
{
  string selection_lineNum;
  string selection_transDate;
  string valueToCheck;
  string valueToSort;
  string dataRow;
  int reccount = 0;
  transRec1.initialize();
  recordList_Trans.clear();


  while(true)
  {
    ifstream file1 (filename_Transaction);
    if (file1.is_open())
    {
      //----------
      // Display column hedders
      //----------
      system("cls");
      cout << "List of Transaction records:" << endl;
      cout << "****************************************************************************************" << endl;
      cout << " No.   TransDate   Acct Debit  Acct Credit    Amount        Ref No.         TransType   " << endl;
      cout << "----  -----------  ----------  -----------  ----------  ---------------  ---------------" << endl;

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
        split_DataRow_to_Fields(dataRow, transRec1);
        valueToCheck = "";
        if      (filterType=="TransDate")     valueToCheck = transRec1.transDate;   
        else if (filterType=="*Month")        valueToCheck = transRec1.transDate.substr(3,7);   
        else if (filterType=="*Year")         valueToCheck = transRec1.transDate.substr(6,4);   
        //else if (filterType=="*AcctCode")     valueToCheck = transRec1.acctCode1;    
		    else if (filterType=="Amount")        valueToCheck = transRec1.amount;  
		    else if (filterType=="RefNbr")        valueToCheck = transRec1.refNbr; 
		    else if (filterType=="TransType")     valueToCheck = transRec1.transType; 
		    else if (filterType=="TransDesc")     valueToCheck = transRec1.transDesc; 
        //
        if (filterType=="*ALL")
        {
          // do nothing
        }
        else if (filterType=="TransDate" && filterValue!=valueToCheck)          continue;     // not matched, skip
        else if (filterType=="*Month"    && filterValue!=valueToCheck)          continue;     // not matched, skip
        else if (filterType=="*Year"     && filterValue!=valueToCheck)          continue;     // not matched, skip
        else if (filterType=="*AcctCode" && filterValue!=transRec1.acctCode1 
                                         && filterValue!=transRec1.acctCode2)   continue;     // not matched, skip
        else if (filterType=="Amount")
        {
          if (stod(filterValue)!=stod(valueToCheck))                            continue;     // not matched, skip
        }
        else if (filterType=="RefNbr"  ||
                 filterType=="TransType" ||
                 filterType=="TransDesc")
       {
          if (valueToCheck.find(filterValue) == string::npos)
          {
            continue;        // skip if not match
          }
      }
        //
        // get data for sorting...
		    if      (filterType=="AcctCode1")     valueToSort = transRec1.acctCode1;   
        //else if (filterType=="Year")        valueToSort = transRec1.transDate;   
        else if (filterType=="TransDate")     valueToSort = transRec1.transDate;  
		    else if (filterType=="Amount")        valueToSort = transRec1.amount;  
        else                                  valueToSort = transRec1.lineID;
        //
        // display matched data...
        reccount++;
        recordList_Trans.push_back(make_tuple(
		    valueToSort,
        transRec1.lineID,
  		  transRec1.transDate,
  		  transRec1.acctCode1,
  		  transRec1.acctCode2,
  		  transRec1.amount, 
        transRec1.refNbr,
        transRec1.transType,
        transRec1.transDesc
          ));
      }
      file1.close();



      //----------
      // Sort Record list by first column (Line Number)
      //----------
      sort(recordList_Trans.begin(), recordList_Trans.end());



      //----------
      // Loop to display detail rows...  (sorted by Line Number)
      //----------
      for (int i = 0; i < recordList_Trans.size(); i++) 
      {
        cout << utility1.padLeft(to_string(i+1), '0', 4) << "   "     // Record No.(lineID + 1)
      			 << get<2>(recordList_Trans[i]) << "     "                // transDate
      			 << get<3>(recordList_Trans[i]) << "         "            // acctCode1
             << get<4>(recordList_Trans[i]) << "     "                // acctCode2
             << get<5>(recordList_Trans[i]) << "  "                   // amount
             << get<6>(recordList_Trans[i]) << "  "                   // refNbr
             << get<7>(recordList_Trans[i]) << ""                     // transType
             << "\n";
      }
      //recordList_Trans.clear();
    }    
    else
    {
      cout << "> Error!  Unable to open file";
    }  


    cout << "****************************************************************************************" << endl;
    if (reccount < 1)
    {
      // no record found, exit.
      cout << "\nNo Transaction record is available.\n" << endl;
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
    
    // Select Line Number detail
    while (true)
    {
      // Futher selection_lineNum
      cout << "Please select the line number of the record to search." << endl;
      cout << "(Line number can be found at the first column of above list)" << endl;
      cout << "Enter 'X' now to exit." << endl;
      cout << "Please enter line number (1-" << reccount << "): ";
      // read the input
      getline (cin, selection_lineNum);
      
      // Exit...
      if (selection_lineNum=="X" ||
          selection_lineNum=="x")
      {
        cout << "\n";
        system("cls");
        return;     // exit
      }
      
      // Display Transaction Record detail
      if (utility1.isNumber(selection_lineNum, false, false)==true && stoi(selection_lineNum) > 0 && stoi(selection_lineNum) <= reccount)
      {
        Display_Transaction(get<1>(recordList_Trans[stoi(selection_lineNum) - 1]));
        break;
      }
      
      
      // invalid input, retry
      cout << "\n>> Invalid input.  Please retry." << endl;
      system("pause");
    }
    recordList_Trans.clear();
  }
      
  system("pause");
  return;
}

//-------------------------------------------------------------------------------------//
// Split Transaction Record to Column Values 
//-------------------------------------------------------------------------------------//
bool Transaction::split_DataRow_to_Fields(std::string DataRow, Transaction::TransactionRecord& transRec1)
{
  transFldLen1.initialize();
  
  string* values = new string[transFldLen1._numOfFields];
  int    strPos = 0;
  int    endPos = -1;
  //TransactionFldLen transFldLen1;

  // load field length values into array for extraing field values
  // (check header file for correct field length values)
  //transFldLen1.initialize();
  for (int i=0; i<transFldLen1._numOfFields; i++)
  {
    values[i] = "";
    strPos = endPos+1;
    endPos = strPos + transFldLen1._val[i] - 1;
    //
    if (DataRow.length() >= endPos)       values[i] = DataRow.substr(strPos,    transFldLen1._val[i]);
    else                                  values[i] = utility1.padLeft("", ' ', transFldLen1._val[i]);
  }
 
  //----------
  // Loading data into struct
  //----------
  transRec1.lineID     = values[0];
  transRec1.transDate  = values[1];
  transRec1.acctCode1  = values[2];
  transRec1.acctCode2  = values[3];
  transRec1.amount     = values[4];
  transRec1.refNbr     = values[5];
  transRec1.transType  = values[6];
  transRec1.transDesc  = values[7];
  
  return true;
}

//-------------------------------------------------------------------------------------//
// Over-budget Warning
//-------------------------------------------------------------------------------------//
void Transaction::Alert_Budget(std::string acctCode, std::string date1, bool showAlert)
{
  string year;
  string month;
  string dataRow;
  double YTD = 0;
  double MTD = 0;
  double MTD_budget = 0;
  transRec1.initialize();
  
  // Get year value
  if (date1.length()==10)     year = date1.substr(6,4);     // if input is dd-mm-yyyy
  else if (date1.length()==7) year = date1.substr(3,4);     // if input is mm-yyyy
  else if (date1.length()==4) year = date1;                 // if input is yyyy
  
  // Get month + year value
  if (date1.length()==10)     month = date1.substr(3,7);    // if input is dd-mm-yyyy
  else if (date1.length()==7) month = date1;                // if input is mm-yyyy
  else month = "";                                          // if input is yyyy
  
  // Get budget record
  bdgtRec1.initialize();
  budgetMaster1.getRec_by_BudgetMasterKey(acctCode, year, bdgtRec1);
  if (bdgtRec1.acctCode == "" || bdgtRec1.alert != "Y" || stod(bdgtRec1.amount) == 0)
  {
    return;
  }
  
  // Get total Transaction Amount (YTD & MTD)
  ifstream file1 (filename_Transaction);
  if (file1.is_open())
  {
    while ( getline (file1, dataRow) )
    {
      if (utility1.trim(dataRow)=="")
      {
        continue;    // skip if space line
      }
      
      // Split data line into column values
      split_DataRow_to_Fields(dataRow, transRec1);
      
      // Does record match target account code 1
      if (transRec1.acctCode1 == acctCode)
      {
        // Accumulate YTD
        if (transRec1.transDate.substr(6,4) == year)     YTD += stod(transRec1.amount);
        
        // Accumulate MTD
        if (transRec1.transDate.substr(3,7) ==month)     MTD += stod(transRec1.amount);
      }
      
      // Does record match target account code 2
      if (transRec1.acctCode2 == acctCode)
      {
        // Accumulate YTD
        if (transRec1.transDate.substr(6,4) == year)     YTD -= stod(transRec1.amount);
        
        // Accumulate MTD
        if (transRec1.transDate.substr(3,7) ==month)     MTD -= stod(transRec1.amount);
      }
    }
    file1.close();
  }
  else
  {
    cout << "> Error!  Unable to open file";
  } 
  
  // Store month to be compared
  if(month.substr(0,2) == "01")          MTD_budget = stod(bdgtRec1.amount_01);
  else if(month.substr(0,2) == "02")     MTD_budget = stod(bdgtRec1.amount_02);
  else if(month.substr(0,2) == "03")     MTD_budget = stod(bdgtRec1.amount_03);
  else if(month.substr(0,2) == "04")     MTD_budget = stod(bdgtRec1.amount_04);
  else if(month.substr(0,2) == "05")     MTD_budget = stod(bdgtRec1.amount_05);
  else if(month.substr(0,2) == "06")     MTD_budget = stod(bdgtRec1.amount_06);
  else if(month.substr(0,2) == "07")     MTD_budget = stod(bdgtRec1.amount_07);
  else if(month.substr(0,2) == "08")     MTD_budget = stod(bdgtRec1.amount_08);
  else if(month.substr(0,2) == "09")     MTD_budget = stod(bdgtRec1.amount_09);
  else if(month.substr(0,2) == "10")     MTD_budget = stod(bdgtRec1.amount_10);
  else if(month.substr(0,2) == "11")     MTD_budget = stod(bdgtRec1.amount_11);
  else if(month.substr(0,2) == "12")     MTD_budget = stod(bdgtRec1.amount_12);
  
  // Compare and Display warning
  if (YTD > stod(bdgtRec1.amount))     // Check yearly total
  {
    // Write alert flag into budget record
    //bdgtRec1.alert = "Y";
    //bdgtRec1.alert = "*";
    
    if (showAlert == true)               // Show warning?
    {
      // Display warning
      cout << "\n\n" << endl;
      cout << "****************************************************************************************" << endl;
      cout << "*                                    !!! WARNING !!!                                   *" << endl;
      cout << "****************************************************************************************" << endl;
      cout << "*                       YEARLY total expense has exceeded budget.                      *" << endl;
      cout << "*                       Affected year: " << year << "                                            *" << endl;
      cout << "*                       Account code: " << bdgtRec1.acctCode << "                                             *" << endl;
      cout << "*                       Transaction Amount: " << transRec1.amount << "                                 *" << endl;
      cout << "*                       Budget Amount: " << bdgtRec1.amount << "                                       *" << endl;
      cout << "****************************************************************************************" << endl;
    }
  }
  
  else if (MTD > MTD_budget)     // Check monthly total
  {
    // Write alert flag into budget record
    //bdgtRec1.alert = "Y";
    //bdgtRec1.alert = "*";
    
    if (showAlert == true)               // Show warning?
    {
      // Display warning
      cout << "\n\n" << endl;
      cout << "****************************************************************************************" << endl;
      cout << "*                                    !!! WARNING !!!                                   *" << endl;
      cout << "****************************************************************************************" << endl;
      cout << "*                      MONTHLY total expense has exceeded budget.                      *" << endl;
      cout << "*                      Affected month: " << month << "                                         *" << endl;
      cout << "*                      Account code: " << bdgtRec1.acctCode << "                                              *" << endl;
      cout << "*                      Transaction Amount: " << transRec1.amount << "                                  *" << endl;
      cout << "*                      Budget Amount: " << bdgtRec1.amount << "                                        *" << endl;
      cout << "****************************************************************************************" << endl;
    }
  }
  
  
}

//-------------------------------------------------------------------------------------//
// Check if account code is in use
//-------------------------------------------------------------------------------------//
bool Transaction::IsUsed_AccountCode(string acctCode)
{
  string  dataRow;
  transRec1.initialize();
  transFldLen1.initialize();     // For AccountMaster.Delete_AccountMaster()
  
  try
  {
    ifstream file1 (filename_Transaction);
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
        split_DataRow_to_Fields(dataRow, transRec1);
        //
        // is any Account Code matched?
        if (transRec1.acctCode1==acctCode || 
            transRec1.acctCode2==acctCode)
        {
          file1.close();
          return true;
        }
      }
      transRec1.initialize();
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
void Transaction::add_Record(TransactionRecord transRec1)
{
  ofstream outfile;
  outfile.open(filename_Transaction, std::ios_base::app);
  
  transRec1.lineID = getNext_LineID();
  
  //----------
  // Pad all fields with space to get maxi. length before writting to file
  //----------
  transRec1.lineID     = utility1.padRight(transRec1.lineID,      ' ', transFldLen1.lineID);
  transRec1.transDate  = utility1.padRight(transRec1.transDate,   ' ', transFldLen1.transDate);
  transRec1.acctCode1  = utility1.padRight(transRec1.acctCode1,   ' ', transFldLen1.acctCode1);
  transRec1.acctCode2  = utility1.padRight(transRec1.acctCode2,   ' ', transFldLen1.acctCode2);
  transRec1.amount     = utility1.padLeft( transRec1.amount,      ' ', transFldLen1.amount);
  transRec1.refNbr     = utility1.padRight( transRec1.refNbr,     ' ', transFldLen1.refNbr);
  transRec1.transType  = utility1.padRight( transRec1.transType,  ' ', transFldLen1.transType);
  transRec1.transDesc  = utility1.padRight( transRec1.transDesc,  ' ', transFldLen1.transDesc);
  //
  transRec1._endSpace  = utility1.padRight(transRec1._endSpace,   ' ', transFldLen1._endSpace); 
  //
  outfile << transRec1.lineID
          << transRec1.transDate
		      << transRec1.acctCode1
		      << transRec1.acctCode2
		      << transRec1.amount
		      << transRec1.refNbr
		      << transRec1.transType
		      << transRec1.transDesc
          << transRec1._endSpace
          << "\n";
  //
  outfile.close();
}

//-------------------------------------------------------------------------------------//
// UPDATE Record
//-------------------------------------------------------------------------------------//
void Transaction::change_Record(TransactionRecord transRec1)
{
  string  dataRow;
  streampos lastPos;
  TransactionRecord transRec2;

  try
  {
    ifstream fileOld(filename_Transaction);
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
        split_DataRow_to_Fields(dataRow, transRec2);
        //
        // is the Transaction key  matched?
        if (transRec1.lineID!=transRec2.lineID)
        {
          // copy line to new file if not matched
          fileNew << dataRow << "\n";
        }
        else
        {
          //----------
          // Transaction record found, write new changed record
          //----------
          // Pad all fields with space to get maxi. length before writting to file
          transRec1.lineID     = utility1.padRight(transRec1.lineID,      ' ', transFldLen1.lineID);
    		  transRec1.transDate  = utility1.padRight(transRec1.transDate,   ' ', transFldLen1.transDate);
    		  transRec1.acctCode1  = utility1.padRight(transRec1.acctCode1,   ' ', transFldLen1.acctCode1);
    		  transRec1.acctCode2  = utility1.padRight(transRec1.acctCode2,   ' ', transFldLen1.acctCode2);
    		  transRec1.amount     = utility1.padLeft( transRec1.amount,      ' ', transFldLen1.amount);
    		  transRec1.refNbr     = utility1.padRight( transRec1.refNbr,     ' ', transFldLen1.refNbr);
    		  transRec1.transType  = utility1.padRight( transRec1.transType,  ' ', transFldLen1.transType);
    		  transRec1.transDesc  = utility1.padRight( transRec1.transDesc,  ' ', transFldLen1.transDesc);
      	  //
      	  transRec1._endSpace  = utility1.padRight(transRec1._endSpace,   ' ', transFldLen1._endSpace); 
          //
          fileNew << transRec1.lineID
        				  << transRec1.transDate
        				  << transRec1.acctCode1
        				  << transRec1.acctCode2
        				  << transRec1.amount
        				  << transRec1.refNbr
        				  << transRec1.transType
        				  << transRec1.transDesc
        				  << transRec1._endSpace
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
    remove(filename_Transaction.c_str());
    // rename old to new
    rename(filename_TempOutput.c_str(), filename_Transaction.c_str());

  }
  catch (int e)
  {
    // exception handling at here
  }
}

//-------------------------------------------------------------------------------------//
// DELETE Record
//-------------------------------------------------------------------------------------//
void Transaction::delete_Record(TransactionRecord transRec1)
{
  string  dataRow;
  streampos lastPos;
  TransactionRecord transRec2;

  try
  {
    ifstream fileOld(filename_Transaction);
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
        split_DataRow_to_Fields(dataRow, transRec2);
        //
        // is the Transaction key  matched?
        if (transRec1.lineID==transRec2.lineID)
        {
          // write nothing if matched
        }
        else
        {
          fileNew << dataRow << "\n";
        }
      }
      fileNew.close();
      fileOld.close();
    }    

    //----------
    // rename file
    //----------
    // delete the original file
    remove(filename_Transaction.c_str());
    // rename old to new
    rename(filename_TempOutput.c_str(), filename_Transaction.c_str());

  }
  catch (int e)
  {
    // exception handling at here
  }
}

//-------------------------------------------------------------------------------------//
// Get Transaction Record to Column Values 
//-------------------------------------------------------------------------------------//
bool Transaction::getRec_by_TransactionLineID(string lineID, TransactionRecord& transRec1)
{
  string  dataRow;
  
  try
  {
    ifstream file1 (filename_Transaction);
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
        split_DataRow_to_Fields(dataRow, transRec1);
        //
        // is the primary key matched?
        if (transRec1.lineID==lineID)
        {
          file1.close();
          return true;
        }
      }
      transRec1.initialize();
      file1.close();
    }    

    //----------
    // initialize with spaces
    //----------
    split_DataRow_to_Fields("     ", transRec1);        // fill-up with spaces  (fixed length)
    return false;
  }
  catch (int e)
  {
      // exception handling at here
  }
}

//-------------------------------------------------------------------------------------//
// Get the next available Line ID  
//-------------------------------------------------------------------------------------//
string Transaction::getNext_LineID()
{
  string  last_LineID = getLast_LineID();
  string  next_LineID = utility1.padLeft(to_string(stoi(last_LineID) + 1), '0', transFldLen1.lineID);
  return next_LineID;
}

//-------------------------------------------------------------------------------------//
// Get the latest assigned Line ID  
//-------------------------------------------------------------------------------------//
string Transaction::getLast_LineID()
{
  string  last_LineID = utility1.padLeft("", '0', transFldLen1.lineID);
  string  dataRow;
  transRec1.initialize();


  try
  {
    ifstream file1 (filename_Transaction);
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
        split_DataRow_to_Fields(dataRow, transRec1);
        //
        // Account code found
        if (last_LineID=="" ||
		    transRec1.lineID>last_LineID)
        {
        	last_LineID = transRec1.lineID;
        }
      }
      file1.close();
      return last_LineID;
    }    
    // not found
    return last_LineID;
  }
  catch (int e)
  {
    // exception handling at here
  }
}

