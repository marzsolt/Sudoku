#include <fstream> // std::ifstream

#include "gamemaster.hpp"

GameMaster::GameMaster() { }

std::vector<unsigned short> GameMaster::loadFieldsFromFile(std::string filename) {
    std::ifstream in (filename.c_str());
    if(in.fail())
        return std::vector<unsigned short>(81, 0);
    std::vector<unsigned short> nums(81);
    for(unsigned short i = 0; i < 81; i++)
        in >> nums[i];
    return nums;
}
