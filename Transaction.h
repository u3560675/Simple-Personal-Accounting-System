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
    
    struct TransactionRecord
    {
      std::string lineID;
      std::string transDate;
      std::string acctCode1;     // Account (Debit)
      std::string acctCode2;     // Account (Credit)
      std::string amount;
      std::string refNbr;
      std::string transType;
      std::string transDesc;
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
    
    struct TransactionFldChg
    {
      char lineID;
  	  char transDate;
  	  char acctCode1;
  	  char acctCode2;
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
    
    struct TransactionFldLen
    {
      int lineID;
  	  int transDate;
  	  int acctCode1;
  	  int acctCode2;
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
  		transType = 15;
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
    void Menu();
    void Add_Transaction();
    void Change_Transaction();
    void Delete_Transaction();
    void Search_Transaction(bool showDetail, bool Loop);
    void Display_Transaction(std::string lineID);
    void List_Records(bool showDetail);
    void List_Records(std::string filterType, std::string filterValue, bool showDetail);
    bool split_DataRow_to_Fields(std::string DataRow, TransactionRecord& transRec1);
    void Alert_Budget(std::string acctCode, std::string date1, bool showAlert);
    bool IsUsed_AccountCode(std::string acctCode);


  private:
    void add_Record(TransactionRecord transRec1);
    void change_Record(TransactionRecord transRec1);
    void delete_Record(TransactionRecord transRec1);
    bool getRec_by_TransactionLineID(std::string lineID, TransactionRecord& transRec1);
    std::string getLast_LineID();
    std::string getNext_LineID();
    
};
#endif

