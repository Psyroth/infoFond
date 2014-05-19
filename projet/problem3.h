#ifndef PROBLEM3_H
#define PROBLEM3_H

#include "parser3.h"
#include "minisat/Solver.hpp"
#include "problem2.h"
#include <cmath>

class Problem3 : public Problem2
{
public:
    Problem3(Parser1 *parser);
    
    int encodingC(int musician, int group);
    void printResult() override;
    virtual void addAllClauses() override;
    
protected:
    virtual void aMusicianInMinOneGroupForOneInstrumentWhichHeCanPlayOrToSing();
    virtual void minOneSingerInAllActiveGroups();
    virtual void onlySingerCanSing();

};

#endif // PROBLEM3_H
