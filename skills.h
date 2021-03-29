// skills.h
#ifndef SKILLS_H
#define SKILLS_H

#include "pugixml/pugixml.hpp"

class SKILLS
{
private:
    int ATK;
    std::string NAME;

public:

    static const std::string MONSTER_ART_FOLDER_PATH;
    // have to be char [] as the load_file() does not support string
    static const char MONSTER_STATS_FILE[];
    static const char MONSTER_SKILLS_FILE[];

    int getATK();

    void setATK(int newATK);

    std::string getNAME();

    void loadMonsterXML(pugi::xml_document&);
};

#endif
