#ifndef _MATH_HPP_
#define _MATH_HPP_

#include <vector>

using namespace std;

class Math {
public:
    static double sqNorm2( vector<double> x);
    static double gaussianKernel( vector<double> x1, vector<double> x2);
private:
    static double q;
};

#endif
