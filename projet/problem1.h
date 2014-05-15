#ifndef PROBLEM_H
#define PROBLEM_H

#include "parser1.h"
#include "minisat/Solver.hpp"

class Problem1
{
public:
    Problem1(Parser1 parser);
    
    int encodingX(int musician, int instrument, int group);
    int encodingA(int group);
    void solve();
    void printResult();
    
private:
    Solver _solver;
    Parser1 _parser;
    
    int _musician_nb;
    int _instrument_nb;
    int _group_nb;
};

#endif // PROBLEM_H
