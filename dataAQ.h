#ifndef DATAAQ_H
#define DATAAQ_H

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "stateDemog.h"
#include "stateHosp.h"
#include <memory>
#include <algorithm>

using namespace std;
class dataAQ {
  public:
    dataAQ() {

    }
    void createStateDemogData(std::vector< shared_ptr<demogData> > theData){
      string state = "";
      for( shared_ptr<demogData> county: theData) {
        state = county->getState();
        //if true, key is not found
        if(allStateDemogData.count(state) == 0){
          allStateDemogData.insert(make_pair(state, make_shared<stateDemog>(state)));
        }
        allStateDemogData.at(state)->addCounty(county);
      }
      //now to calculate all the values with the inputted data
      for(map<string, shared_ptr<stateDemog>>::iterator i = allStateDemogData.begin(); i != allStateDemogData.end(); ++i ){
        i->second->calculate();
      }
    }
    
    void createStateHospData(std::vector<shared_ptr<hospitalData> > theData) {
      string state = "";
      for( shared_ptr<hospitalData> hosp: theData) {
        state = hosp->getState();
        //if true, key is not found
        if(allStateHospData.count(state) == 0){
          allStateHospData.insert(make_pair(state, make_shared<stateHosp>(state)));
        }
        allStateHospData.at(state)->addHosp(hosp);
      }
      for(map<string, shared_ptr<stateHosp>>::iterator i = allStateHospData.begin(); i != allStateHospData.end(); ++i ){
        i->second->calculate();
      }
    }
    
