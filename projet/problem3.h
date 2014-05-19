#ifndef PROBLEM3_H
#define PROBLEM3_H

#include "parser3.h"
#include "minisat/Solver.hpp"
#include <cmath>

class Problem3
{
public:
    Problem3(Parser3 parser);
    
    int encodingX(int musician, int instrument, int group);
    int encodingA(int group);
    int encodingC(int musician, int group);
    void solve();
    void printResult();
    std::vector< int > inc(std::vector< int > tab, int i, int base);
    bool valid(std::vector<int> tab);
    bool isInVector(std::vector<int> tab, int elem);
    std::vector<std::vector<int> > generateVector(int maxGroup, int sizeOfCoordsVector);
    
private:
    Solver _solver;
    Parser3 _parser;
    
    int _musician_nb;
    int _instrument_nb;
    int _group_nb;
};

#endif // PROBLEM3_H
