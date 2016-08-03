#ifndef _TOOLS_HPP_
#define _TOOLS_HPP_

#include <Guide.hpp>
#include <vector>
#include <string>

using namespace std;

class Tools {
    
public:
    static Guide splitString( const string& str);
    static vector<Guide> readFile( const string& fileName);
    static void writeFile( const string& fileName, vector< vector<double> > points);
    
};

#endif