    //return the name of the state with the largest PROPORTION population under age 5, answer is UT
    string youngestPop() {
      string state = "";
      double largestPop = 0;
      double pop = 0;
      for(map<string, shared_ptr<stateDemog>>::iterator i = allStateDemogData.begin(); i != allStateDemogData.end(); i++ ){
        pop = i->second->getpopUnder5();
        //cout << i->second->getName() << "       " << pop << endl;
        if(pop > largestPop){
          //cout << i->second->getName() << endl;
          largestPop = pop;
          state = i->first;
        }
        /*
        if((i->first).compare("UT") == 0){
          cout << i->second->getName() << " " << (i->second->getpopUnder5() / i->second->getTotalPop()) 
            << " " << i->second->getBAup() << endl;
        }
        */
      }
      return state;
    }
    //return the name of the state with the largest population under age 18
    string teenPop() {
      string state = "";
      double largestPop = 0;
      double pop = 0;
      for(map<string, shared_ptr<stateDemog>>::iterator i = allStateDemogData.begin(); i != allStateDemogData.end(); i++ ){
        pop = i->second->getpopUnder18();
        if(pop > largestPop){
          //cout << i->second->getName() << "       " << pop << endl;
          largestPop = pop;
          state = i->first;
        }
      }
      return state;
    }
    //return the name of the state with the largest population over age 65
    string wisePop() {
      string state = "";
      double largestPop = 0;
      double pop = 0;
      for(map<string, shared_ptr<stateDemog>>::iterator i = allStateDemogData.begin(); i != allStateDemogData.end(); i++ ){
        pop = i->second->getpopOver65();
        //cout << i->second->getName() << "       " << pop << endl;
        if(pop > largestPop){
          //cout << i->second->getName() << endl;
          largestPop = pop;
          state = i->first;
        }
      }
      return state;
    }
    //return the name of the state with the largest population who did not finish high school
    string underServeHS() {
      string state = "";
      double largestPop = 0;
      double pop = 0;
      for(map<string, shared_ptr<stateDemog>>::iterator i = allStateDemogData.begin(); i != allStateDemogData.end(); i++ ){
        pop = 100 - i->second->getHSup();
        //cout << i->second->getName() << "       " << pop << endl;
        if(pop > largestPop){
          //cout << i->second->getName() << "   inside     " << pop << endl;
          largestPop = pop;
          state = i->first;
        }
      }
      return state;
    }
    //return the name of the state with the largest population who completed college, answer is DC
    string collegeGrads() {
      string state = "";
      double largestPop = 0;
      double pop = 0;
      for(map<string, shared_ptr<stateDemog>>::iterator i = allStateDemogData.begin(); i != allStateDemogData.end(); i++ ){
        pop = i->second->getBAup();
        //cout << i->second->getName() << "       " << pop << endl;
        if(pop > largestPop){
          //cout << i->second->getName() << "   inside     " << pop << endl;
          largestPop = pop;
          state = i->first;
          //cout << state << " " << largestPop << endl;
        }
        /*
        if((i->first).compare("DC") == 0){
          cout << i->second->getName() << " " << (i->second->getpopUnder5() / i->second->getTotalPop()) 
            << " " << i->second->getBAup() << endl;
        }
        */
      }
      //cout << "Test Failed: 'Testing state data aggregation query...\nPASSED: youngestPop\nPASSED: bachelors\nPASSED: teenPop\nPASSED: wisePop\nPASSED: underServeHS' != 'Testing state data aggregation query...\n   FAILED: youngestPop\n     Expected: UT Actual: SD\nPASSED: bachelors\n   FAILED: teenPop\n     Expected: UT Actual: SD\n   FAILED: wisePop\n     Expected: FL Actual: SD\n   FAILED: underServeHS\n     Expected: CA Actual:" << endl;
      return state;
    }
    string LowHospRating() {
      /*
      string state = "";
      double lowestR = 1000000;
      double r = 0;
      for(map<string, shared_ptr<stateHosp>>::iterator i = allStateHospData.begin(); i != allStateHospData.end(); i++ ){
        r = i->second->getAvgRate();
        //cout << i->second->getName() << "       " << r << endl;
        if(r < lowestR){
          //cout << i->second->getName() << "   inside     " << r << endl;
          lowestR = r;
          state = i->first;
          //cout << state << " " << largestPop << endl;
        }
      }
      return state;
      */
     pair<string, shared_ptr<stateHosp>> min = *min_element(allStateHospData.begin(), allStateHospData.end(), &stateHosp::compareO);
     return min.second->getState();
    }
    string HighHospRating(){ 
      /*
      string state = "";
      double highestR = 0;
      double r = 0;
      for(map<string, shared_ptr<stateHosp>>::iterator i = allStateHospData.begin(); i != allStateHospData.end(); i++ ){
        r = i->second->getAvgRate();
        //cout << i->second->getName() << "       " << r << endl;
        if(r > highestR){
          //cout << i->second->getName() << "   inside     " << r << endl;
          highestR = r;
          state = i->first;
          //cout << state << " " << largestPop << endl;
        }
      }
      return state;
      */
     pair<string, shared_ptr<stateHosp>> max = *max_element(allStateHospData.begin(), allStateHospData.end(), &stateHosp::compareO);
     return max.second->getState();
    }
    string HighMortHospRating(){ 
      /*
      string state = "";
      double highestR = 0;
      double r = 0;
      for(map<string, shared_ptr<stateHosp>>::iterator i = allStateHospData.begin(); i != allStateHospData.end(); i++ ){
        r = i->second->getMortality().getRatingNum();
        //cout << i->second->getName() << "       " << r << endl;
        if(r > highestR){
          //cout << i->second->getName() << "   inside     " << r << endl;
          highestR = r;
          state = i->first;
          //cout << state << " " << largestPop << endl;
        }
      }
      return state;
      */
     pair<string, shared_ptr<stateHosp>> max = *max_element(allStateHospData.begin(), allStateHospData.end(), &stateHosp::compareM);
     return max.second->getState();
    }
    string HighReadmitHospRating(){
      /*
      string state = "";
      double highestR = 0;
      double r = 0;
      for(map<string, shared_ptr<stateHosp>>::iterator i = allStateHospData.begin(); i != allStateHospData.end(); i++ ){
        r = i->second->getReadmit().getRatingNum();
        //cout << i->second->getState() << "       " << r << endl;
        if(r > highestR){
          //cout << i->second->getName() << "   inside     " << r << endl;
          highestR = r;
          state = i->first;
          //cout << state << " " << largestPop << endl;
        }
      }
      */
      pair<string, shared_ptr<stateHosp>> max = *max_element(allStateHospData.begin(), allStateHospData.end(), &stateHosp::compareR);
      return max.second->getState();
    }
    /*
    void sortStateHospRatingHighLow(vector<stateHosp*> vec){
        int sortedPos = 0;
        int hPos = 0;
        double hRating = 0;
        stateHosp *h = NULL;
        for(int i = 0; i < vec.size(); i++) {
          for(int j = sortedPos; j < vec.size(); j++){
            h = vec.at(j);
            if(h->getAvgRate() > hRating){
              hRating = h->getAvgRate();
              hPos = j;
            }
          }
          //select/move. Normal selection sort would just remove then insert, not swap.
          swap(vec.at(sortedPos), vec.at(hPos));
          //update variables
          sortedPos++;
          hRating = 0;
          hPos = sortedPos;
        }
    }
    */
    void sortStateHospRatingHighLow(vector<stateHosp *> &hospHighToLow) { 
        //adding elements from the hashmap to the vector
        for(map<string, shared_ptr<stateHosp>>::iterator i = allStateHospData.begin(); i != allStateHospData.end(); i++ ){
            hospHighToLow.push_back(&(*i->second));
        }
        /*
        vector<stateHosp *> vec = hospHighToLow;
        int sortedPos = 0;
        int hPos = 0;
        double hRating = 0;
        stateHosp *h = NULL;
        for(int i = 0; i < vec.size(); i++) {
          for(int j = sortedPos; j < vec.size(); j++){
            h = vec.at(j);
            if(h->getAvgRate() > hRating){
              hRating = h->getAvgRate();
              hPos = j;
            }
          }
          //select/move. Normal selection sort would just remove then insert, not swap.
          swap(vec.at(sortedPos), vec.at(hPos));
          //update variables
          sortedPos++;
          hRating = 0;
          hPos = sortedPos;
        }
        hospHighToLow = vec;
        */
        sort(hospHighToLow.begin(), hospHighToLow.end(), &stateHosp::compareOV);
        //reverse
        reverse(hospHighToLow.begin(), hospHighToLow.end());
    }
    void sortStateHospRatingLowHigh(vector<stateHosp *> &hospLowToHigh) {
        for(map<string, shared_ptr<stateHosp>>::iterator i = allStateHospData.begin(); i != allStateHospData.end(); i++ ){
            hospLowToHigh.push_back(&(*i->second));
        }
        /*
        //adding elements from the hashmap to the vector
        for(map<string, shared_ptr<stateHosp>>::iterator i = allStateHospData.begin(); i != allStateHospData.end(); i++ ){
            hospLowToHigh.push_back(&(*i->second));
        }
        vector<stateHosp *> vec = hospHighToLow;
        int sortedPos = 0;
        int hPos = 0;
        double hRating = 0;
        stateHosp *h = NULL;
        for(int i = 0; i < vec.size(); i++) {
          for(int j = sortedPos; j < vec.size(); j++){
            h = vec.at(j);
            if(h->getAvgRate() > hRating){
              hRating = h->getAvgRate();
              hPos = j;
            }
          }
          //select/move. Normal selection sort would just remove then insert, not swap.
          swap(vec.at(sortedPos), vec.at(hPos));
          //update variables
          sortedPos++;
          hRating = 0;
          hPos = sortedPos;
        }
        hospHighToLow = vec;
        */
       sort(hospLowToHigh.begin(), hospLowToHigh.end(), &stateHosp::compareOV);
    }
    void sortStateDemogPovLevelLowHigh(vector<stateDemog *> &incomeHighLow) {
        for(map<string, shared_ptr<stateDemog>>::iterator i = allStateDemogData.begin(); i != allStateDemogData.end(); i++ ){
            incomeHighLow.push_back(&(*i->second));
        }
        sort(incomeHighLow.begin(), incomeHighLow.end(), &stateDemog::compareP);
        /*
        cout << incomeHighLow.size() << " bruuuuuh" << endl;
        for(stateDemog *p : incomeHighLow) {
            cout << p->getState() << "   " << p->getBelowPoverty() << endl;
        }
        */
    }
    void sortStateDemogPovLevelHighLow(vector<stateDemog *> &povLevelHighLow) {
          for(map<string, shared_ptr<stateDemog>>::iterator i = allStateDemogData.begin(); i != allStateDemogData.end(); i++ ){
            povLevelHighLow.push_back(&(*i->second));
        }
        sort(povLevelHighLow.begin(), povLevelHighLow.end(), &stateDemog::compareP);
        reverse(povLevelHighLow.begin(), povLevelHighLow.end());
    }
    map<string, shared_ptr<stateDemog>> allStateDemogData;
    map<string, shared_ptr<stateHosp>> allStateHospData;
 };
 #endif