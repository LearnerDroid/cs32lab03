#ifndef HOSP_H
#define HOSP_H

#include <string>
#include <iostream>
#include <utility>
#include "rating.h"

using namespace std;

/*
  class to represent hospital data
  from CORGIS
*/
class hospitalData {
  public:
	 //constructor for starting code - make complete by adding rating
    hospitalData(string inN, string inS, string inType) :
            name(inN), state(inS), type(inType), overallrate(-1), mortality(-1), readmit(-1) {}
    hospitalData(string inN, string inS, string inType, int o, rating m, rating r) :
            name(inN), state(inS), type(inType), overallrate(o), mortality(m), readmit(r){
    }
    string getName() const { return name; }
    string getState() const { return state; }
    string getType() const { return type; }
    int getOverallRate() const { return overallrate; }
    rating getMortality() const { return mortality; }
    rating getReadmit() const { return readmit; }

   friend std::ostream& operator<<(std::ostream &out, const hospitalData &HD);

private:
    const string name;
    const string state;
    const string type;
    const int overallrate;
    const rating mortality;
    const rating readmit;

};

#endif
