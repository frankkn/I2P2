#include "manage_file.h"

Manage_file::Manage_file() {
}

void Manage_file::read_file() {
    file = al_fopen("score.txt", "r");

    if (!file) {
        fprintf(stderr, "無法開啟檔案\n");
        return;
    }

    char buffer[256];
    al_fgets(file, buffer, sizeof(buffer));
    istringstream iss(buffer);

    float num;
    while (iss >> num) {
        scores.insert(num);
    }

    al_fclose(file);
}

void Manage_file::write_file(float new_score) {
    read_file();
    scores.insert(new_score);

    // 將數字寫回檔案
    file = al_fopen("score.txt", "w");
    if (!file) {
        fprintf(stderr, "無法開啟檔案\n");
        return;
    }

    for (auto score : scores) {
        al_fprintf(file, "%.2f \n", score);
    }
/*
    for (size_t i = 0; i < scores.size(); ++i) {
        al_fprintf(file, "%.2f ", scores[i]);
    }
*/
    al_fclose(file);
}

float Manage_file::get_highest_score() {
    read_file();
    float highest_score = 1001;
    for(auto score : scores)
        if( highest_score > score)
            highest_score = score;
    return highest_score;
};
