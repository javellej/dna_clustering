#ifndef _DATASET_HPP_
#define _DATASET_HPP_

#include <Guide.hpp>
#include <dlib/matrix.h>
#include <vector>

using namespace std;

class DataSet {
public:
    DataSet( vector<Guide> guides);
    void makeKernelMatrix( );
    double squareDistance( vector<double> x); // square of the distance to the center of the sphere in the kernel space
    bool connectedPoints( int indexA, int indexB);
    void computeClusters( );
    int getNumClusters( );
private:
    vector<Guide> guides;
    int numPoints;
    vector< vector<double> > dataPoints;
    int numClusters;
    vector< vector<Guide> > clusters;
    // qp related data
    dlib::matrix<double> Q;
    dlib::matrix<double> alpha;
    double quadraticTerm;
    double squareRadius;
};

#endif
