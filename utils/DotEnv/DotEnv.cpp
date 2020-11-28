#include "DotEnv.h"

DotEnv* DotEnv::_instance = nullptr;

DotEnv::DotEnv()
{

}

DotEnv::DotEnv(bool loadFromFile, std::string path)
{
    this->haveLoadFromFile = loadFromFile;
    if (!loadFromFile) return;
    this->name = new std::string[50];
    this->value = new std::string[50];

    numOfVar = 0;

    freopen(path.c_str(), "r", stdin);
    std::cout << path << std::endl;

    std::string s, sPre, sSuf;
    unsigned int i;
    while (getline(std::cin, s))
    {
        if (s.length() < 3) continue; // at least 3 character
        sPre = sSuf = "";
        i = -1;
        while (i + 1 < s.length() && s[++i] != '=')
        {
            if (s[i] != ' ')
            {
                sPre += s[i];
            }
        }
        while (i + 1 < s.length() && ++i < s.length())
        {
            if (s[i] != ' ')
            {
                sSuf += s[i];
            }
        }
        *(this->name + numOfVar) = sPre;
        *(this->value + numOfVar++) = sSuf;
    }

    fclose(stdin);
}

DotEnv* DotEnv::initDotEnv()
{
    if (_instance == nullptr)
    {
        _instance = new DotEnv(true, std::string(QCoreApplication::applicationDirPath().toLocal8Bit().constData()) + "/config.txt");
    }

    return _instance;
}

std::string DotEnv::operator[](const std::string& key)
{
    if (!(this->haveLoadFromFile))
        return getenv(key.c_str());

    for (int i = 0;i < this->numOfVar;i++)
    {
        if (this->name[i] == key)
            return this->value[i];
    }
    return "";
}

DotEnv::~DotEnv()
{
    delete[] name;
    delete[] value;
}

