//-----------------------------------------------------------------------
// Description : Accounting System - Budget Code (Header file) 
// Last Modified: 2019-04-26
//
//-----------------------------------------------------------------------
// 
//-----------------------------------------------------------------------
#ifndef BUDGETMASTER_H
#define BUDGETMASTER_H

// DO NOT USE in header file --> "using namespace std;"



class BudgetMaster
{
  public:
    const std::string filename_BudgetMaster = ".\\data\\file_BudgetMaster.txt";
    const std::string filename_TempOutput   = ".\\data\\file_BudgetMaster.tmp";
    
    struct BudgetMasterRecord     // Struct used for storing records extracted from .txt file or strong new record enterd
    {
      std::string acctCode;     // Account code
      std::string year;         // Year
      std::string amount;       // Budget amount for the entire year
      std::string amount_01;    // Budget amount for January   (= amount / 12)
      std::string amount_02;    // Budget amount for February  (= amount / 12)
      std::string amount_03;    // Budget amount for March     (= amount / 12)
      std::string amount_04;    // Budget amount for April     (= amount / 12)
      std::string amount_05;    // Budget amount for May       (= amount / 12)
      std::string amount_06;    // Budget amount for June      (= amount / 12)
      std::string amount_07;    // Budget amount for July      (= amount / 12)
      std::string amount_08;    // Budget amount for August    (= amount / 12)
      std::string amount_09;    // Budget amount for September (= amount / 12)
      std::string amount_10;    // Budget amount for October   (= amount / 12)
      std::string amount_11;    // Budget amount for November  (= amount / 12)
      std::string amount_12;    // Budget amount for December  (= amount / 12)
      std::string alert;         // Value to indicate whether system should show over-budget warning message
      std::string _endSpace;     // ending buffer for 'add_Record()' only (size = 100 - total_length)
      
      initialize() 
      { 
        acctCode  = "";
        year      = "";
        amount    = "";
        amount_01 = "";
        amount_02 = "";
        amount_03 = "";
        amount_04 = "";
        amount_05 = "";
        amount_06 = "";
        amount_07 = "";
        amount_08 = "";
        amount_09 = "";
        amount_10 = "";
        amount_11 = "";
        amount_12 = "";
        alert     = "";
        _endSpace = "  ";
      };
    };        
    
    struct BudgetMasterFldChg     // Struct used for showing changed record field (showing a '*' for edited records in Change_BudgetMaster)
    {
      char acctCode;
      char year;
      char amount;
      char amount_01;
      char amount_02;
      char amount_03;
      char amount_04;
      char amount_05;
      char amount_06;
      char amount_07;
      char amount_08;
      char amount_09;
      char amount_10;
      char amount_11;
      char amount_12;
      char alert;
      
      initialize() 
      { 
        acctCode  = ' ';
        year  = ' ';
        amount  = ' ';
        amount_01  = ' ';
        amount_02  = ' ';
        amount_03  = ' ';
        amount_04  = ' ';
        amount_05  = ' ';
        amount_06  = ' ';
        amount_07  = ' ';
        amount_08  = ' ';
        amount_09  = ' ';
        amount_10  = ' ';
        amount_11  = ' ';
        amount_12  = ' ';
        alert = ' ';
      };
    };        
    
    struct BudgetMasterFldLen     // Struct for setting field lengths of record fields
    {
      int acctCode;
      int year;
      int amount;
      int amount_01;
      int amount_02;
      int amount_03;
      int amount_04;
      int amount_05;
      int amount_06;
      int amount_07;
      int amount_08;
      int amount_09;
      int amount_10;
      int amount_11;
      int amount_12;
      int alert;
      int _endSpace;        // ending buffer for 'add_Record()' only (size = 100 - total_length)
      int _numOfFields;     // Number of fields
      int _val[16];
      int _totalLength;     // total length of all 16 record field strings combined
      
      initialize() 
      { 
        acctCode  = 4;
        year      = 4;
        amount    = 9;
        amount_01 = 9;
        amount_02 = 9;
        amount_03 = 9;
        amount_04 = 9;
        amount_05 = 9;
        amount_06 = 9;
        amount_07 = 9;
        amount_08 = 9;
        amount_09 = 9;
        amount_10 = 9;
        amount_11 = 9;
        amount_12 = 9;
        alert = 1;         // Value can be Y/N, only 1 character, so length set to 1
        //
        _numOfFields = 16;
        //
        // also put to array for iterating process (loop)
        _val[0] = acctCode;           
        _val[1] = year;
        _val[2] = amount;
        _val[3] = amount_01;
        _val[4] = amount_02;
        _val[5] = amount_03;
        _val[6] = amount_04;
        _val[7] = amount_05;
        _val[8] = amount_06;
        _val[9] = amount_07;
        _val[10] = amount_08;
        _val[11] = amount_09;
        _val[12] = amount_10;
        _val[13] = amount_11;
        _val[14] = amount_12;
        _val[15] = alert;
        //
        _totalLength = 0;
        for (int i=0; i<_numOfFields; i++)
        {
          _totalLength += _val[i];
        }
        _endSpace  = 128 - _totalLength;
      };
    };        
      
      
  public:
    // Display budget master sub-menu, let user select functions listed
    void Menu();
    
    // Let user enter a new record, store the new record
    void Add_BudgetMaster();
    
    // Let user view a list of records, select a record and change it, store the changes
    void Change_BudgetMaster();
    
    // Let user view a list of records, select a record and delete it
    void Delete_BudgetMaster();
    
    // Let user search for a record from a list of records, display the record's detail for user to review
    void Search_BudgetMaster();
    
    // Display the budget record corresponding to the date of budget and account code specified
    void Display_BudgetMaster(std::string accountCode, std::string targetYear);
    
    // Generalized version of List_Records (call List_Records with default filterType and filterValue)
    void List_Records(bool showDetail);
    
    // Display all available records in list form, with different levels of detail and sorting order according to the requirements stated by the calling statement (the values set for filterValue showDetail)
    void List_Records(std::string filterType, std::string filterValue, bool showDetail);
    
    // Get an budget record from the account code and year provided
    bool getRec_by_BudgetMasterKey(std::string acctCode, std::string year, BudgetMasterRecord& bdgtRec1);
    
    // Split a data row from the .txt file into values of the record
    bool split_DataRow_to_Fields(std::string DataRow, BudgetMasterRecord& bdgtRec1);
    
    // Public version of isValid_BudgetMasterKey, for other functions outside class BudgetMaster to call (structures are initialized before isValid_BudgetMasterKey is executed)
    bool isValid_BudgetMasterKey2(std::string acctCode, std::string year);
    
    // Check if the account code specified is already in use by a budget master record
    bool IsUsed_AccountCode(std::string acctCode);


  private:
    // add a new record (copy original data + new record into new file, overwrite original file)
    void add_Record(BudgetMasterRecord bdgtRec1);
    
    // select a record and make changes to it (copy original data into new file, replace chosen record with new values, overwrite original file)
    void change_Record(BudgetMasterRecord bdgtRec1);
    
    // remove a record from .txt file (copy original data into new file, skip the chosen record, overwrite original file)
    void delete_Record(std::string acctCode, std::string year);
    
    // Check if budget key is valid (whether the budget record with the corresponding account code and date exists), returns true / false
    bool isValid_BudgetMasterKey(std::string acctCode, std::string year);
      
 };
#endif 

