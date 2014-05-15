#ifndef PROBLEM_H
#define PROBLEM_H

#include "parser.h"
#include "minisat/Solver.hpp"

class Problem
{
public:
    Problem(Parser parser);
    
    int encodingX(int musician, int instrument, int group);
    int encodingA(int group);
    void solve();
    void printResult();
    
private:
    Solver _solver;
    Parser _parser;
    
    int _musician_nb;
    int _instrument_nb;
    int _group_nb;
};

#endif // PROBLEM_H
