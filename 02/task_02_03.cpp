#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

#define IN_FILE "river.txt"
#define OUT_FILE "basket.txt"
#define STR_BUF_SIZE 1023

using namespace std;

bool find_fish(const string *in_file_name, const string *fish_name) {
    ifstream in_file;
    bool fish_found = false;
    char *str_buf;

    if (in_file_name->length() == 0) {
        cerr << "The file name was entered incorrectly." << endl;

        return false;
    }

    if (fish_name->length() == 0) {
        cerr << "The fish name was entered incorrectly." << endl;

        return false;
    }

    in_file.exceptions (ifstream::failbit | ifstream::badbit);

    try {
        in_file.open(in_file_name->c_str(), ios::in);
    }
    catch (ifstream::failure err) {
        cerr << "Error: Exception opening file: " << err.what() << endl;

        return false;
    }

    str_buf = (char *) calloc(STR_BUF_SIZE + 1, sizeof(char));

    while (!in_file.eof()) {

        try {
            in_file.getline(str_buf, STR_BUF_SIZE);
        }
        catch (ifstream::failure err) {
            cerr << "Error: Exception reading file: " << err.what() << endl;

            return false;
        }

        if (strcmp(fish_name->c_str(), str_buf) == 0) {
            fish_found = true;

            break;
        }
    }

    free(str_buf);

    try {
        in_file.close();
    }
    catch (ifstream::failure err) {
        cerr << "Error: Exception closing file: " << err.what() << endl;

        return false;
    }

    return fish_found;
}

bool put_in_basket(const string *out_file_name, const string *fish_name) {
    ofstream out_file;

    if (out_file_name->length() == 0) {
        cerr << "The file name was entered incorrectly." << endl;

        return false;
    }

    if (fish_name->length() == 0) {
        cerr << "The fish name was entered incorrectly." << endl;

        return false;
    }

    out_file.exceptions (ifstream::failbit | ifstream::badbit);

    try {
        out_file.open(out_file_name->c_str(), ios::out | ios::app);

        out_file.write(fish_name->c_str(), fish_name->length());
        out_file.write("\n", sizeof(char));

        out_file.close();
    }
    catch (ifstream::failure err) {
        cerr << "Exception opening/writing/closing file: " << err.what()
            << endl;

        return false;
    }

    return true;
}

int main() {
    string in_file_name = IN_FILE;
    string out_file_name = OUT_FILE;
    string fish_name;

    cout << "What kind of fish are we catching: ";
        std::getline (cin, fish_name);

    if (fish_name.length() == 0) {
        cerr << "The fish name was entered incorrectly." << endl;

        return 1;
    }

    if (find_fish(&in_file_name, &fish_name)) {
        if (put_in_basket(&out_file_name, &fish_name)) {
            cout << "The fish is caught!" << endl;
        }
    } else {
        cout << "They didn't catch anything :(" << endl;
    }

    return 0;
}