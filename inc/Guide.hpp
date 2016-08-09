#ifndef _GUIDE_HPP_
#define _GUIDE_HPP_

#include <vector>
#include <string>

using namespace std;
/*
typedef enum activit_name {
    int 0_7_N   = 0;
    int 0_14_N  = 1;
    int 7_14_N  = 2;
    int 0_7_D   = 3;
    int 0_14_D  = 4;
    int 7_14_   = 5;
};*/

class Guide {
    
public:
    Guide( vector<double> point);
    void setId( const string& idStr);
    void setGene( const string& geneStr);
    void setSequence( const string& seqStr);
    uint64_t getSequence( );
    void computeActivities( );
    vector<double> getActivities();
    double getActivity( int index);
    string getId( );
private:
    string id;
    string gene;
    uint64_t sequence; // compressed encoding of a AA sequence
    vector<double> point;
    // this vector contains variables corresponding to the activities we chose to study
    vector<double> activities; // ( 0_7_N, 0_14_N, 7_14_N, 0_7_D, 0_14_D, 7_14_D)
    double activity;
    
};

#endif
