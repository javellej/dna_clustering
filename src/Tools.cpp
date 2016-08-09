#include <Tools.hpp>
#include <Guide.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Guide Tools::splitString( const string& str) {
    vector<double> rawData;
    string geneStr, guideStr, seqStr;
    double val;
    // Turn the string into a stream.
    istringstream iss( str);
    // get string data at the beginning of the file
    iss >> geneStr >> guideStr >> seqStr;
    while ( iss >> val ) {
        rawData.push_back( val);
    }
    Guide guide( rawData);
    guide.setId( guideStr);
    guide.setGene( geneStr);
    guide.setSequence( seqStr);
    return guide;
}

vector<Guide> Tools::readFile( const string& fileName) {
    ifstream inputFile( fileName.c_str(), ifstream::in);
    if ( inputFile.good() == 0 ) {
        cout << "Error - Bad file name" << endl;
        throw 1;
    }
    vector<Guide> guides;
    string line;
    //bool isFirstLine = true;
    while ( getline( inputFile, line) ) {
        /*if ( isFirstLine ) {
            isFirstLine = false;
            continue;
        }*/
        guides.push_back( splitString( line));
    }
    cout << guides.size() << endl;
    return guides;
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
