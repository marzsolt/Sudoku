#ifndef GAMEMASTER_HPP_INCLUDED
#define GAMEMASTER_HPP_INCLUDED

#include <vector> // std::vector

class GameMaster{
public:
    GameMaster();
    std::vector<unsigned short>loadFieldsFromFile(std::string filename);
};

#endif // GAMEMASTER_HPP_INCLUDED
