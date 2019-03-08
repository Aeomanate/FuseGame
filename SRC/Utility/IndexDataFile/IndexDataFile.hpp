//
// Created by Lyosha12 on 05.03.2019.
//

#ifndef FUSEGAME_INDEXDATAFILE_HPP
#define FUSEGAME_INDEXDATAFILE_HPP

#include <map>
#include <string>
#include <vector>
#include <fstream>

std::vector<char> loadFromFileRawData(std::string data_name);
size_t getOffsetInRawData(std::string data_name);



#endif // FUSEGAME_INDEXDATAFILE_HPP
