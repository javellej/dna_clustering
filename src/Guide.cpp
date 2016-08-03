#include <Guide.hpp>
#include <vector>
#include <math.h>

using namespace std;

Guide::Guide( vector<double> point) {
    this->point = point;
    this->activity = 0;
}

void Guide::setId( const string& idStr) {
    this->id = idStr;
}

void Guide::setGene( const string& geneStr) {
    this->gene = geneStr;
}

void Guide::setSequence( const string& seqStr) {
    this->sequence = seqStr;
}

void Guide::computeActivities( ) {
    this->activities.push_back( log( this->point[0] / this->point[1] ));
    this->activities.push_back( log( this->point[0] / this->point[3] ));
    this->activities.push_back( log( this->point[1] / this->point[3] ));
    this->activities.push_back( log( this->point[0] / this->point[5] ));
    this->activities.push_back( log( this->point[0] / this->point[7] ));
    this->activities.push_back( log( this->point[1] / this->point[7] ));
}

double Guide::getActivity( int index) {
    return this->activities[ index];
}
