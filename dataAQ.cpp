#include "dataAQ.h"
using namespace std;
//function to aggregate the data - this CAN and SHOULD vary per student - depends on how they map
void dataAQ::sortStateDemogPovLevelLowHigh(vector<stateDemog *> &incomeHighLow) {
    for(map<string, shared_ptr<stateDemog>>::iterator i = allStateDemogData.begin(); i != allStateDemogData.end(); i++ ){
        incomeHighLow.push_back(&(*i->second));
    }
    sort(incomeHighLow.begin(), incomeHighLow.end(), &stateDemog::compareP);
}

std::ostream& operator<<(std::ostream &out, const dataAQ &AQ) {
    out << "bruh";
    return out;
}
 