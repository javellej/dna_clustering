#include <Tools.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

vector<double> Tools::splitString( const string& str) {
    vector<double> values;
    istringstream iss( str); // Turn the string into a stream.
    string geneStr, guideStr, seqStr;
    double val;
    iss >> geneStr >> guideStr >> seqStr;
    //cout << "gene : " << geneStr << endl;
    //cout << "guide id : " << guideStr << endl;
    //cout << "sequence : " << seqStr << endl;
    while ( iss >> val ) {
    //    cout << val << " ";
        values.push_back( val);
    }
    //cout << endl;
    return values;
}

vector< vector<double> > Tools::readFile( const string& fileName) {
    ifstream inputFile( fileName.c_str(), ifstream::in);
    if ( inputFile.good() == 0 ) {
        cout << "Error - Bad file name" << endl;
        throw 1;
    }
    vector< vector<double> > points;
    string line;
    while ( getline( inputFile, line) ) {
        vector<double> point = splitString( line);
        if ( point.size() != 0 ) {
            points.push_back( splitString( line));
        }
    }
    return points;
}

void Tools::writeFile( const string& fileName, vector< vector<double> > points) {
    ofstream outputFile( fileName.c_str(), ofstream::out);
    for ( int i=0; i<points.size(); i++ ) {
        vector<double> currPoint = points[i];
        for ( int j=0; j<currPoint.size(); j++ ) {
            outputFile << currPoint[j] << " ";
        }
        outputFile << endl;
    }
}
