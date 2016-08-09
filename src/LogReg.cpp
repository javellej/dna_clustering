#include <LogReg.hpp>
#include <Guide.hpp>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

LogReg::LogReg( vector< vector<Guide> > guideClusters) {
    int numClusters = guideClusters.size();
    for ( int i=0; i<numClusters; i++ ) {
        vector<uint64_t> sequences;
        int clusterSize = guideClusters[i].size();
        for ( int j=0; j<clusterSize; j++ ) {
            sequences.push_back( guideClusters[i][j].getSequence());
        }
        this->clusters.push_back( sequences);
    }
    this->numClusters = numClusters;
}

void LogReg::computeStatistics( ) {
    // parse sequences and count subsequences of amino acids
    for ( int i=0; i<this->numClusters; i++ ) {
        int singletons[4] = {0};
        int pairs[16] = {0};
        int triples[64] = {0};
        int clusterSize = this->clusters[i].size();
        for ( int j=0; j<clusterSize; j++ ) {
            uint64_t seq = this->clusters[i][j];
            // single amino acid
            uint64_t mask = 0x3;
            //cout << "sequence " << seq << endl;
            for ( int k=0; k<20; k++ ) {
                uint64_t index = (uint64_t) ( mask & seq ) >> 2*k;
                //cout << "index " << index << endl;
                singletons[index]++;
                mask <<= 2;
            }
            // pairs
            mask = 0xf;
            for ( int k=0; k<19; k++ ) {
                uint64_t index = (uint64_t) ( mask & seq ) >> 2*k;
                //cout << "index " << index << endl;
                pairs[index]++;
                mask <<= 2;
            }
            // triples
            mask = 0x3f;
            for ( int k=0; k<18; k++ ) {
                uint64_t index = (uint64_t) ( mask & seq ) >> 2*k;
                //cout << "index " << index << endl;
                triples[index]++;
                mask <<= 2;
            }
        }
        cout << "1 amino acid" << endl;
        for ( int j=0; j<4; j++ ) {
            cout << singletons[j] << " ";
        }
        cout << endl;
        cout << "2 amino acids" << endl;
        for ( int j=0; j<16; j++ ) {
            cout << pairs[j] << " ";
        }
        cout << endl;
        cout << "3 amino acids" << endl;
        for ( int j=0; j<64; j++ ) {
            cout << triples[j] << " ";
        }
        cout << endl;
    }
}

void LogReg::printClusters( ) {
    int numClusters = this->numClusters;
    for ( int i=0; i<numClusters; i++ ) {
        int clusterSize = this->clusters[i].size();
        for ( int j=0; j<clusterSize; j++ ) {
            cout << this->clusters[i][j] << " ";
        }
        cout << endl;
    }
}

