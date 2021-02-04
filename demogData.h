#ifndef DEMOG_H
#define DEMOG_H

#include <string>
#include <iostream>

using namespace std;

/*
  class to represent county demographic data
  from CORGIS
*/
class demogData {
  public:
    demogData(string inN, string inS, double in65, double in18,
        double in5, double tPop) :
            name(inN), state(inS), popOver65(in65), popUnder18(in18),
            popUnder5(in5), percentUndergraduate(-1), percentHighSchool(-1), totalPop(tPop), belowPoverty(0) {
    } 

    demogData(string inN, string inS, double in65, double in18,
        double in5, double percU, double percH, double tPop, double bp) :
            name(inN), state(inS), popOver65(in65), popUnder18(in18),
            popUnder5(in5), percentUndergraduate(percU), percentHighSchool(percH), totalPop(tPop), belowPoverty(bp) {
    }    

    string getName() { return name; }

    double getBAup() { return percentUndergraduate; }

    double getHSup() { return percentHighSchool; }

    string getState() { return state; }

    double getpopOver65() { return popOver65; }

    double getpopUnder18() { return popUnder18; }

    double getpopUnder5() { return popUnder5; }

    double getTotalPop() { return totalPop; }

    double getBelowPoverty() { return belowPoverty; }

   friend std::ostream& operator<<(std::ostream &out, const demogData &DD);

private:
    const string name;
    const string state;
    const double popOver65;
    const double popUnder18;
    const double popUnder5;
    const double percentUndergraduate;
    const double percentHighSchool;
    const double totalPop;
    const double belowPoverty;
};
#endif
