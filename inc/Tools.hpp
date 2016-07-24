#include <vector>
#include <string>

using namespace std;

class Tools {
    
public:
    static vector<double> splitString( const string& str);
    static vector< vector<double> > readFile( const string& fileName);
    static void writeFile( const string& fileName, vector< vector<double> > points);
    
};
