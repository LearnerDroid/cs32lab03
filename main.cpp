#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include "dataAQ.h"
#include "demogData.h"
#include "stateDemog.h"
#include "hospitalData.h"
#include "stateHosp.h"
#include "parse.h"

using namespace std;

int main() {

	dataAQ theAnswers;

    //read in a csv file and create a vector of objects representing each counties data
    std::vector<shared_ptr<demogData>> theDemogData = read_csv(
            "county_demographics.csv", DEMOG);

    //read in a csv file and create a vector of objects representing each counties data
    std::vector<shared_ptr<hospitalData>> theHospitalData = read_csvHospital(
            "hospitals.csv", HOSPITAL);

    /* For debugging print out what is read  - only AL for debug only*/
    for (auto elem : theDemogData) {
        if (elem->getName().compare("AL"))
            cout << *elem << endl;
    }
    for (auto hosp : theHospitalData) {
        if (hosp->getName().compare("AL"))
            cout << *hosp << endl;
    }

    //create state level data


    //print out the requested data

    return 0;
}

