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
    virtual bool solve();
    virtual void printResult();
    virtual void write(std::string output);
    virtual void addAllClauses();
    
protected:
    Solver _solver;
    Parser1 *_parser;
    
    int _musician_nb;
    int _instrument_nb;
    int _group_nb;
    std::string _finalResult;
    
    virtual void aMusicianInMinOneGroupForOneInstrumentWhichHeCanPlay();
    virtual void defPVariable();
    virtual void aMusicianInMaxOneGroup();
    virtual void aMusicianOnlyOnceInAGroup();
    virtual void maxOneMusicianForOneInstrumentInAGroup();
    virtual void groupFullOrEmpty();
};

#endif // PROBLEM_H
