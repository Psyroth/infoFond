#ifndef PARSER2_H
#define PARSER2_H
#include <string>
#include <vector>
#include "parser1.h"

class Parser2 : public Parser1
{
public:
    Parser2();
    Parser2(std::string constraints);

    virtual std::vector<int> instrumentsNotPlayedOfUser(int user);
    virtual bool isInVector(std::vector<int> tab, int elem);

    virtual int maxGroupOfUser(int user);

    
protected:
    std::vector<int> _max_group;
    std::vector< std::vector<int> > _instruments_not_played;
};

#endif // PARSER2_H