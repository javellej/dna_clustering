#include <Tools.hpp>
#include <Guide.hpp>
#include <DataSet.hpp>
#include <iostream>
#include <string>
#include <vector>

int main( int argc, const char * argv[]) {
    std::cout << "Welcome to the DNA clustering program.\n";
    if ( argc != 2 ) {
        cout << "Usage : " << argv[0] << " <input file name>" << endl;
        throw 1;
    }
    string inputFile = argv[1];
    string outputFile = "outData.txt";
    if ( inputFile == outputFile ) {
        cout << "Input and output files are the same" << endl;
        throw 1;
    }
    vector<Guide> guides = Tools::readFile( inputFile);
    //Tools::writeFile( outputFile, guides);
    // compute guide activities
    for ( int i=0; i<guides.size(); i++ ) {
        guides[i].computeActivities();
    }
    // create data set based on guides and their activities
    DataSet data( guides);
    data.computeClusters();
    cout << data.getNumClusters() << " clusters found" << endl;
    return 0;
}

