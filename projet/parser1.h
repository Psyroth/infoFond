#ifndef PARSER1_H
#define PARSER1_H
#include <string>
#include <vector>

class Parser1
{
public:
    Parser1();
    Parser1(std::string constraints);
    virtual std::vector<std::string> split(std::string s, char delim);
    virtual std::vector<int> convertVecStringToVecInt(std::vector<std::string> vec);
    virtual std::vector<int> instrumentsOfUser(int user);
    
    virtual int getMusicianNb();
    virtual int getInstrumentNb();
    virtual int getGroupNb();
    
protected:
    int _musician_nb;
    int _instrument_nb;
    int _group_nb;
    std::vector< std::vector<int> > _instruments_played;
};

#endif // PARSER1_H
