#ifndef _DATASET_HPP_
#define _DATASET_HPP_

#include <Guide.hpp>
#include <dlib/matrix.h>
#include <vector>

using namespace std;

class DataSet {
public:
    DataSet( vector<Guide> trainingGuides, vector<Guide>dataGuides);
    void makeKernelMatrix( );
    double squareDistance( vector<double> x); // square of the distance to the center of the sphere in the kernel space
    bool connectedPoints( int indexA, int indexB);
    bool connectedPoints( vector<double> pointA, vector<double> pointB);
    void computeClusters( );
    int getNumClusters( );
    vector< vector<Guide> > getClusters();
    void printClusters( );
private:
    vector<Guide> trainingGuides;
    vector<Guide> dataGuides;
    int numTrainingPoints;
    int numDataPoints;
    vector< vector<double> > trainingPoints;
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
