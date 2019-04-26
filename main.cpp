//-----------------------------------------------------------------------
// Description : Accounting System - Main Menu
// Last Modified: 2019-04-20
//
//-----------------------------------------------------------------------
// 
//-----------------------------------------------------------------------

#include <iostream>
#include <string>
#include <bits/stdc++.h> 
#include "AccountMaster.h"
#include "BudgetMaster.h"
#include "Report.h"
#include "Transaction.h"
#include "Utility.h"


using namespace std;


//*********************************************************************************************//
int main(void)
{
    char selection;
    AccountMaster accountMaster1;
    BudgetMaster budgetMaster1;
    Transaction Transaction1;
    Report Report1;
    Utility utility1;

    //-------------------
    // Loop: Display menu and selection option 
    //-------------------
    while (true)
    {
        // Display menu
        system("cls");
        cout << "|-------------------------------------------------------------------------|" << endl;
        cout << "|                      ACCOUNTING SYSTEM - MAIN MENU                      |" << endl;
        cout << "|-------------------------------------------------------------------------|" << endl;
        cout << "|***           Welcome to HKU Simple Accounting System (2019)          ***|" << endl;
        cout << "|***  This system is developed by ENGG1340 Class No.XXXXX Group No.XX  ***|" << endl;
        cout << "|-------------------------------------------------------------------------|" << endl;
        cout << "|                                                                         |" << endl;
        cout << "|  Options:                                                               |" << endl;
        cout << "|    1. Daily Incomes/Expenses Transactions                               |" << endl;
        cout << "|    2. Maintain Account Code Records                                     |" << endl;
        cout << "|    3. Maintain Budget Setting Record                                    |" << endl;
        cout << "|    4. Statistical Reports                                               |" << endl;
        cout << "|    5. Backup Tables                                                     |" << endl;
        cout << "|                                                                         |" << endl;
        cout << "|    X. Exit                                                              |" << endl;
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
                Transaction1.Menu();
                continue;
            case '2' :
                cout.flush();
                cin.ignore();
                accountMaster1.Menu();
                continue;
            case '3' :
                cout.flush();
                cin.ignore();
                budgetMaster1.Menu();
                continue;
            case '4' :
                cout.flush();
                cin.ignore();
                Report1.Menu();
                continue;
            case '5' :
                cout.flush();
                cin.ignore();
                utility1.Backup_Files();
                continue;
            case 'X' :
            case 'x' :
                cout << "\nExit...\n";
                return 0;
            default : 
                cout << "\n>> Invalid selection.  Please retry.";
                continue;
                // no break in the default case
        }
    }
     
    return 0;
}

