#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

enum taskType {
    A,
    B,
    C,
    ALL_TASKS
};

const static struct {
    taskType    val;
    const char *str;
} taskType2str[] = {
    {A, "A"},
    {B, "B"},
    {C, "C"}
};

class Employee {
public:
    Employee(const uint32_t id) : name(id) {}

    void workOnTask(uint32_t taskId, taskType tType) {
        cout << "Employee: " << this->name + 1 << " is working on a task: "
            << taskId + 1 << "(type: " << taskType2str[tType].str
            << ")" << endl;

        this->busy = true;
    }

    bool getStatus() {
        return this->busy;
    }

protected:
    uint32_t name;
    bool busy = false;
};

class Manager : public Employee {
public:
    Manager(const uint32_t id) : Employee(id) {}

    void workOnTask(uint32_t taskId, vector<vector<Employee *>> *workers) {
        uint32_t workersCnt;
        uint32_t taskCnt;
        uint32_t workersBusyCnt = 0;
        size_t currWorker = 0;

        cout << "Manager: " << this->name + 1 << " is working on a task: "
            << taskId << endl;

        srand(taskId + this->name);

        workersCnt = (*workers)[this->name].size();
        taskCnt = rand() % workersCnt;

        while (true) {
            if ((*workers)[this->name][currWorker]->getStatus()) {
                workersBusyCnt++;
            } else {
                (*workers)[this->name][currWorker]->
                  workOnTask(currWorker, taskType2str[rand() % ALL_TASKS].val);
            }

            if (workersBusyCnt == workersCnt - 1) {
                this->busy = true;
                break;
            }

            if (currWorker == taskCnt)
                break;

            currWorker++;
        }
    }
};

class Company {
public:
    Company(uint32_t teamsCount, uint32_t workersPerTeam) :
                teamsCount(teamsCount), workersPerTeam(workersPerTeam) {
        vector<Employee *> team;
        uint32_t workerId = 0;

        for (size_t i = 0; i < teamsCount; i++) {
            this->managers.push_back(new Manager(i));

            for (size_t j = 0; j < workersPerTeam; j++) {
                team.push_back(new Employee(workerId));
                workerId++;
            }

            this->workers.push_back(team);
            team.clear();
        }
    }

    ~Company() {
        for (size_t i = 0; i < this->teamsCount; i++) {
            delete this->managers[i];

            for (size_t j = 0; j < this->workersPerTeam; j++)
                delete this->workers[i][j];
        }
    }

    void createTask(uint32_t bossTaskId) {
        for (size_t i = 0; i < this->teamsCount; i++) {
            this->managers[i]->workOnTask(bossTaskId, &this->workers);

            if (managers[i]->getStatus())
                this->teamsBusyCnt++;
        }

        if (teamsBusyCnt == teamsCount)
            this->owerload = true;
    }

    bool checkOverload() {
        return this->owerload;
    }

private:
    vector<vector<Employee *>> workers;
    vector<Manager *> managers;
    uint32_t teamsCount;
    uint32_t workersPerTeam;
    uint32_t teamsBusyCnt = 0;
    bool owerload = false;
};

int main() {
    string teamsCount;
    string workersPerTeam;
    string taskId;
    Company *company;

    cout << "Enter the number of teams: ";
    getline (cin, teamsCount);

    cout << "Enter the number of workers per team: ";
    getline (cin, workersPerTeam);

    company = new Company(static_cast<uint32_t>(std::stoul(teamsCount)),
                          static_cast<uint32_t>(std::stoul(workersPerTeam)));

    while (true) {
        cout << "Enter the task ID: ";
        getline (cin, taskId);

        company->createTask(static_cast<uint32_t>(std::stoul(taskId)));

        if (company->checkOverload())
            break;
    }

    delete company;

    return 0;
}