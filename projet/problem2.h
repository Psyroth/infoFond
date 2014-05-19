#ifndef PROBLEM2_H
#define PROBLEM2_H

#include "parser2.h"
#include "minisat/Solver.hpp"
#include "problem1.h"
#include <cmath>

class Problem2 : public Problem1
{
public:
    Problem2(Parser1 *parser);

    void printResult() override;
    virtual std::vector< int > inc(std::vector< int > tab, int i, int base);
    virtual bool valid(std::vector<int> tab);
    virtual bool isInVector(std::vector<int> tab, int elem);
    virtual std::vector<std::vector<int> > generateVector(int maxGroup, int sizeOfCoordsVector);
    virtual void addAllClauses() override;
    
protected:
    virtual void aMusicianInMaxNGroups();
    virtual void aMusicianCantPlayWithAnInstrumentWhichHeCantPlay();
    virtual void recFunc(int beginIndex, vec<Lit> *currentVec, int maxGroup, int musician);
};

#endif // PROBLEM2_H