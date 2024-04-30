#include <iostream>
#include <string>
#include <fstream>

#define STR_BUF_SIZE 1024

using namespace std;

int main() {
    string file_name;
    ifstream infile;
    char *str_buf;

    str_buf = (char *) calloc(STR_BUF_SIZE, sizeof(char));

    infile.exceptions (ifstream::failbit | ifstream::badbit);

    cout << "Enter the file name: ";
    getline(cin, file_name);

    try {
        infile.open(file_name, ios::binary | ios::in);

        while (!infile.eof()) {
            infile.getline(str_buf, STR_BUF_SIZE);
            cout << str_buf << endl;
        }

        infile.close();
    }
    catch (ifstream::failure err) {
        cerr << "Error: Exception opening/reading/closing file: " << err.what()
            << endl;

        return 1;
    }

    free(str_buf);

    return 0;
}