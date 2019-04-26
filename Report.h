//-----------------------------------------------------------------------
// Description : Accounting System - Transaction (Header file) 
// Last Modified: 2019-04-20
//
//-----------------------------------------------------------------------
// 
//-----------------------------------------------------------------------
#ifndef REPORT_H
#define REPORT_H

// DO NOT USE in header file --> "using namespace std;"



class Report
{
  public:
    void Menu();
    void MonthStat_Report(std::string accountType);
    void MonthTrans_Report();
    void BdgtCtrl_Report(std::string accountType);
    double get_accountTotal(std::string accountCode, std::string monthYear);
};

#endif
