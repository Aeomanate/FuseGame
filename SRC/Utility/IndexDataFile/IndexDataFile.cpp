// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Lyosha12 on 05.03.2019.
//
#include "IndexDataFile.hpp"


std::vector<char> loadFromFileRawData(std::string data_name) {
    std::ifstream data("data.bin", std::ios::binary);
    if(!data.is_open()) {
        throw std::runtime_error("Game file data.bin not found");
    }
    try {
        data.seekg(getOffsetInRawData(data_name));
    } catch (std::exception const& e) {
        throw std::logic_error("Data " + data_name + " not found in map");
    }
    uint32_t this_data_size;
    data.read((char*)&this_data_size, sizeof(uint32_t));
    
    std::vector<char> raw_data(this_data_size);
    data.read(raw_data.data(), this_data_size);
    data.close();
    
    return raw_data;
}

size_t getOffsetInRawData(std::string data_name) {
    static std::map<std::string, size_t> const file_index = {
		{ "BlizzardDOTRusbyme", 0 },
		{ "Background", 141848 },
		{ "Player64", 359864 },
		{ "SimpleBeamSpriteSheet", 368401 },
		{ "MassiveBeamGenerateSpriteSheet", 371969 },
		{ "MassiveBeamSpriteSheet", 454464 },
		{ "SimpleExplosionSpriteSheet4", 606072 },
		{ "SimpleExplosionSpriteSheet3", 777549 },
		{ "SimpleExplosionSpriteSheet2", 932833 },
		{ "SimpleExplosionSpriteSheet1", 1101888 },
		{ "PlayerDeathSpriteSheet", 1160420 },
		{ "MassiveExplosionSpriteSheet", 1527002 },
		{ "AngrySmile", 22023136 },
		{ "CrownOfThorns", 22030289 },
		{ "March8SpriteSheet", 22038773 },
		{ "Bomb1", 34062189 },
		{ "Bomb2", 34175141 },
		{ "Bomb3", 34241747 },
		{ "Bomb4", 34316918 },
		{ "EnemyDeath1", 34452203 },
		{ "EnemyDeath2", 34526046 },
		{ "EnemyDeath3", 34593839 },
		{ "EnemyShot", 34701127 },
		{ "MassiveAccumulation", 34750938 },
		{ "MassiveCancelAccumulation", 35029808 },
		{ "MassiveExplosion", 35058557 },
		{ "MassiveShot", 35236047 },
		{ "Pararam", 35375283 },
		{ "PlayerDeathSound", 35427863 },
		{ "PlayerShot", 35545446 },
		{ "TakeDamage", 35569644 },
		{ "BackgroundMusic (1)", 35593831 },
		{ "BackgroundMusic (10)", 41819316 },
		{ "BackgroundMusic (2)", 45164974 },
		{ "BackgroundMusic (3)", 47356802 },
		{ "BackgroundMusic (4)", 58521105 },
		{ "BackgroundMusic (5)", 62097351 },
		{ "BackgroundMusic (6)", 64688067 },
		{ "BackgroundMusic (7)", 75849524 },
		{ "BackgroundMusic (8)", 77374665 },
		{ "BackgroundMusic (9)", 79612684 },
		{ "SpecialMusic (1)", 84888825 },
		{ "SpecialMusic (2)", 89301365 },


    };
    
    return file_index.at(data_name);
}
