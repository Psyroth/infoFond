#include "parser2.h"
#include <list>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdlib>


Parser2::Parser2(std::string constraints, int syntax_level)
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
        std::vector<std::string> splitted_line = split(line, ' ');
        splitted_line.erase(splitted_line.begin());
        _max_group.push_back(atoi(splitted_line[0].c_str()));
        splitted_line.erase(splitted_line.begin());
        _instruments_played.push_back(convertStringToInt(splitted_line));
        
    }
    
    std::cout<<_instruments_played[0][0]<<std::endl;
    std::cout<<instrumentsOfUser(4)[0]<<std::endl;
    
}

int Parser2::getMusicianNb()
{
    return _musician_nb;
}

int Parser2::getInstrumentNb()
{
    return _instrument_nb;
}

int Parser2::getGroupNb()
{
    return _group_nb;
}

std::vector<int> Parser2::convertStringToInt(std::vector<std::string> vec)
{
    std::vector<int> vec_int;
    for(std::vector<std::string>::iterator it=vec.begin(); it != vec.end(); ++it)
    {
        //on fait -1 car dans le fichier ca commence a 1 et ici on commence a 0
        vec_int.push_back(atoi(it->c_str())-1);
    }
    return vec_int;
}


std::vector<std::string> Parser2::split(std::string s, char delim) {
    std::vector<std::string> elems;
    
    std::string temp;
    int index = 0;
    while (index < s.length())
    {
        if(s.at(index) == delim)
        {
            elems.push_back(temp);
            temp = "";
        }
        else
        {
            temp.push_back(s.at(index));
        }
        ++index;
        
    }
    elems.push_back(temp);
    return elems;
}

std::vector< int > Parser2::instrumentsNotPlayedOfUser(int user)
{
    std::vector<int> instrumentsNotPlayedByUser;
    for(int i=0; i<_instrument_nb; ++i)
    {
        if(!isInVector(instrumentsOfUser(user), i))
        {
            instrumentsNotPlayedByUser.push_back(i);
        }
    }
    return instrumentsNotPlayedByUser;
}


std::vector<int> Parser2::instrumentsOfUser(int user)
{
    return _instruments_played[user];
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
