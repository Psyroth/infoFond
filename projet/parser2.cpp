#include "parser2.h"
#include <list>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdlib>


Parser2::Parser2()
{}


Parser2::Parser2(std::string constraints)
{
        
    std::ifstream infile(constraints.c_str());
   

    std::string line;
    
    std::getline(infile, line);
    
    std::istringstream iss(line);
    int a, b, c;
    if (!(iss >> a >> b >> c)) // error
    {
        std::cout<<"ERROR"<<std::endl;
    } 
    
    std::cout<<a<<", "<<b<<", "<<c<<std::endl;
    
    _musician_nb = a;
    _instrument_nb = b;
    _group_nb = c;        
    
    
    
    while (std::getline(infile, line))
    {
        // Split de la ligne
        std::vector<std::string> splitted_line = split(line, ' ');
        // Suppression du numero d'utilisateur
        splitted_line.erase(splitted_line.begin());
        // Groupe max
        _max_group.push_back(atoi(splitted_line[0].c_str()));
        splitted_line.erase(splitted_line.begin());
        // Les instruments joues 
        std::vector<int> instruments = convertStringToInt(splitted_line);
        _instruments_played.push_back(instruments);
        // Les instruments non joues
        std::vector<int> instrumentsNotPlayed;
        for(int i=0; i<_instrument_nb; ++i)
        {
            if(!isInVector(instruments, i))
            {
                instrumentsNotPlayed.push_back(i);
            }
        }
        _instruments_not_played.push_back(instrumentsNotPlayed);
        
    }
    
    std::cout<<_instruments_played[0][0]<<std::endl;
    std::cout<<instrumentsOfUser(4)[0]<<std::endl;
    
}

std::vector< int > Parser2::instrumentsNotPlayedOfUser(int user)
{
    
    return _instruments_not_played[user];
}


int Parser2::maxGroupOfUser(int user)
{
    return _max_group[user];
}

bool Parser2::isInVector(std::vector<int> tab, int elem)
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
