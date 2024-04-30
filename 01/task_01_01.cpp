#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

#define IN_FILE "words.txt"
#define STR_BUF_SIZE 1023

using namespace std;

int main() {
    ifstream infile;
    char *str_buf;
    char *word_buf;
    string search_word;
    uint32_t words_found = 0;

    cout << "Enter the word you are looking for: ";
    getline(cin, search_word);

    str_buf = (char *) calloc(STR_BUF_SIZE + 1, sizeof(char));

    infile.exceptions (ifstream::failbit | ifstream::badbit);
    
    try {
        infile.open(IN_FILE, ios::in);

        while (!infile.eof()) {
            infile.getline(str_buf, STR_BUF_SIZE);

            word_buf = std::strtok (str_buf, " ");

            while (word_buf != nullptr) {
                if (strcmp(search_word.c_str(), word_buf) == 0)
                    words_found++;

                word_buf = std::strtok (nullptr, " ");
            }
        }

        infile.close();
    }
    catch (ifstream::failure err) {
        cerr << "Error: Exception opening/reading/closing file: " << err.what()
            << endl;

        return 1;
    }

    cout << "Found " << words_found << " words" << endl;

    free(str_buf);
    free(word_buf);
    

    return 0;
}