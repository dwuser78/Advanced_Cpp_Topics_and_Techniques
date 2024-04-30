#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

#define CARDS_PATH "q-a"
#define QUESTION_POSTFIX ".q"
#define ANSWER_POSTFIX ".a"
#define WIN_SCORES 6
#define NUM_SECTORS 13
#define MIN_SECTOR 1
#define START_SECTOR 1
#define STR_BUF_SIZE 1023

using namespace std;

void get_file_name(string *file_name, const uint32_t *sector, bool is_answer) {
    file_name->clear();

    if (*sector > NUM_SECTORS)
        return;

    file_name->append(CARDS_PATH "/");
    file_name->append(to_string(*sector));

    if (is_answer)
        file_name->append(ANSWER_POSTFIX);
    else
        file_name->append(QUESTION_POSTFIX);
}

uint32_t get_sector(const uint32_t *curr_sector, uint32_t *unavailable_sectors,
                    uint32_t offset) {
    uint32_t tmp;

    if (offset == 0)
        return 0;

    for (size_t i = 0; i < NUM_SECTORS; i++) {
        tmp = (*curr_sector + offset + i) % NUM_SECTORS;

        if (tmp == 0)
            tmp = NUM_SECTORS;

        if (unavailable_sectors[tmp - MIN_SECTOR] == 0)
            return tmp;
    }

    return 0;
}

bool read_file(const string *file_name, string *text) {
    ifstream infile;
    char *str_buf;
    bool is_first_line = true;

    text->clear();

    infile.exceptions (ifstream::failbit | ifstream::badbit);

    str_buf = (char *) calloc(STR_BUF_SIZE + 1, sizeof(char));
    
    try {
        infile.open(file_name->c_str(), ios::in);

        while (!infile.eof()) {
            infile.getline(str_buf, STR_BUF_SIZE);

            text->append(str_buf);

            if (!is_first_line) {
                text->push_back('\n');
            }

            is_first_line = false;
        }

        infile.close();
    }
    catch (ifstream::failure err) {
        cerr << "Error: Exception opening/reading/closing file: " << err.what()
            << endl;

        return false;
    }

    free(str_buf);

    if (text->size() == 0)
        return false;

    return true;
}

int main() {
    string file_name;
    string question;
    string answer;
    string players_answer;
    string offset;
    uint32_t players_score = 0;
    uint32_t tv_viewers_score = 0;
    uint32_t curr_sector = START_SECTOR;
    uint32_t unavailable_sectors[NUM_SECTORS];

    std::memset(unavailable_sectors, 0, sizeof(uint32_t) * NUM_SECTORS);

    while (players_score < WIN_SCORES && tv_viewers_score < WIN_SCORES) {
        cout << "Enter how many sectors the game reel has spun: ";
        getline(cin, offset);

        curr_sector = get_sector(&curr_sector, unavailable_sectors,
                    static_cast<uint32_t>(std::stoul(offset, nullptr, 10)));

        if (curr_sector == 0) {
            cerr << "The sector is not defined" << endl;

            return 1;
        }

        unavailable_sectors[curr_sector - MIN_SECTOR] = 1;

        get_file_name(&file_name, &curr_sector, false);

        if (!read_file(&file_name, &question)) {
            cerr << "Impossible to read the question" << endl;

            return 1;
        }

        get_file_name(&file_name, &curr_sector, true);

        if (!read_file(&file_name, &answer)) {
            cerr << "Impossible to read the question" << endl;

            return 1;
        }

        cout << "Question:" << endl;
        cout << question << endl << endl;

        cout << "Enter the answer to the question: ";
        getline(cin, players_answer);

        if (players_answer == answer) {
            cout << "The answer is correct!" << endl;

            players_score++;
        } else {
            cout << "The answer is wrong!" << endl;

            tv_viewers_score++;
        }

        cout << "The current score in the game" << endl;
        cout << "Players: " << players_score << endl;
        cout << "TV Viewers: " << tv_viewers_score << endl << endl;;

        players_answer.clear();
    }

    if (players_score > tv_viewers_score)
        cout << "The players won." << endl;
    else
        cout << "The TV viewers won." << endl;

    return 0;
}