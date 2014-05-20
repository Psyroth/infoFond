#include "problem3.h"
#include <iostream>

Problem3::Problem3(Parser1* parser):
Problem2(parser)
{
}


int Problem3::encodingC(int musician, int group)
{
    int res = (_musician_nb * _instrument_nb * _group_nb) + (_group_nb) + (_musician_nb * _group_nb) + musician * _group_nb + group;
    return res;
}


void Problem3::printResult()
{
    std::string res;
    if(_solver.okay())
    {
        res += "Satisfaisable \n";
        for(int group=0; group<_group_nb; ++group)
        {
            res += "Groupe " + std::to_string(group+1) + " : ";
            for(int instrument=0; instrument<_instrument_nb; ++instrument)
            {
                std::vector<int> musicians_for_instrument_in_group;
                for(int musician=0; musician<_musician_nb; ++musician)
                {
                    if(_solver.model[encodingX(musician, instrument, group)] == l_True)
                    {
                        musicians_for_instrument_in_group.push_back(musician);
                    }
                }
                if(musicians_for_instrument_in_group.size() > 1)
                {
                    res += "* ";
                }
                else if(musicians_for_instrument_in_group.size() == 1)
                {
                    res += std::to_string(musicians_for_instrument_in_group[0]+1) + " ";
                }
                else// == 0
                {
                    res += "* ";
                }
            }
            
            //affichage des chanteurs
            for(int musician=0; musician<_musician_nb; ++musician)
            {
                if(_solver.model[encodingC(musician, group)] == l_True)
                {
                    res += std::to_string(musician+1) + " ";
                }
            }
            res += "\n";
        }
    }
    else
    {
        res = "Non Satisfaisable";
    }
    _finalResult = res;
    
}

void Problem3::addAllClauses()
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
    
    //ajout des variables C(a,c)
    for(int i=0; i<_group_nb*_musician_nb; ++i)
    {
        _solver.newVar();
    }
    
    //contraintes
    
    aMusicianInMinOneGroupForOneInstrumentWhichHeCanPlayOrToSing();
    aMusicianOnlyOnceInAGroup();
    maxOneMusicianForOneInstrumentInAGroup();
    groupFullOrEmpty();
    defPVariable();
    aMusicianInMaxNGroups();
    aMusicianCantPlayWithAnInstrumentWhichHeCantPlay();
    minOneSingerInAllActiveGroups();
    onlySingerCanSing();
    
}

void Problem3::aMusicianInMinOneGroupForOneInstrumentWhichHeCanPlayOrToSing()
{
    //un musicien est dans au moins un groupe pour un instrument qu'il sait jouer ou pour le chant (ce qui change de Q1, c1)
    for(int musician = 0; musician < _musician_nb; ++musician)
    {
        vec<Lit> lits;
        for(int group = 0; group < _group_nb; ++group)
        {
            for(int indexOfInstrumentList = 0; indexOfInstrumentList < _parser->instrumentsOfUser(musician).size(); ++indexOfInstrumentList)
            {
                lits.push(Lit(encodingX(musician, _parser->instrumentsOfUser(musician)[indexOfInstrumentList], group)));
            }
            lits.push(Lit(encodingC(musician, group)));
        }
        _solver.addClause(lits);
    }
}


void Problem3::minOneSingerInAllActiveGroups()
{
    //Tous les groupes actifs doivent contenir au moins un chanteur
    for(int group=0; group<_group_nb; ++group)
    {
        vec<Lit> lits;
        lits.push(~Lit(encodingA(group)));
        for(int musician=0; musician<_musician_nb; ++musician)
        {
            lits.push(Lit(encodingC(musician, group)));
        }
        _solver.addClause(lits);
    }
}

void Problem3::onlySingerCanSing()
{
    //Uniquement les chanteurs peuvent chanter
    for(int group=0; group<_group_nb; ++group)
    {
        for(int musician=0; musician<_musician_nb; ++musician)
        {
            if(!dynamic_cast<Parser3*>(_parser)->isSinger(musician))
            {
                _solver.addUnit(~Lit(encodingC(musician, group)));
            }
        }
    }
}

