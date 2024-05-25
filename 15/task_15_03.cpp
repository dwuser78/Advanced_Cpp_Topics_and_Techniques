#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <typename KT, typename VT>
class Registry {
public:
    void add(const KT& key, const VT& value) {
        data.push_back(make_pair(key, value));
    }

    void remove(const KT& key) {
        auto it = data.begin();
        while (it != data.end()) {
            if (it->first == key)
                it = data.erase(it);
            else
                it++;
        }
    }

    void print() {
        for (const auto& pair : data) {
            cout << "Key: " << pair.first << ", Value: " << pair.second << endl;
        }
    }

    void find(const KT& key) {
        for (const auto& pair : data) {
            if (pair.first == key) {
                cout << "Key: " << pair.first << ", Value: " << pair.second
                    << endl;
            }
        }
    }

private:
    vector<pair<KT, VT>> data;
};

template<typename T>
void processInput(Registry<T, T> *registry) {
    T key;
    T value;
    string command;

    while (command != "exit") {
        cout << "Enter command or type 'exit' to exit: ";
        getline(cin, command);

        if (command == "add") {
            cout << "Enter KEY: ";
            cin >> key;

            cout << "Enter VALUE: ";
            cin >> value;

            cin.clear();
            cin.ignore();

            registry->add(key, value);
        }
        else if (command == "remove") {
            cout << "Enter KEY: ";
            cin >> key;

            cin.clear();
            cin.ignore();

            registry->remove(key);
        }
        else if (command == "print") {
            registry->print();
        }
        else if (command == "find") {
            cout << "Enter KEY: ";
            cin >> key;

            cin.clear();

            registry->find(key);
        }
    }
}

int main() {
    Registry<int, int> *intRegistry;

    intRegistry = new Registry<int, int>;

    processInput(intRegistry);

    delete intRegistry;

    return 0;
}
