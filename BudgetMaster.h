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
    
    struct BudgetMasterRecord
    {
      std::string acctCode;
      std::string year;
      std::string amount; 
      std::string amount_01;
      std::string amount_02;
      std::string amount_03;
      std::string amount_04;
      std::string amount_05;
      std::string amount_06;
      std::string amount_07;
      std::string amount_08;
      std::string amount_09;
      std::string amount_10;
      std::string amount_11;
      std::string amount_12;
      std::string alert;         // value to indicate whether system should show over-budget warning message
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
    
    struct BudgetMasterFldChg
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
    
    struct BudgetMasterFldLen
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
      int _endSpace;         // ending buffer for 'add_Record()' only (size = 100 - total_length)
      int _numOfFields;
      int _val[16];
      int _totalLength;
      
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
        alert = 1;
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
    void Menu();      
    void Add_BudgetMaster();
    void Change_BudgetMaster();
    void Delete_BudgetMaster();
    void Search_BudgetMaster();
    void Display_BudgetMaster(std::string accountCode, std::string targetYear);
    void List_Records(bool showDetail);
    void List_Records(std::string filterType, std::string filterValue, bool showDetail);
    bool getRec_by_BudgetMasterKey(std::string acctCode, std::string year, BudgetMasterRecord& bdgtRec1);
    bool split_DataRow_to_Fields(std::string DataRow, BudgetMasterRecord& bdgtRec1);
    bool isValid_BudgetMasterKey2(std::string acctCode, std::string year);
    bool IsUsed_AccountCode(std::string acctCode);


  private:
    void add_Record(BudgetMasterRecord bdgtRec1);
    void change_Record(BudgetMasterRecord bdgtRec1);
    void delete_Record(std::string acctCode, std::string year);
    bool isValid_AccountMasterKey(std::string accountCode);
    bool isValid_BudgetMasterKey(std::string acctCode, std::string year);
      
 };
#endif 

