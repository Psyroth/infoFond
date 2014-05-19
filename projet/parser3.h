#ifndef PARSER3_H
#define PARSER3_H
#include <string>
#include <vector>
#include "parser2.h"

class Parser3 : public Parser2
{
public:
    Parser3(std::string constraints);

    virtual bool isSinger(int musician);
    std::vector< int > instrumentsOfUser(int user) override;
};

#endif // PARSER3_H
