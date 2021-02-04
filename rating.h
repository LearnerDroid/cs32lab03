#ifndef RATING_H
#define RATING_H

#include <string>
#include <iostream>

using namespace std;

/* 
A class to represent a rating system that uses both words and numbers
(see CORGIS hospital data for an example)
Rating.Overall  Integer     Overall rating between 1 and 5 stars, with 5 stars being the highest rating; -1 represents no rating.
Rating.Mortality    String  Above, Same, Below, or Unknown comparison to national hospital mortality
Rating.Safety   String  Above, Same, Below, or Unknown comparison to national hospital safety 
*/
class rating {
  public:
    rating() : inR(-1) {}
    rating(double inRating) : inR(inRating) {
        update(inRating);
    }
    /*
    n < “below” <= n+0.5
    n+.5 < “same” <= n+1.5
    n+1.5 < “above” <= n+2.5
    */
    rating(string inRating) : inRS(inRating) { 
        update(inRating);
    }

    const string getRating() const { return inRS; }
    double getRatingNum() const { return inR; }

    friend std::ostream& operator<<(std::ostream &out, const rating &r) {
        out << r.inR;
        return out;
    }

    rating& operator/=(const double Sc) {
        inR /= Sc;
        return *this;
    }

    /* implement other operators for example, maybe... */
    rating& operator/(const int Sc) {
        inR /= Sc;
        return *this;
    }

    rating& operator+=(const rating r) {
        inR += r.inR;
        return *this;
    }
    
    bool operator < (const rating& r) {
        return this->getRatingNum() < r.getRatingNum();
    }
    
    void update(string inRating){
        if (inRating.compare("Below") == 0)
            inR = 0;
        else if (inRating.compare("Same") == 0)
            inR = 1;
        else if (inRating.compare("Above") == 0)
            inR = 2;
        else
            inR = -1; //last option is undefined
    }

    void update(double inRating){
        if (inRating == -1)
            inRS = "Unknown";
        else if (inRating > 0 && inRating <= 0.5)
            inRS = "Below";
        else if (inRating > 0.5 && inRating <= 1.5)
            inRS = "Same";
        else
            inRS = "Above";
    }
private:
    double inR;
    string inRS; //string version of rating
};
#endif
