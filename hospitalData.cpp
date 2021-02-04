#include "hospitalData.h"
#include <sstream>


/* print hospital data partial - you must fill in*/
std::ostream& operator<<(std::ostream &out, const hospitalData &HD) {
    
    out << "Hosptial Info: " << HD.name << ", " << HD.state;
    out << "\nType: " << HD.type;
    out << "\nOverall rating (out of 5): " << HD.overallrate;
    out << "\nmortality rating: " << HD.mortality.getRating();
    out << "\nreadmission rating:" << HD.readmit.getRating();
    
    //out << HD.name << ", " << HD.type << ", " <<  HD.overallrate << ", " <<  HD.mortality << ", " <<  HD.readmit;
    return out;
}
