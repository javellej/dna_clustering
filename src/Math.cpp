#include <Math.hpp>
#include <math.h>
#include <iostream>

using namespace std;

double Math::q = 40;

double Math::norm2( vector<double> x) {
    int squareNorm = 0;
    for ( int i=0; i<x.size(); i++ ) {
        squareNorm += x[i]*x[i];
    }
    return sqrt( squareNorm);
}

double Math::gaussianKernel( vector<double> x1, vector<double> x2) {
    int n = x1.size();
    if ( n != x2.size() ) {
        cout << "Gaussian kernel : vector sizes do not match" << endl;
        throw 1;
    }
    vector<double> diffVect; // to hold x1 - x2
    for ( int i=0; i<n; i++ ) {
        diffVect.push_back( x1[i] - x2[i]);
    }
    return exp( - Math::q * Math::norm2( diffVect));
}
