#include <DataSet.hpp>
#include <Guide.hpp>
#include <Math.hpp>
#include <Parameters.hpp>
#include <dlib/optimization.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <vector>
#include <iostream>

using namespace std;

DataSet::DataSet( vector<Guide> trainingGuides, vector<Guide> dataGuides) {
    this->trainingGuides = trainingGuides;
    this->dataGuides = dataGuides;
    //cout << "guides size " << guides.size() << endl;
    this->numTrainingPoints = trainingGuides.size();
    for ( int i=0; i<this->numTrainingPoints; i++ ) {
        vector<double> point;
        Guide currGuide = trainingGuides[i];
        for ( int j=0; j<6; j++ ) {
            point.push_back( currGuide.getActivity( j));
        }
        this->trainingPoints.push_back( point);
    }
    this->numDataPoints = dataGuides.size();
    for ( int i=0; i<this->numDataPoints; i++ ) {
        vector<double> point;
        Guide currGuide = dataGuides[i];
        for ( int j=0; j<6; j++ ) {
            point.push_back( currGuide.getActivity( j));
        }
        this->dataPoints.push_back( point);
    }
}

double DataSet::squareDistance( vector<double> x) {
    // compute second term of equation (13) in ref paper
    double sum = 0;
    for ( int i=0; i<this->numTrainingPoints; i++ ) {
        sum += alpha( i) * Math::gaussianKernel( this->trainingPoints[i], x);
    }
    return Math::gaussianKernel( x, x) - 2 * sum + this->quadraticTerm;
}

bool DataSet::connectedPoints( int indexA, int indexB) {
    int dim = this->trainingPoints[indexA].size();
    int numSampledPoints = NUM_SAMPLED_POINTS;
    for ( int i=1; i<numSampledPoints; i++ ) {
        // sample point
        vector<double> sampledPoint;
        for ( int j=0; j<dim; j++ ) {
            sampledPoint.push_back( ( ( numSampledPoints - i ) * this->trainingPoints[indexA][j] + i * this->trainingPoints[indexB][j] ) / (double) numSampledPoints);
        }
        // test if sampled point is outside the sphere
        if ( squareDistance( sampledPoint) > this->squareRadius ) {
            return false;
        }
    }
    return true;
}

bool DataSet::connectedPoints( vector<double> pointA, vector<double> pointB) {
    int dim = pointA.size();
    if ( dim != pointB.size() ) {
        cout << "Error : dimensions do not match" << endl;
        throw 1;
    }
    int numSampledPoints = NUM_SAMPLED_POINTS;
    for ( int i=1; i<numSampledPoints; i++ ) {
        // sample point
        vector<double> sampledPoint;
        for ( int j=0; j<dim; j++ ) {
            sampledPoint.push_back( ( ( numSampledPoints - i ) * pointA[j] + i * pointB[j] ) / (double) numSampledPoints);
        }
        // test if sampled point is outside the sphere
        if ( squareDistance( sampledPoint) > this->squareRadius ) {
            return false;
        }
    }
    return true;
}

