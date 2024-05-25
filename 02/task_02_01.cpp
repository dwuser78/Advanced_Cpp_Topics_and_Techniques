#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include <map>

#define OUT_FILE "payroll.out"
#define MIN_DAYS_PER_MONTH 1
#define MIN_MONTHS_PER_YEAR 1
#define MAX_DAYS_PER_MONTH 31
#define MAX_MONTHS_PER_YEAR 12

using namespace std;

enum table_fields
{
    FIRST_NAME,
    LAST_NAME,
    SALARY = 0,
    DATE,
    NUM_FIELDS = 4
};

bool verify_date (const string *date) {
    uint32_t day;
    uint32_t month;
    uint32_t year;

    if (date->length() != 10)
        return false;

    if (date->at(2) != '.' || date->at(5) != '.')
        return false;

    try {
        day = stoul (date->substr(0, 2));
        month = stoul (date->substr(3, 2));
        year = stoul (date->substr(6, 4));
    }
    catch (const invalid_argument& err){
        return false;
    }
    catch (const out_of_range& err) {
        return false;
    }

    if (day < MIN_DAYS_PER_MONTH || day > MAX_DAYS_PER_MONTH)
        return false;

    if (month < MIN_MONTHS_PER_YEAR || month > MAX_MONTHS_PER_YEAR)
        return false;

    if (year < 1000)
        return false;

    return true;
}

bool input_data(string *output_string) {
    string first_name;
    string last_name;
    string date;
    string salary;

    cout << "Eenter first name: ";
      std::getline (cin, first_name);

    if (first_name.length() == 0 || first_name == " ") {
        cerr << "The first name was entered incorrectly." << endl;

        return false;
    }

    cout << "Eenter last name: ";
      std::getline (cin, last_name);

    if (last_name.length() == 0 || last_name == " ") {
        cerr << "The last name was entered incorrectly." << endl;

        return false;
    }

    output_string->append(first_name);
    output_string->append(" ");
    output_string->append(last_name);

    cout << "Eenter date: ";
      std::getline (cin, date);

    if (!verify_date(&date)) {
        cerr << "The date was entered incorrectly." << endl;

        return false;
    }

    output_string->append(" ");
    output_string->append(date);

    cout << "Eenter salary: ";
      std::getline (cin, salary);

    try {
        stod (salary);
    }
    catch (const invalid_argument& err){
        cerr << "The salary was entered incorrectly." << endl;
        cerr << "Invalid argument: " << err.what() << endl;

        return false;
    }
    catch (const out_of_range& err) {
        cerr << "The salary was entered incorrectly." << endl;
        cerr << "Out of Range error: " << err.what() << endl;

        return false;
    }

    output_string->append(" ");
    output_string->append(salary);
    output_string->push_back('\n');

    return true;
}

bool write_data(const string *file_name, const string *output_string) {
    ofstream outfile;

    if (file_name->length() == 0) {
        cerr << "The file name was entered incorrectly." << endl;

        return false;
    }

    outfile.exceptions (ifstream::failbit | ifstream::badbit);

    try {
        outfile.open(file_name->c_str(), ios::out | ios::app);
        outfile.write(output_string->c_str(), output_string->length());
        outfile.close();
    }
    catch (ifstream::failure err) {
        cerr << "Exception opening/reading/closing file: " << err.what()
            << endl;

        return false;
    }

    return true;
}

int main() {
    string file_name = OUT_FILE;
    string *output_string;

    output_string = new string();

    if (input_data(output_string))
        write_data(&file_name, output_string);

    delete(output_string);

    return 0;
}