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
    const char *seqChar = seqStr.c_str();
    uint64_t encodedSequence = 0;
    for ( int i=0; i<20; i++ ) {
        // 'T' is encoded as bits '00'
        if ( seqChar[i] == 'A' ) {
            encodedSequence += 1;
        } else if ( seqChar[i] == 'G' ) {
            encodedSequence += 2;
        } else if ( seqChar[i] == 'C' ) {
            encodedSequence += 3;
        }
        encodedSequence <<= 2;
    }
    this->sequence = encodedSequence;
}

uint64_t Guide::getSequence( ) {
    return this->sequence;
}

void Guide::computeActivities( ) {
    this->activities.push_back( log( this->point[0] / this->point[1] ));
    this->activities.push_back( log( this->point[0] / this->point[3] ));
    this->activities.push_back( log( this->point[1] / this->point[3] ));
    this->activities.push_back( log( this->point[0] / this->point[5] ));
    this->activities.push_back( log( this->point[0] / this->point[7] ));
    this->activities.push_back( log( this->point[1] / this->point[7] ));
}

vector<double> Guide::getActivities() {
    return this->activities;
}

double Guide::getActivity( int index) {
    return this->activities[ index];
}

string Guide::getId( ) {
    return this->id;
}
