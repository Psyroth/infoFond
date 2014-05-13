#include "parser.h"
#include <list>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdlib>


Parser::Parser(std::string constraints, int syntax_level)
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
        _instruments_played.push_back(convertStringToInt(splitted_line));
        
    }
    
    std::cout<<_instruments_played[1][1]<<std::endl;
    std::cout<<instrumentsOfUser(4)[0]<<std::endl;
    
}

int Parser::getMusicianNb()
{
    return _musician_nb;
}

int Parser::getInstrumentNb()
{
    return _instrument_nb;
}

int Parser::getGroupNb()
{
    return _group_nb;
}

std::vector<int> Parser::convertStringToInt(std::vector<std::string> vec)
{
    std::vector<int> vec_int;
    for(std::vector<std::string>::iterator it=vec.begin(); it != vec.end(); ++it)
    {
        vec_int.push_back(atoi(it->c_str()));
    }
    return vec_int;
}


std::vector<std::string> Parser::split(std::string s, char delim) {
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


std::vector<int> Parser::instrumentsOfUser(int user)
{
    return _instruments_played[user];
}