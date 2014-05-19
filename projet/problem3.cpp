#include "problem3.h"
#include <iostream>

Problem3::Problem3(Parser3 parser):
_parser(parser),
_musician_nb(_parser.getMusicianNb()),
_instrument_nb(_parser.getInstrumentNb()),
_group_nb(_parser.getGroupNb())
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
    
    //ajout des variables C(a,c)
    for(int i=0; i<_group_nb*_musician_nb; ++i)
    {
        _solver.newVar();
    }
    
    //contraintes
    
    //un musicien est dans au moins un groupe pour un instrument qu'il sait jouer
    for(int musician = 0; musician < _musician_nb; ++musician)
    {
        vec<Lit> lits;
        for(int group = 0; group < _group_nb; ++group)
        {
            for(int indexOfInstrumentList = 0; indexOfInstrumentList < _parser.instrumentsOfUser(musician).size(); ++indexOfInstrumentList)
            {
                lits.push(Lit(encodingX(musician, _parser.instrumentsOfUser(musician)[indexOfInstrumentList], group)));
            }
            lits.push(Lit(encodingC(musician, group)));
        }
        _solver.addClause(lits);
    }
    
    //pas deux fois le meme musicien dans un meme groupe
    for(int group = 0; group < _group_nb; ++group)
    {
        for(int musician = 0; musician < _musician_nb; ++musician)
        {
            //attention, ici, on ajoute peut etre 2 fois les meme clauses, je ne sais pas si c'est un probleme
            for(int instrument1 = 0; instrument1 < _instrument_nb; ++instrument1)
            {
                for(int instrument2 = 0; instrument2 < _instrument_nb; ++instrument2)
                {
                    if(instrument1 != instrument2)
                    {
                        _solver.addBinary(~Lit(encodingX(musician, instrument1, group)), ~Lit(encodingX(musician, instrument2, group)));
                    }
                }
            }
        }
    }
    
    //pas deux fois le meme musicien dans 2 groupes differents
    
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
        std::vector<std::vector<int> > aVec = generateVector(_parser.maxGroupOfUser(musician), coords.size());
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
    
    //Un musicien ne peut pas prendre une place pour un instrument qu'il ne joue pas
    for(int musician=0; musician<_musician_nb; ++musician)
    {
        for(int group=0; group<_group_nb; ++group)
        {
            std::vector<int> instNotPlayed = _parser.instrumentsNotPlayedOfUser(musician);
            for(int indexOfInstrumentsNotPlayed=0; indexOfInstrumentsNotPlayed<instNotPlayed.size(); ++indexOfInstrumentsNotPlayed)
            {
                _solver.addUnit(~Lit(encodingX(musician, instNotPlayed[indexOfInstrumentsNotPlayed], group)));
            }
        }
    }
    
    //pas 2 musiciens pour le meme instrument dans le meme groupe
    for(int group=0; group<_group_nb; ++group)
    {
        for(int instrument=0; instrument<_instrument_nb; ++instrument)
        {
            for(int musician1=0; musician1<_musician_nb; ++musician1)
            {
                for(int musician2=0; musician2<_musician_nb; ++musician2)
                {
                    if(musician1!=musician2)
                    {
                        _solver.addBinary(~Lit(encodingX(musician1, instrument, group)), ~Lit(encodingX(musician2, instrument, group)));
                    }
                }
            }
        }
    }
    
    
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
    // partie 2 de "groupes complets ou vides"
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
    
    //Uniquement les chanteurs peuvent chanter
    for(int group=0; group<_group_nb; ++group)
    {
        for(int musician=0; musician<_musician_nb; ++musician)
        {
            if(!parser.isSinger(musician))
            {
                _solver.addUnit(~Lit(encodingC(musician, group)));
            }
        }
    }
    
    
}



int Problem3::encodingX(int musician, int instrument, int group)
{
    int res = _instrument_nb * _group_nb * musician +
    _group_nb * instrument + group; 
    return res;
}

int Problem3::encodingA(int group)
{
    int res = (_musician_nb * _instrument_nb * _group_nb) + group;
    return res;
}

int Problem3::encodingC(int musician, int group)
{
    int res = (_musician_nb * _instrument_nb * _group_nb) + (_group_nb) + musician * _group_nb + group;
    return res;
}


void Problem3::solve()
{
    _solver.solve();
    if (_solver.okay())
    {
        std::cout<<"ok"<<std::endl;
    }
    else
    {
        std::cout<<"pas ok"<<std::endl;
    }
}

void Problem3::printResult()
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
    std::cout<<res<<std::endl;
}



std::vector<int> Problem3::inc(std::vector< int > tab, int i, int base)
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



bool Problem3::valid(std::vector< int > tab)
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


bool Problem3::isInVector(std::vector<int> tab, int elem)
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

std::vector< std::vector< int > > Problem3::generateVector(int maxGroup, int sizeOfCoordsVector)
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
