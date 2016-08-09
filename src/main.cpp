#include <Tools.hpp>
#include <Guide.hpp>
#include <DataSet.hpp>
#include <LogReg.hpp>
#include <iostream>
#include <string>
#include <vector>

int main( int argc, const char * argv[]) {
    std::cout << "Welcome to the DNA clustering program.\n";
    if ( argc != 3 ) {
        cout << "Usage : " << argv[0] << " <training file name> <data file name>" << endl;
        throw 1;
    }
    string trainingFile = argv[1];
    string dataFile = argv[2];
    string outputFile = "outData.txt";
    if ( ( trainingFile == outputFile ) || ( dataFile == outputFile ) ) {
        cout << "Input and output files are the same" << endl;
        throw 1;
    }
    vector<Guide> trainingGuides = Tools::readFile( trainingFile);
    vector<Guide> dataGuides = Tools::readFile( dataFile);
    // compute guide activities
    cout << trainingGuides.size() << endl;
    for ( int i=0; i<trainingGuides.size(); i++ ) {
        trainingGuides[i].computeActivities();
    }
    for ( int i=0; i<dataGuides.size(); i++ ) {
        dataGuides[i].computeActivities();
    }
    // create data set based on guides and their activities
    DataSet data( trainingGuides, dataGuides);
    data.computeClusters();
    data.printClusters();
    // compute statistics
    LogReg lr( data.getClusters());
    lr.printClusters();
    lr.computeStatistics();
    return 0;
}

