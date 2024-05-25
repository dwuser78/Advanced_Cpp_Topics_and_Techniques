#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

#define MAX_TREES 5

using namespace std;

class Elf {
private:
    string name;

public:
    Elf(const string *n) {
      this->name = *n;
    }

    const string getName() const {
        return this->name;
    }
};

class Branch {
private:
    Branch *parent = nullptr;
    vector<Branch *> children;
    vector<Elf *> elves;
    string name;

public:
    Branch() {}

    Branch(Branch *branch) {
        this->parent = branch;
    }

    ~Branch() {
        for (Branch *branch : this->children)
            delete (branch);
        
        for (Elf *elf : this->elves)
            delete (elf);
    }

    void addChild(Branch *branch) {
        this->children.push_back(branch);
    }

    const vector<Branch*> *getChild() {
        return &this->children;
    }

    void setName(string name) {
        this->name = name;
    }

    string *getName() {
        return &this->name;
    }

    void addElf(string name) {
        this->elves.push_back(new Elf(&name));
    }

    const vector<Elf*> *getElfes() {
        return &this->elves;
    }

    bool findElfName(string *name) {
        for (Elf *elf: this->elves) {
            if (elf->getName() == *name)
                return true;
        }

        return false;
    }

};

bool findElf(vector<Branch *> *trees, string *name) {
    for (Branch *tree : *trees) {
        for (Branch *bigBranch : *tree->getChild()) {
            if (bigBranch->findElfName(name)) {
                cout << "Elf " << *name << " was found at:" << endl;
                cout << *tree->getName() << endl;
                cout << *bigBranch->getName() << endl;
                cout << "Neighbors: " << bigBranch->getElfes()->size();

                return true;
            }
            for (Branch *mediumBranch : *bigBranch->getChild()) {
                if (mediumBranch->findElfName(name)) {
                    cout << "Elf " << *name << " was found at:" << endl;
                    cout << *tree->getName() << endl;
                    cout << *bigBranch->getName() << endl;
                    cout << *mediumBranch->getName() << endl;
                    cout << "Neighbors: " << bigBranch->getElfes()->size();

                    return true;
                }
            }
        }
    }

    return false;
}

int main() {
    vector<Branch *> trees;
    uint32_t numBigBranches;
    uint32_t numMediumBranches;
    string name;

    srand(time(nullptr));

    for (int i = 0; i < MAX_TREES; i++) {
        Branch *new_tree = new Branch();
        trees.push_back(new_tree);

        new_tree->setName("Tree #" + to_string(i + 1));

        numBigBranches = rand() % 3 + 3; // from 3 to 5

        for (int j = 0; j < numBigBranches; j++) {
            Branch *newBigBranch = new Branch(new_tree);
            new_tree->addChild(newBigBranch);

            newBigBranch->setName("Big Branch #" + to_string(j + 1));

            cout << "In a house located on:" << endl;
            cout << *new_tree->getName() << endl;
            cout << *newBigBranch->getName() << endl;
            cout << "Will live an elf (enter name or 'None'): ";
            getline (cin, name);

            if (name == "None")
                continue;

            newBigBranch->addElf(name);

            numMediumBranches = rand() % 2 + 2; // from 2 to 3

            for (int k = 0; k < numMediumBranches; k++) {
                Branch *newMediumBranch = new Branch(newBigBranch);
                newBigBranch->addChild(newMediumBranch);

                newMediumBranch->setName("Medium Branch #" + to_string(k + 1));

                cout << "In a house located on:" << endl;
                cout << *new_tree->getName() << endl;
                cout << *newBigBranch->getName() << endl;
                cout << *newMediumBranch->getName() << endl;
                cout << "Will live an elf (enter name or 'None'): ";
                getline (cin, name);

                if (name == "None")
                    continue;

                newMediumBranch->addElf(name);
            }
        }
    }

    cout << "Enter the name of the elf you are looking for: ";
    getline (cin, name);

    findElf(&trees, &name);

    for (Branch *tree : trees)
        delete (tree);

    return 0;
}