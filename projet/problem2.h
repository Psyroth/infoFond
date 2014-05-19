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

    virtual void addAllClauses() override;
    
protected:
    virtual void aMusicianInMaxNGroups();
    virtual void aMusicianCantPlayWithAnInstrumentWhichHeCantPlay();
    virtual void recFunc(int beginIndex, vec<Lit> *currentVec, int maxGroup, int musician);
};

#endif // PROBLEM2_H