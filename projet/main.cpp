#include "parser3.h"
#include "problem3.h"

#include <iostream>

int main(int argc, char **argv)
{
    // Vérifier le nombre d'arguments
    if (argc != 3)
    {
        std::cerr << "Utilisation : " << argv[0] << " <contraintes> <sortie>" << std::endl;
        return 1;
    }

    std::string binary_name(argv[0]);
    std::string constraints(argv[1]);
    std::string output(argv[2]);

    
    int question_number = 3;

    if (binary_name.size() >= 13)
    {
        char c = binary_name[binary_name.size()-5];

        if (c == '1') question_number = 1;
        else if (c == '2') question_number = 2;
        else if (c == '3') question_number = 3;
    }

    // Parser le fichier de contraintes
    Parser1 *parser;

    // Résoudre le problème
    Problem1 *problem;
    
    if(question_number == 1)
    {
        parser = new Parser1(constraints);
        problem = new Problem1(parser);
    }
    else if(question_number == 2)
    {
        parser = new Parser2(constraints);
        problem = new Problem2(parser);
    }
    else if(question_number == 3)
    {
        parser = new Parser3(constraints);
        problem = new Problem3(parser);
    }

    problem->addAllClauses();
    problem->solve();
    problem->printResult();
    problem->write(output);
    delete problem;
    delete parser;
}