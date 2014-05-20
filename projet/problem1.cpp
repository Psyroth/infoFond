#include "problem1.h"
#include <iostream>
#include <fstream>

Problem1::Problem1(Parser1 *parser):
_parser(parser),
_musician_nb(_parser->getMusicianNb()),
_instrument_nb(_parser->getInstrumentNb()),
_group_nb(_parser->getGroupNb())
{
}


int Problem1::encodingX(int musician, int instrument, int group)
{
    int res = _instrument_nb * _group_nb * musician +
    _group_nb * instrument +
    group; 
    return res;
}

int Problem1::encodingA(int group)
{
    int res = (_musician_nb * _instrument_nb * _group_nb) + group;
    return res;
}

int Problem1::encodingP(int musician, int group)
{
    int res = (_musician_nb * _instrument_nb * _group_nb) + _group_nb + musician*_group_nb + group;
    return res;
}


bool Problem1::solve()
{
    _solver.solve();
    return _solver.okay();
}

void Problem1::printResult()
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
                    std::cout<<"Plusieurs musiciens possibles pour la place : groupe("<<group+1<<"), "<<instrument+1<<")"<<std::endl;
                    for(std::vector<int>::iterator it=musicians_for_instrument_in_group.begin(); it!=musicians_for_instrument_in_group.end(); ++it)
                    {
                        std::cout<<(*it)+1<<std::endl;
                    }
                    res += "* ";
                }
                else if(musicians_for_instrument_in_group.size() == 1)
                {
                    res += std::to_string(musicians_for_instrument_in_group[0]+1) + " ";
                }
                else// == 0
                {
                    std::cout<<"Pas de musicien pour la place : groupe("<<group+1<<"), "<<instrument+1<<")"<<std::endl;
                    res += "* ";
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
    std::cout<<res<<std::endl;
}

void Problem1::write(std::string output)
{
    std::ofstream outputFile;
    outputFile.open(output);
    outputFile << _finalResult;
    outputFile.close();
}



void Problem1::addAllClauses()
{
    std::cout<<"Add all causes 1"<<std::endl;
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
    defPVariable();
    aMusicianInMaxOneGroup();
    aMusicianOnlyOnceInAGroup();
    maxOneMusicianForOneInstrumentInAGroup();
    groupFullOrEmpty();
}


void Problem1::aMusicianInMinOneGroupForOneInstrumentWhichHeCanPlay()
{
    //un musicien est dans au moins un groupe pour un instrument qu'il sait jouer
    for(int musician = 0; musician < _musician_nb; ++musician)
    {
        vec<Lit> lits;
        for(int group = 0; group < _group_nb; ++group)
        {
            for(int indexOfInstrumentList = 0; indexOfInstrumentList < _parser->instrumentsOfUser(musician).size(); ++indexOfInstrumentList)
            {
                lits.push(Lit(encodingX(musician, _parser->instrumentsOfUser(musician)[indexOfInstrumentList], group)));
            }
        }
        _solver.addClause(lits);
    }
}

void Problem1::defPVariable()
{
    // def de la variable P qui est vraie si le musicien a est dans le groupe c
    for(int musician=0; musician<_musician_nb; ++musician)
    {
        for(int group=0; group<_group_nb; ++group)
        {
            for(int instrument=0; instrument<_instrument_nb; ++instrument)
            {
                _solver.addBinary(~Lit(encodingX(musician, instrument, group)), Lit(encodingP(musician, group)));
            }
            
            vec<Lit> lits;
            lits.push(~Lit(encodingP(musician, group)));
            for(int instrument=0; instrument<_instrument_nb; ++instrument)
            {
                lits.push(Lit(encodingX(musician, instrument, group)));
            }
        }
    }
}

void Problem1::aMusicianInMaxOneGroup()
{ 
    // Un musicien est dans un seul groupe
    for(int musician=0; musician<_musician_nb; ++musician)
    {
        for(int group1=0; group1<_group_nb; ++group1)
        {
            for(int group2=group1+1; group2<_group_nb; ++group2)
            {
                _solver.addBinary(~Lit(encodingP(musician, group1)), ~Lit(encodingP(musician, group2)));
            }
        }
    }
}

void Problem1::aMusicianOnlyOnceInAGroup()
{
    //pas deux fois le meme musicien dans un meme groupe
    for(int group = 0; group < _group_nb; ++group)
    {
        for(int musician = 0; musician < _musician_nb; ++musician)
        {
            //attention, ici, on ajoute peut etre 2 fois les meme clauses, je ne sais pas si c'est un probleme
            for(int instrument1 = 0; instrument1 < _instrument_nb; ++instrument1)
            {
                for(int instrument2 = instrument1+1; instrument2 < _instrument_nb; ++instrument2)
                {
                    _solver.addBinary(~Lit(encodingX(musician, instrument1, group)), ~Lit(encodingX(musician, instrument2, group)));
                }
            }
        }
    }
}


void Problem1::maxOneMusicianForOneInstrumentInAGroup()
{
    //pas 2 musiciens pour le meme instrument dans le meme groupe
    for(int group=0; group<_group_nb; ++group)
    {
        for(int instrument=0; instrument<_instrument_nb; ++instrument)
        {
            for(int musician1=0; musician1<_musician_nb; ++musician1)
            {
                for(int musician2=musician1+1; musician2<_musician_nb; ++musician2)
                {
                    _solver.addBinary(~Lit(encodingX(musician1, instrument, group)), ~Lit(encodingX(musician2, instrument, group)));
                }
            }
        }
    }
}

void Problem1::groupFullOrEmpty()
{
    //tout groupe est complet ou vide
    for(int group=0; group<_group_nb; ++group)
    {
        for(int musician=0; musician<_musician_nb; ++musician)
        {
            for(int instrument=0; instrument<_instrument_nb; ++instrument)
            {
                _solver.addBinary(~Lit(encodingX(musician, instrument, group)), Lit(encodingA(group)));
            }
        }
    }
    
    for(int group=0; group<_group_nb; ++group)
    {
        for(int instrument=0; instrument<_instrument_nb; ++instrument)
        {
            vec<Lit> lits;
            lits.push(~Lit(encodingA(group)));
            for(int musician=0; musician<_musician_nb; ++musician)
            {
                lits.push(Lit(encodingX(musician, instrument, group)));
            }
            _solver.addClause(lits);
        }
    }
}
