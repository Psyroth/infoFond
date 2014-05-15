#ifndef PROBLEM2_H
#define PROBLEM2_H

#include "parser2.h"
#include "minisat/Solver.hpp"
#include <cmath>

class Problem2
{
public:
    Problem2(Parser2 parser);
    
    int encodingX(int musician, int instrument, int group);
    int encodingA(int group);
    void solve();
    void printResult();
    std::vector< int > inc(std::vector< int > tab, int i, int base);
    bool valid(std::vector<int> tab);
    bool isInVector(std::vector<int> tab, int elem);
    std::vector<std::vector<int> > generateVector(int maxGroup, int sizeOfCoordsVector);
    
private:
    Solver _solver;
    Parser2 _parser;
    
    int _musician_nb;
    int _instrument_nb;
    int _group_nb;
};

#endif // PROBLEM2_H