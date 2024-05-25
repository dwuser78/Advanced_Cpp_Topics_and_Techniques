#include <iostream>
#include <string>
#include <cstring>
#include <map>
#include <vector>

#define STR_BUF_SIZE 1023

using namespace std;

enum part_names
{
    COMMAND,
    ARG1,
    ARG2,
    NUM_NAMES
};

void fill_database(map<string, uint32_t> *warehouse) {
    string item_code;
    string tmp;
    uint32_t item_count;
    map<string, uint32_t>::iterator it;

    cout << "Fill in the product database." << endl;
    cout << "To stop typing, enter 'end'." << endl;

    while (true) {
        cout << "Enter the item code: ";
        getline(cin, item_code);

        if (item_code.length() == 0)
            throw invalid_argument("The item code should not be empty.");

        if (item_code == "end")
            break;

        it = warehouse->find(item_code);

        if (it != warehouse->end()) {
            throw invalid_argument("Such a item already exists.");
        }

        cout << "Enter the item count: ";
        getline(cin, tmp);

        try {
            item_count = static_cast<uint32_t>(std::stoul(tmp, nullptr, 10));
        }
        catch (const invalid_argument& err){
            throw invalid_argument("Incorrect count value.");
        }

        (*warehouse)[item_code] = item_count;
    }
}

void add_item(map<string, uint32_t> *warehouse,
              map<string, uint32_t> *shopping_cart,
              pair<string, uint32_t> *command_args) {
    map<string, uint32_t>::iterator it;

    it = warehouse->find(command_args->first);

    if (it == warehouse->end())
        throw invalid_argument("Unknown item.");

    if ((*warehouse)[command_args->first] < command_args->second)
        throw invalid_argument("Incorrect quantity of the item.");

    (*warehouse)[command_args->first] -= command_args->second;

    it = shopping_cart->find(command_args->first);

    if (it != shopping_cart->end()) {
        (*shopping_cart)[command_args->first] += command_args->second;
    } else {
        (*shopping_cart)[command_args->first] = command_args->second;
    }
}

void remove_item(map<string, uint32_t> *warehouse,
                 map<string, uint32_t> *shopping_cart,
                 pair<string, uint32_t> *command_args) {
    map<string, uint32_t>::iterator it;

    it = shopping_cart->find(command_args->first);

    if (it == shopping_cart->end())
        throw invalid_argument("Unknown item.");

    if ((*shopping_cart)[command_args->first] < command_args->second)
        throw invalid_argument("Incorrect quantity of the item.");

    (*shopping_cart)[command_args->first] -= command_args->second;

    (*warehouse)[command_args->first] += command_args->second;
}

void input_command(map<string, uint32_t> *warehouse,
                   map<string, uint32_t> *shopping_cart) {
    char *command_part;
    char *str_buf;
    vector<string> command_parts;
    pair<string, uint32_t> command_args;

    cout << endl << "Fill in the shopping cart." << endl;
    cout << "Commands:" << endl;
    cout << "add <item> <count> - adding an item of <item> to the cart in "
        "quantity of <count>." << endl;
    cout << "remove <item> <count> - removing an item of <item> from the "
        "shopping cart in quantity of <count>." << endl;
    cout << "end - completing the shopping cart." << endl << endl;

    while (true) {
        str_buf = (char *) calloc(STR_BUF_SIZE + 1, sizeof(char));

        cout << "Shopping cart: ";
        cin.getline(str_buf, STR_BUF_SIZE);

        command_part = std::strtok (str_buf, " ");

        while (command_part != nullptr) {
            command_parts.push_back(command_part);
            command_part = std::strtok (nullptr, " ");
        }

        free(str_buf);

        if (command_parts[COMMAND] == "end") 
            break;

        if (command_parts.size() != NUM_NAMES)
            throw invalid_argument("Incorrect command format.");

        command_args.first = command_parts[ARG1];

        try {
            command_args.second = static_cast<uint32_t>(std::stoul(
                                            command_parts[ARG2], nullptr, 10));
        }
        catch (const invalid_argument& err) {
            throw invalid_argument("Incorrect count value.");
        }

        if (command_parts[COMMAND] == "add")
            add_item(warehouse, shopping_cart, &command_args);
        else if (command_parts[COMMAND] == "remove")
            remove_item(warehouse, shopping_cart, &command_args);
        else
            throw invalid_argument("Unknown command.");

        command_parts.clear();
    }
}

void print_items_info(map<string, uint32_t> *warehouse,
                      map<string, uint32_t> *shopping_cart) {
    map<string, uint32_t>::iterator it;

    cout << endl << "Warehouse (Item Code - Item Count):" << endl;
    cout << "--------------------------------" << endl;
    it = warehouse->begin();
    while (it != warehouse->end()){
        cout << it->first << " - " << it->second << endl;
        it++;
    }

    cout << endl << "Shopping Cart (Item Code - Item Count):" << endl;
    cout << "--------------------------------" << endl;
    it = shopping_cart->begin();
    while (it != shopping_cart->end()){
        cout << it->first << " - " << it->second << endl;
        it++;
    }
}

int main() {
    map<string, uint32_t> *warehouse;
    map<string, uint32_t> *shopping_cart;

    warehouse = new map<string, uint32_t>();
    shopping_cart = new map<string, uint32_t>();

    try {
        fill_database(warehouse);
        input_command(warehouse, shopping_cart);
    }
    catch (const invalid_argument& err){
        cerr << "Invalid argument: " << err.what() << endl;

        return 1;
    }
    catch (const out_of_range& err) {
        cerr << "Out of Range error: " << err.what() << endl;

        return 1;
    }

    print_items_info(warehouse, shopping_cart);

    delete(warehouse);
    delete(shopping_cart);

    return 0;
}