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
    
    std::cout<<a<<", "<<b<<", "<<c<<std::endl;
    
    _musician_nb = a;
    _instrument_nb = b-1;//car on enleve le chant
    _group_nb = c;        
    
    
    
    while (std::getline(infile, line))
    {
        std::vector<std::string> splitted_line = split(line, ' ');
        splitted_line.erase(splitted_line.begin());
        _max_group.push_back(atoi(splitted_line[0].c_str()));
        splitted_line.erase(splitted_line.begin());
        _instruments_played.push_back(convertVecStringToVecInt(splitted_line));
        
    }
    
    std::cout<<_instruments_played[0][0]<<std::endl;
    std::cout<<instrumentsOfUser(4)[0]<<std::endl;
    
    std::cout<<isSinger(5)<<std::endl;
    std::cout<<isSinger(6)<<std::endl;
    
}



bool Parser3::isSinger(int musician)
{
    bool res = false;
    if(isInVector(_instruments_played[musician], _instrument_nb))
    {
        res = true;
    }
    return res;
}

std::vector<int> Parser3::instrumentsOfUser(int user)
{
    std::vector<int> res = _instruments_played[user];
    if(res[res.size()-1] == _instrument_nb)
    {
        res.erase(res.begin()+res.size()-1);
    }
    return res;
}

