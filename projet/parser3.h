#ifndef PARSER3_H
#define PARSER3_H
#include <string>
#include <vector>

class Parser3
{
public:
    Parser3(std::string constraints, int syntax_level);
    std::vector<std::string> split(std::string s, char delim);
    std::vector<int> convertStringToInt(std::vector<std::string> vec);
    std::vector<int> instrumentsOfUser(int user);
    std::vector<int> instrumentsNotPlayedOfUser(int user);
    bool isInVector(std::vector<int> tab, int elem);
    bool isSinger(int musician);

    int maxGroupOfUser(int user);
    
    int getMusicianNb();
    int getInstrumentNb();
    int getGroupNb();
    
private:
    int _musician_nb;
    int _instrument_nb;
    int _group_nb;
    std::vector< std::vector<int> > _instruments_played;
    std::vector<int> _max_group;
};

#endif // PARSER3_H
