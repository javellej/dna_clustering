#ifndef _LOGREG_HPP_
#define _LOGREG_HPP_

#include <Guide.hpp>
#include <vector>
#include <string>

using namespace std;

class LogReg {
public:
    LogReg( vector< vector<Guide> >);
    void computeStatistics();
    void printClusters();
private:
    int numClusters;
    vector< vector<uint64_t> > clusters;
};

#endif
