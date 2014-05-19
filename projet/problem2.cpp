#include "problem2.h"
#include <iostream>


Problem2::Problem2(Parser1* parser):
Problem1(parser)
{
    std::cout<<"Constructeur 2"<<std::endl;
}

void Problem2::addAllClauses()
{
    //ajout des variables X(a,b,c)
    for(int i=0; i < _musician_nb * _instrument_nb * _group_nb; ++i)
    {
        _solver.newVar();
    }
    
    //ajout des variables A(g)
    for(int i=0; i<_group_nb; ++i)
    {
        _solver.newVar();
    }
    
    //ajout des variables P(a,c)
    for(int i=0; i<_musician_nb * _group_nb; ++i)
    {
        _solver.newVar();
    }
    
    //contraintes
    aMusicianInMinOneGroupForOneInstrumentWhichHeCanPlay();
    aMusicianOnlyOnceInAGroup();
    maxOneMusicianForOneInstrumentInAGroup();
    groupFullOrEmpty();
    defPVariable();
    aMusicianInMaxNGroups();
    aMusicianCantPlayWithAnInstrumentWhichHeCantPlay();
    
}

void Problem2::recFunc(int beginIndex, vec<Lit> *currentVec, int maxGroup, int musician)
{
    if(currentVec->size() == maxGroup+1)
    {
        _solver.addClause(*currentVec);
    }
    else
    {
        for(int group=beginIndex; group<_group_nb; ++group)
        {
            currentVec->push(~Lit(encodingP(musician, group)));
            recFunc(group+1, currentVec, maxGroup, musician);
            currentVec->pop();
        }
    }
}

void Problem2::aMusicianInMaxNGroups()
{   
    for(int musician=0; musician<_musician_nb; ++musician)
    {
        vec<Lit> *lits = new vec<Lit>;
        recFunc(0, lits, dynamic_cast<Parser2*>(_parser)->maxGroupOfUser(musician), musician);
    }
}

void Problem2::aMusicianCantPlayWithAnInstrumentWhichHeCantPlay()
{
    //Un musicien ne peut pas prendre une place pour un instrument qu'il ne joue pas
    for(int musician=0; musician<_musician_nb; ++musician)
    {
        for(int group=0; group<_group_nb; ++group)
        {
            std::vector<int> instNotPlayed = dynamic_cast<Parser2*>(_parser)->instrumentsNotPlayedOfUser(musician);
            for(int indexOfInstrumentsNotPlayed=0; indexOfInstrumentsNotPlayed<instNotPlayed.size(); ++indexOfInstrumentsNotPlayed)
            {
                _solver.addUnit(~Lit(encodingX(musician, instNotPlayed[indexOfInstrumentsNotPlayed], group)));
            }
        }
    }
}
