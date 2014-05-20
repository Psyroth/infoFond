#include "parser3.h"
#include <list>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdlib>


Parser3::Parser3(std::string constraints)
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
    
    
    _musician_nb = a;
    _instrument_nb = b-1;//car on enleve le chant
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
        std::vector<int> instruments = convertVecStringToVecInt(splitted_line);
        
        // Si le dernier instrument est le chant, on le retire de la liste des instruments 
        // et on met a true la case correspondante au musicien dans le vecteur _singers
        if(instruments[instruments.size()-1] == _instrument_nb)
        {
            _singers.push_back(true);
            instruments.pop_back();
        }
        else
        {
            _singers.push_back(false);
        }
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
    
}



bool Parser3::isSinger(int musician)
{
    return _singers[musician];
}


