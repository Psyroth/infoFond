#ifndef PROBLEM_H
#define PROBLEM_H

#include "parser.h"
#include "minisat/Solver.hpp"

class Problem
{
public:
    Problem(Parser parser);
    
    int encoding(int musician, int instrument, int group);
    void solve();
    
private:
    Solver _solver;
    Parser _parser;
    
    int _musician_nb;
    int _instrument_nb;
    int _group_nb;
};

#endif // PROBLEM_H
