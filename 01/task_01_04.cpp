#include <iostream>
#include <string>
#include <fstream>

#define HEADER_SIZE_BYTE 4

using namespace std;

int main() {
    string file_name;
    ifstream infile;
    char byte_buf;
    const int8_t header_template[HEADER_SIZE_BYTE] = {-119, 80, 78, 71};

    infile.exceptions (ifstream::failbit | ifstream::badbit);

    cout << "Enter the file name: ";
    getline(cin, file_name);

    try {
        infile.open(file_name, ios::binary | ios::in);

        for (size_t i = 0; i < HEADER_SIZE_BYTE; i++) {
            infile.get(byte_buf);

            if (static_cast<int8_t>(byte_buf) != header_template[i]) {
                cout << "This is not a PNG file." << endl;

                return 0;
            }

            if (infile.eof()) {
                cerr << "Error: Unexpected end of file" << endl;

                return 1;
            }
        }

        infile.close();
    }
    catch (ifstream::failure err) {
        cerr << "Error: Exception opening/reading/closing file: " << err.what()
            << endl;

        return 1;
    }

    cout << "This is a PNG file." << endl;

    return 0;
}