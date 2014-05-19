#ifndef PROBLEM_H
#define PROBLEM_H

#include "parser1.h"
#include "minisat/Solver.hpp"

class Problem1
{
public:
    Problem1(Parser1 *parser);
    
    virtual int encodingX(int musician, int instrument, int group);
    virtual int encodingA(int group);
    virtual void solve();
    virtual void printResult();
    virtual void addAllClauses();
    
protected:
    Solver _solver;
    Parser1 *_parser;
    
    int _musician_nb;
    int _instrument_nb;
    int _group_nb;
    
    virtual void addC1();
    virtual void addC2();
    virtual void addC3();
    virtual void addC4();
};

#endif // PROBLEM_H
