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
    
    struct AccountMasterRecord     // Struct used for storing records extracted from .txt file or strong new record enterd
    {
        std::string acctCode;      // Account code
        std::string acctDesc;      // Account description
        std::string acctType;      // Account type
        std::string Taxable;       // Value to indicate whether account is taxable
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
    
    struct AccountMasterFldChg     // Struct used for showing changed record field (showing a '*' for edited records in Change_AccountMaster)
    {
        char acctCode;
        char acctDesc;
        char acctType;
        char Taxable;
        
        initialize()     // When a field is changed, ' ' is changed to a '*'
        { 
            acctCode = ' ';
            acctDesc = ' ';
            acctType = ' ';
            Taxable  = ' ';
        };
    };        
    
    struct AccountMasterFldLen     // Struct for setting field lengths of record fields
    {
        int acctCode;
        int acctDesc;
        int acctType;
        int Taxable;
        int _endSpace;        // ending buffer for 'add_Record()' only (size = 100 - total_length)
        int _numOfFields;
        int _val[9];
        int _totalLength;     // total length of all 4 record field strings combined
        
        initialize() 
        { 
            acctCode  =  4;
            acctDesc  = 30;
            acctType  = 1;     // Value can be I/E, only 1 character, so length set to 1
            Taxable   = 1;     // Value can be Y/N, only 1 character, so length set to 1
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
            _endSpace  = 100 - _totalLength;     // length of a line written into .txt file is always 100 characters, _totallength is always <= 100, use endspace to fill in remainder
        };
    };        
      
      
  public:
    // Display account master sub-menu, let user select functions listed
    void Menu();
    
    // Let user enter a new record, store the new record
    void Add_AccountMaster();
    
    // Let user view a list of records, select a record and change it, store the changes
    void Change_AccountMaster();
    
    // Let user view a list of records, select a record and delete it
    void Delete_AccountMaster();
    
    // Display details of the account record corresponding to the given account code
    void Display_AccountMaster(std::string accountCode);
    
    // Generalized version of List_Records (call List_Records with default filterType and filterValue)
    void List_Records(bool showDetail);
    
    // Display all available records in list form, with different levels of detail and sorting order according to the requirements stated by the calling statement
    void List_Records(std::string filterType, std::string filterValue, bool showDetail);
    
    // Let user search for a record from a list of records, display the record's detail for user to review
    void Search_AccountMaster();
    
    // Get an account record from the account code provided
    bool getRec_by_AccountMasterKey(std::string accountCode, AccountMasterRecord& acctRec1);
    
    // Split a data row from the .txt file into values of the record
    bool split_DataRow_to_Fields(std::string DataRow, AccountMasterRecord& acctRec1);
    
    // Public version of isValid_AccountMasterKey, for other functions outside class AccountMaster to call (structures are initialized before isValid_AccountMasterKey is executed)
    bool isValid_AccountMasterKey2(std::string accountCode);


  private:
    // add a new record (copy original data + new record into new file, overwrite original file)
    void add_Record(AccountMasterRecord acctRec1);
    
    // select a record and make changes to it (copy original data into new file, replace chosen record with new values, overwrite original file)
    void change_Record(AccountMasterRecord acctRec1);
    
    // remove a record from .txt file (copy original data into new file, skip the chosen record, overwrite original file)
    void delete_Record(std::string accountCode);
    
    // Check if account key is valid (whether the account record exists, as every record has its own account code), returns true / false
    bool isValid_AccountMasterKey(std::string accountCode);
        
 };
#endif 

