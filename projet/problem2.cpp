#include "problem2.h"
#include <iostream>


Problem2::Problem2(Parser1* parser):
Problem1(parser)
{
    std::cout<<"Constructeur 2"<<std::endl;
}

void Problem2::printResult()
{
    std::string res;
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
    std::cout<<res<<std::endl;
}



std::vector<int> Problem2::inc(std::vector< int > tab, int i, int base)
{
    if (i < tab.size())
    {
        if(tab[i]<base-1)
        {
            tab[i]++;
        }
    
        else if (tab[i]==base-1)
        {
            tab[i] = 0;
            tab = inc(tab, i+1, base);
        }
        else
        {
            std::cout<<"ERROR"<<std::endl;
        }
    }
    return tab;
}



bool Problem2::valid(std::vector< int > tab)
{
    std::vector<int> newTab;
    for(int i=0; i<tab.size(); ++i)
    {
        if(!isInVector(newTab, tab[i]))
        {
            newTab.push_back(tab[i]);
        }
        else
        {
            return false;
        }
    }
    return true;
}


bool Problem2::isInVector(std::vector<int> tab, int elem)
{
    for(int i=0; i<tab.size(); ++i)
    {
        if(tab[i] == elem)
        {
            return true;
        }
    }
    return false;
}

std::vector< std::vector< int > > Problem2::generateVector(int maxGroup, int sizeOfCoordsVector)
{
    std::vector< std::vector<int> > res;
    std::vector<int> aVec;
    int cpt=0;
    
    for(int i=0; i< maxGroup+1; ++i)
    {
        aVec.push_back(0);
    }
    while(pow(sizeOfCoordsVector,maxGroup+1) > cpt)
    {
        aVec = inc(aVec, 0, sizeOfCoordsVector);
        if(valid(aVec))
        {
            res.push_back(aVec);
        }
        ++cpt;
    }
    return res;
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
    
    //contraintes
    addC1();
    addC3();
    addC4();
    addC5();
    addC6();
    addC7();
    
}

void Problem2::addC5()
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

void Problem2::addC6()
{
    std::cout<<"debut c6"<<std::endl;
    //initialisation du vecteur de coordonnees
    //vecteur de tuples ou premier indice = instrument et deuxieme indice = groupe
    std::vector< std::vector<int> > coords;
    for(int instrument = 0; instrument < _instrument_nb; ++instrument)
    {
        for(int group = 0; group < _group_nb; ++group)
        {
            std::vector<int> item_coords;
            item_coords.push_back(instrument);
            item_coords.push_back(group);
            coords.push_back(item_coords);
        }
        
    }
    
    //Un musicien peut etre au plus dans k groupes NEW PAR RAPPORT A Q1
    for(int musician=0; musician<_musician_nb; ++musician)
    {
        std::vector<std::vector<int> > aVec = generateVector(dynamic_cast<Parser2*>(_parser)->maxGroupOfUser(musician), coords.size());
        for(int index1=0; index1<aVec.size(); ++index1)
        {
            vec<Lit> lits;
            for(int index2=0; index2<aVec[index1].size(); ++index2)
            {
                lits.push(~Lit(encodingX(musician,coords[aVec[index1][index2]][0],coords[aVec[index1][index2]][1])));
            }
            _solver.addClause(lits);
        }
    }
    std::cout<<"fin c6"<<std::endl;
}

void Problem2::addC7()
{
    std::cout<<"debut c7"<<std::endl;
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
    std::cout<<"fin c7"<<std::endl;
}
