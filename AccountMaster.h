//-----------------------------------------------------------------------
// Description : Accounting System - Account Code (Header file) 
// Last Modified: 2019-04-26
//
//-----------------------------------------------------------------------
// 
//-----------------------------------------------------------------------
#ifndef ACCOUNTMASTER_H
#define ACCOUNTMASTER_H

// DO NOT USE in header file --> "using namespace std;"



class AccountMaster
{
  public:
    const std::string filename_AccountMaster = ".\\data\\file_AccountMaster.txt";
    const std::string filename_TempOutput    = ".\\data\\file_AccountMaster.tmp";
    
    struct AccountMasterRecord
    {
        std::string acctCode;
        std::string acctDesc;
        std::string acctType;
        std::string Taxable;
        std::string _endSpace;     // ending buffer for 'add_Record()' only (size = 100 - total_length)
        
        initialize() 
        { 
            acctCode  = "";
            acctDesc  = "";
            acctType  = "";
            Taxable   = "";
            _endSpace = "                ";
        };
    };        
    
    struct AccountMasterFldChg
    {
        char acctCode;
        char acctDesc;
        char acctType;
        char Taxable;
        
        initialize() 
        { 
            acctCode = ' ';
            acctDesc = ' ';
            acctType = ' ';
            Taxable  = ' ';
        };
    };        
    
    struct AccountMasterFldLen
    {
        int acctCode;
        int acctDesc;
        int acctType;
        int Taxable;
        int _endSpace;         // ending buffer for 'add_Record()' only (size = 100 - total_length)
        int _numOfFields;
        int _val[9];
        int _totalLength;
        
        initialize() 
        { 
            acctCode  =  4;
            acctDesc  = 30;
            acctType  = 1;
            Taxable   = 1;
            //
            _numOfFields = 9;
            //
            // also put to array for iterating process (loop)
            _val[0] = acctCode;           
            _val[1] = acctDesc;
            _val[2] = acctType;
            _val[3] = Taxable;
            //
            _totalLength = 0;
            for (int i=0; i<_numOfFields; i++)
            {
                _totalLength += _val[i];
            }
            _endSpace  = 100 - _totalLength;
        };
    };        
      
      
  public:
    void Menu();    	
    void Add_AccountMaster();
    void Change_AccountMaster();
    void Delete_AccountMaster();
    void Display_AccountMaster(std::string accountCode);
    void List_Records(bool showDetail);
    void List_Records(std::string filterType, std::string filterValue, bool showDetail);
    void Search_AccountMaster();
    bool getRec_by_AccountMasterKey(std::string accountCode, AccountMasterRecord& acctRec1);
    bool split_DataRow_to_Fields(std::string DataRow, AccountMasterRecord& acctRec1);
    bool isValid_AccountMasterKey2(std::string accountCode);


  private:
    void add_Record(AccountMasterRecord acctRec1);
    void change_Record(AccountMasterRecord acctRec1);
    void delete_Record(std::string accountCode);
    bool isValid_AccountMasterKey(std::string accountCode);
        
 };
#endif 