void DataSet::computeClusters( ) {
    int n = this->numTrainingPoints;
    // define Lagrange multipliers vector
    double initVal = 1.0 / n;
    this->alpha.set_size( n, 1);
    for ( int i=0; i<n; i++ ) {
        this->alpha( i) =  initVal;
    }
    // define kernel matrix (quadratic semidefinite positive form) and diagonal vector for optimization problem
    // TODO : create private members
    cout << "BEGIN kernel matrix creation" << endl;
    this->Q.set_size( n, n);
    dlib::matrix<double> b;
    b.set_size( n, 1);
    for ( int i=0; i<n; i++ ) {
        b( i, 0) = Math::gaussianKernel( this->trainingPoints[i], this->trainingPoints[i]);
        for ( int j=0; j<n; j++ ) {
            this->Q( i, j) = Math::gaussianKernel( this->trainingPoints[i], this->trainingPoints[j]);
        }
    }
    cout << "END kernel matrix creation" << endl;
    // call SMO solver from dlib
    cout << "BEGIN optimization" << endl;
    double eps = OPTIMIZATION_PRECISION; // precision of optimization
    int maxIter = OPTIMIZATION_MAX_ITER;
    double numIter = dlib::solve_qp_using_smo( this->Q, 2*b, this->alpha, eps, maxIter); // according to the Wolfe dual
    cout << "numIter : " << numIter << endl;
    cout << "END optimization" << endl;
    // compute quadratic term needed for radius and distance computation
    this->quadraticTerm = 0;
    for ( int i=0; i<n; i++ ) {
        for ( int j=0; j<n; j++ ) {
            this->quadraticTerm += this->alpha( i) * Q( i, j) * this->alpha( j);
        }
    }
    // compute sphere square radius
    this->squareRadius = 0;
    for ( int i=0; i<n; i++ ) {
        double sqDist = squareDistance( trainingPoints[i]);
        if ( sqDist > this->squareRadius) {
            this->squareRadius = sqDist;
        }
    }
    cout << "sphere square radius : " << this->squareRadius << endl;
    // create graph of connected data points
    cout << "BEGIN graph creation" << endl;
    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS> Graph;
    Graph g( n);
    for ( int i=0; i<n; i++ ) {
        for ( int j=i+1; j<n; j++ ) {
            if ( connectedPoints( i, j) ) {
                add_edge( i, j, g);
            }
        }
    }
    cout << "END graph creation" << endl;
    // separate connected components of the graph
    cout << "BEGIN compute connected components" << endl;
    vector<int> components( n);
    int numClusters = boost::connected_components( g, &components[0]);
    cout << "END compute connected components" << endl;
    cout << "graph : " << boost::num_vertices( g) << " vertices and " << boost::num_edges( g) << " edges " << numClusters << " components" << endl;
    this->numClusters = numClusters;
    vector< vector<Guide> > trainingClusters( numClusters);
    this->clusters.resize( numClusters);
    // fill cluster from full data set
    cout << "BEGIN creating clusters" << endl;
    for ( int i=0; i<n; i++ ) { // put training data in clusters
        trainingClusters[components[i]].push_back( trainingGuides[i]);
    }
    cout << "END creating clusters" << endl;
    cout << "BEGIN assigning data points to clusters" << endl;
    for ( int i=0; i<this->numDataPoints; i++ ) { // put data points in clusters
        if ( squareDistance( this->dataPoints[i]) <= this->squareRadius ) {
            //bool isClusterFound = false;
            for ( int j=0; j<numClusters; j++ ) { // parse clusters and check which one the current data point belongs to
                vector<Guide> currCluster = trainingClusters[j];
                //for ( int k=0; k<currCluster.size(); j++ ) {
                    if ( connectedPoints( this->dataPoints[i], currCluster[0].getActivities()) ) {
                        this->clusters[j].push_back( dataGuides[i]);
                        //isClusterFound = true;
                        break;
                    }
                //}
                //if ( isClusterFound ) { break; }
            }
        }
    }
    cout << "BEGIN assigning data points to clusters" << endl;
    for ( int i=0; i<numClusters; i++ ) {
        cout << "cluster " << i << " : size " << this->clusters[i].size() << endl;
    }
}

void DataSet::printClusters( ) {
    for ( int i=0; i<this->numClusters; i++ ) {
        cout << "cluster " << i << endl;
        int clusterSize = this->clusters[i].size();
        for ( int j=0; j<clusterSize; j++ ) {
            cout << this->clusters[i][j].getId() << " ";
        }
        cout << endl;
    }
}

int DataSet::getNumClusters( ) {
    return this->numClusters;
}

vector< vector<Guide> > DataSet::getClusters( ) {
    return this->clusters;
}
