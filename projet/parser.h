#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <vector>

class Parser
{
public:
    Parser(std::string constraints, int syntax_level);
    std::vector<std::string> split(std::string s, char delim);
    std::vector<int> convertStringToInt(std::vector<std::string> vec);
    std::vector<int> instrumentsOfUser(int user);
    
    int getMusicianNb();
    int getInstrumentNb();
    int getGroupNb();
    
private:
    int _musician_nb;
    int _instrument_nb;
    int _group_nb;
    std::vector< std::vector<int> > _instruments_played;
};

#endif // PARSER_H
