//-----------------------------------------------------------------------
// Description : Accounting System - Transaction (Header file) 
// Last Modified: 2019-04-26
//
//-----------------------------------------------------------------------
// 
//-----------------------------------------------------------------------
#ifndef TRANSACTION_H
#define TRANSACTION_H

// DO NOT USE in header file --> "using namespace std;"



class Transaction
{
  public:
    const std::string filename_Transaction = ".\\data\\file_Transaction.txt";
    const std::string filename_TempOutput  = ".\\data\\file_Transaction.tmp";
    
    struct TransactionRecord     // Struct used for storing records extracted from .txt file or strong new record enterd
    {
      std::string lineID;        // Transaction Record Number (also the line number in the .txt file)
      std::string transDate;     // Date of Transaction
      std::string acctCode1;     // Account (Debit)
      std::string acctCode2;     // Account (Credit)
      std::string amount;        // Transaction Amount
      std::string refNbr;        // Reference Number of the Record
      std::string transType;     // Type of Transaction
      std::string transDesc;     // Description
      std::string _endSpace;     // ending buffer for 'add_Record()' only (size = 100 - total_length)
      
      initialize()
      {
        lineID    = "";
        transDate = "";
        acctCode1 = "";
        acctCode2 = "";
        amount    = "";
        refNbr    = "";
        transType = "";
        transDesc = "";
        _endSpace = "  ";
      };
    };
    
    struct TransactionFldChg     // Struct used for showing changed record field (showing a '*' for edited records in Change_Transaction)
    {
      char lineID;
  	  char transDate;
  	  char acctCode1;     // Account (Debit)
  	  char acctCode2;     // Account (Credit)
  	  char amount;
  	  char refNbr;
  	  char transType;
  	  char transDesc;
	  
	  initialize()
	  {
	    lineID    = ' ';
  		transDate = ' ';
  		acctCode1 = ' ';
  		acctCode2 = ' ';
  		amount    = ' ';
  		refNbr    = ' ';
  		transType = ' ';
  		transDesc = ' ';
  	  };
    };
    
    struct TransactionFldLen     // Struct for setting field lengths of record fields
    {
      int lineID;
  	  int transDate;
  	  int acctCode1;     // Account (Debit)
  	  int acctCode2;     // Account (Credit)
  	  int amount;
  	  int refNbr;
  	  int transType;
  	  int transDesc;
  	  int _endSpace;
  	  int _numOfFields;
      int _val[8];
      int _totalLength;
	  
	  initialize()
	  {
	    lineID    = 6;
  		transDate = 10;
  		acctCode1 = 4;
  		acctCode2 = 4;
  		amount    = 10;
  		refNbr    = 15;
  		transType = 15;     // No pre-defined values to match, transaction type can be anything else
  		transDesc = 30;
  		_endSpace = ' ';
  		
  		_numOfFields = 8;
  		//
      // also put to array for iterating process (loop)
  		_val[0] = lineID;
  		_val[1] = transDate;
  		_val[2] = acctCode1;
  		_val[3] = acctCode2;
  		_val[4] = amount;
  		_val[5] = refNbr;
  		_val[6] = transType;
  		_val[7] = transDesc;
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
    // Display budget master sub-menu, let user select functions listed
    void Menu();
    
    // Let user enter a new record, store the new record
    void Add_Transaction();
    
    // Let user view a list of records, select a record and change it, store the changes
    void Change_Transaction();
    
    // Let user view a list of records, select a record and delete it
    void Delete_Transaction();
    
    // Let user search for a record from a list of records, display the record's detail for user to review
    void Search_Transaction(bool showDetail, bool Loop);
    
    // Display the transaction record corresponding to the date of budget and account code specified
    void Display_Transaction(std::string lineID);
    
    // Generalized version of List_Records (call List_Records with default filterType and filterValue)
    void List_Records(bool showDetail);
    
    // Display all available records in list form, with different levels of detail and sorting order according to the requirements stated by the calling statement (the values set for filterValue showDetail)
    void List_Records(std::string filterType, std::string filterValue, bool showDetail);
    
    // Split a data row from the .txt file into values of the record
    bool split_DataRow_to_Fields(std::string DataRow, TransactionRecord& transRec1);
    
    // Display over-budget warning message when 
    void Alert_Budget(std::string acctCode, std::string date1, bool showAlert);
    
    // Check if the account code specified is already in use by a transaction record
    bool IsUsed_AccountCode(std::string acctCode);


  private:
    // add a new record (copy original data + new record into new file, overwrite original file)
    void add_Record(TransactionRecord transRec1);
    
    // select a record and make changes to it (copy original data into new file, replace chosen record with new values, overwrite original file)
    void change_Record(TransactionRecord transRec1);
    
    // remove a record from .txt file (copy original data into new file, skip the chosen record, overwrite original file)
    void delete_Record(TransactionRecord transRec1);
    
    // Get a transaction record from the lineID provided
    bool getRec_by_TransactionLineID(std::string lineID, TransactionRecord& transRec1);
    
    // Get the next available transaction ID in the .txt file
    std::string getLast_LineID();
    
    // Get the last transaction ID in the .txt file
    std::string getNext_LineID();
    
};
#endif

