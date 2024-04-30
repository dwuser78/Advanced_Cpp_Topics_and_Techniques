#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include <map>

#define IN_FILE "payroll.txt"
#define STR_BUF_SIZE 1023

using namespace std;

enum table_fields
{
    FIRST_NAME,
    LAST_NAME,
    SALARY = 0,
    DATE,
    NUM_FIELDS = 4
};

bool read_payroll(const string *file_name,
                  map<string, vector<string>> *data_map) {
    ifstream infile;
    char *str_buf;
    char *word_buf;
    int32_t fields;
    size_t lines = 0;
    string person_name;
    vector<string> personal_data;

    infile.exceptions (ifstream::failbit | ifstream::badbit);

    try {
        infile.open(file_name->c_str(), ios::in);
    }
    catch (ifstream::failure err) {
        cerr << "Error: Exception opening file: " << err.what() << endl;

        return false;
    }

    str_buf = (char *) calloc(STR_BUF_SIZE + 1, sizeof(char));

    while (!infile.eof()) {
        fields = 0;

        try {
            infile.getline(str_buf, STR_BUF_SIZE);
        }
        catch (ifstream::failure err) {
            cerr << "Error: Exception reading file: " << err.what() << endl;

            return false;
        }

        word_buf = std::strtok (str_buf, " ");

        while (word_buf != nullptr) {
            if (fields == FIRST_NAME) {
                person_name.append(word_buf);
                person_name.append(" ");
            } else if (fields == LAST_NAME) {
                person_name.append(word_buf);
            } else {
                personal_data.push_back(word_buf);
            }

            word_buf = std::strtok (nullptr, " ");

            fields++;
        }

        if (fields == NUM_FIELDS) {
            (*data_map)[person_name] = personal_data;
        } else if (fields != 0) {
            cerr << "Error: invalid number of fields in line " << lines << endl;

            return false;
        }

        person_name.clear();
        personal_data.clear();
        lines++;
    }

    free(str_buf);
    free(word_buf);

    try {
        infile.close();
    }
    catch (ifstream::failure err) {
        cerr << "Error: Exception closing file: " << err.what() << endl;

        return false;
    }

    return true;
}

void print_salary_stat(map<string, vector<string>> *data_map) {
    uint32_t max_salary = 0;
    uint32_t curr_salary = 0;
    uint32_t total_salary = 0;
    string max_salary_name;
    map<string, vector<string>>::iterator data_map_it;

    data_map_it = data_map->begin();

    while(data_map_it != data_map->end()) {
        curr_salary = static_cast<uint32_t>(
            std::stoul(data_map_it->second[SALARY], nullptr, 10));

        if (curr_salary > max_salary) {
            max_salary = curr_salary;
            max_salary_name = data_map_it->first;
        }

        total_salary += curr_salary;
        data_map_it++;
    }

    if (max_salary_name.size() == 0) {
        cout << "No data found" << endl;

        return;
    } else {
        cout << "Max salary: " << max_salary_name << " " << max_salary << endl;
        cout << "Total salary: " << total_salary << endl;
    }
}

int main() {
    string file_name = IN_FILE;
    map<string, vector<string>> *data_map;

    data_map = new map<string, vector<string>>();

    if (read_payroll(&file_name, data_map))
        print_salary_stat(data_map);

    delete(data_map);

    return 0;
}