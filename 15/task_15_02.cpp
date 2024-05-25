#include <iostream>
#include <vector>
#include <string>

#define LAKE_SIZE 9
#define NUM_FISH 1
#define NUM_BOOTS 3

using namespace std;

enum catch_types
{
    NOTHING,
    FISH,
    BOOT,
    NUM_CATCH_TYPES
};

class FishException {
public:
    FishException() {}

    FishException(string msg) : err(msg) {}

    string what() const {
        return this->err;
    }

private:
    string err;
};

class BootException {
public:
    BootException() {}

    BootException(string msg) : err(msg) {}

    string what() const {
        return this->err;
    }

private:
    string err;
};

void fillLake(vector<uint32_t> *lake) {
    srand(time(nullptr));

    for (size_t i = 0; i < NUM_FISH; i++) {
        while (true) {
            uint32_t index = rand() % lake->size();

            if ((*lake)[index] == NOTHING) {
                (*lake)[index] = FISH;

                break;
            } else {
                continue;
            }
        }
    }

    for (size_t i = 0; i < NUM_BOOTS; i++) {
        while (true) {
            uint32_t index = rand() % lake->size();

            if ((*lake)[index] == NOTHING) {
                (*lake)[index] = BOOT;

                break;
            } else {
                continue;
            }
        }
    }
}

void  castFishingRod(const vector<uint32_t> *lake, const uint32_t *sector) {
    if ((*lake)[*sector] == FISH)
        throw FishException("You caught a fish!");
    else if ((*lake)[*sector] == BOOT)
        throw BootException("You caught a boot!");
    else
        return;
}

int main() {
    vector<uint32_t> *lake;
    string str_input;
    uint32_t sector;
    uint32_t attempts = 0;

    lake = new vector<uint32_t>(LAKE_SIZE, NOTHING);

    fillLake(lake);

    for (uint32_t i : *lake)
        cout << i << "";

    try {
        while (true) {
            attempts++;

            if (attempts >= lake->size()) {
                cout << "You have no more attempts!" << endl;

                break;
            }

            cout << "Enter the sector where you are casting your fishing rod (0-"
                << lake->size() - 1 << "): ";
            getline(cin, str_input);

            sector = static_cast<uint32_t>(std::stoul(str_input));

            if (sector >= lake->size()) {
                cout << "Invalid sector!" << endl;

                return 1;
            }

            castFishingRod(lake, &sector);

            cout << "You didn't catch anything." << endl;
        }
    }
    catch(const FishException& err) {
            cout << err.what() << endl;
            cout << "For the number of attempts: " << attempts << endl;
    }
    catch(const BootException& err) {
            cout << err.what() << endl;
    }

    delete lake;

    return 0;
}