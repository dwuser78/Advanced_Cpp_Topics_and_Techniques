#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

#define OUT_FILE "pic.txt"

using namespace std;

bool input_data(uint32_t *width, uint32_t *height) {
    string width_str;
    string height_str;

    cout << "Enter the width of the image: ";
      std::getline (cin, width_str);

    if (width_str.length() == 0 || width_str == " ") {
        cerr << "The width of the image was entered incorrectly." << endl;

        return false;
    }

    cout << "Enter the height of the image: ";
      std::getline (cin, height_str);

    if (height_str.length() == 0 || height_str == " ") {
        cerr << "The height of the image was entered incorrectly." << endl;

        return false;
    }

    try {
        *width = static_cast<uint32_t>(stoul(width_str));
        *height = static_cast<uint32_t>(stoul(height_str));
    }
    catch (const invalid_argument& err){
        cerr << "The size was entered incorrectly." << endl;
        cerr << "Invalid argument: " << err.what() << endl;

        return false;
    }
    catch (const out_of_range& err) {
        cerr << "The size was entered incorrectly." << endl;
        cerr << "Out of Range error: " << err.what() << endl;

        return false;
    }

    return true;
}

bool write_data(const string *file_name, const uint32_t *width,
                const uint32_t *height, string *output_line) {
    ofstream outfile;

    if (file_name->length() == 0) {
        cerr << "The file name was entered incorrectly." << endl;

        return false;
    }

    outfile.exceptions (ifstream::failbit | ifstream::badbit);

    try {
        outfile.open(file_name->c_str(), ios::out | ios::app);

        for (uint32_t i = 0; i < *height; i++) {
            output_line->clear();

            for (uint32_t i = 0; i < *width; i++)
                *output_line += (rand() % 2 == 0) ? "0" : "1";

            outfile.write(output_line->c_str(), output_line->length());
        }

        outfile.close();
    }
    catch (ifstream::failure err) {
        cerr << "Exception opening/writing/closing file: " << err.what()
            << endl;

        return false;
    }

    return true;
}

int main() {
    uint32_t width = 0;
    uint32_t height = 0;
    string *output_line;
    string file_name = OUT_FILE;

    output_line = new string();

    if (input_data(&width, &height)) {
        if (!write_data(&file_name, &width, &height, output_line))
            return 1;
    }

    return 0;
}