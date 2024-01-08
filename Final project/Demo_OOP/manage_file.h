#ifndef MANAGE_FILE_H_INCLUDED
#define MANAGE_FILE_H_INCLUDED
#include "constants.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <set>

class Manage_file{
    private:
        ALLEGRO_FILE *file;
        float highest_score;
        set<float> scores;

    public:
        Manage_file();

        void read_file();
        void write_file(float);
        float get_highest_score();
        void delete_duplicate();

};

#endif // MANAGE_FILE_H_INCLUDED
