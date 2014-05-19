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
    virtual int encodingP(int musician, int group);
    virtual void solve();
    virtual void printResult();
    virtual void addAllClauses();
    
protected:
    Solver _solver;
    Parser1 *_parser;
    
    int _musician_nb;
    int _instrument_nb;
    int _group_nb;
    
    virtual void aMusicianInMinOneGroupForOneInstrumentWhichHeCanPlay();
    virtual void aMusicianInMaxOneGroup();
    virtual void aMusicianOnlyOnceInAGroup();
    virtual void maxOneMusicianForOneInstrumentInAGroup();
    virtual void groupFullOrEmpty();
    virtual void recFunc(int beginIndex, vec<Lit> *currentVec, int maxGroup, int musician);
};

#endif // PROBLEM_H
