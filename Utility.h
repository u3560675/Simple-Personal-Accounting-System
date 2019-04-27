//-----------------------------------------------------------------------
// Description : Accounting System - Utility  (Header file) 
// Last Modified: 2019-04-14
//
//-----------------------------------------------------------------------
// 
//-----------------------------------------------------------------------
#ifndef UTILITY_H
#define UTILITY_H

// DO NOT USE in header file --> "using namespace std;"

class Utility
 {
    public:
      std::string formatDouble(double value, int decimalPlace);
      
      std::string formatStringToDecimal(std::string source, int numOfDecimal);
      std::string getDateTime(std::string format);
      
      bool isFileEmpty(std::string fileName);     
      bool isNumber(std::string str1, bool haveSign, bool hasDecimal);
	    bool isValidDate(int dd, int mm, int yyyy);
	    bool isValidTime(int hh, int mm);
	    bool isLeapYear(int year);
      
      std::string padLeft(std::string str, char c, int len);
      std::string padRight(std::string str, char c, int len);
      
      std::string trim(std::string source);
      std::string trimLeft(std::string source);
      std::string trimRight(std::string source);
      
      std::string replaceLeft(std::string source, char fromChar, char toChar);
      std::string replaceRight(std::string source, char fromChar, char toChar);
      
      void Backup_Files();
      
 };
#endif 

