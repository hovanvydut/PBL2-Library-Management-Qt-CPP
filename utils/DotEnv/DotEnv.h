#ifndef DOTENV_H
#define DOTENV_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <QCoreApplication>


class DotEnv
{

private:
    static DotEnv* _instance;
    std::string *name;
    std::string *value;
    int numOfVar;
    bool haveLoadFromFile;
    DotEnv();

public:
    static DotEnv* initDotEnv();
    DotEnv(bool=true, std::string="./.env");
    ~DotEnv();
    std::string operator[](const std::string&);

};

#endif // DOTENV_H
