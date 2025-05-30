#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <functional>
#include <algorithm>
using namespace std;

struct Employee {
    string name;
    string birthYear;
    string profession;
    string structure;
};

auto split = [](string baseString, const string separator) {
    vector<string> splittedValue;
    baseString += separator;
    while (!baseString.empty()) {
        auto index = baseString.find(separator);
        splittedValue.push_back(baseString.substr(0, index));
        baseString = baseString.replace(0, index + separator.size(), "");
    }
    return splittedValue;
};

auto sortAscendingByBirthYear = [](Employee e1, Employee e2) {
    return e1.birthYear < e2.birthYear;
};

auto isEngeneer = [](Employee e) {
    return e.profession == "engineer";
};

auto isNotChairman = [](Employee e) {
    return e.profession != "chairman";
};

class BD {
private:
    vector<Employee> employees;
    string fileName;

    vector<Employee> getSorted(vector<Employee> arr, function<bool(Employee, Employee)> sortFunction) {
        auto a = arr;
        sort(a.begin(), a.end(), sortFunction);
        return a;
    }

    vector<Employee> getWithExpetions(vector<Employee> arr, const vector<function<bool(Employee)> > exeptions) {
        auto a = arr;
        a.erase(remove_if(a.begin(), a.end(), [&](const Employee &e) {
            for (auto &ex: exeptions) if (!ex(e)) return true;
            return false;
        }), a.end());
        return a;
    }

    void display(vector<Employee> arr) {
        for (auto employee: arr) {
            cout << "Employee: " << endl;
            cout << '\t' << employee.name << endl;
            cout << '\t' << employee.birthYear << endl;
            cout << '\t' << employee.profession << endl;
            cout << '\t' << employee.structure << endl;
        }
    }

public:
    BD(string fName) {
        fileName = fName;
        loadFile();
    };

    void loadFile() {
        ifstream file(fileName);
        if (!file.is_open()) return;
        employees.clear();
        string line;
        while (getline(file, line)) {
            auto employeeData = split(line, ", ");
            if (employeeData.size() < 4) continue;
            employees.push_back(Employee{employeeData[0], employeeData[1], employeeData[2], employeeData[3]});
        }
    };

    void display(function<bool(Employee, Employee)> sortFunction, vector<function<bool(Employee)> > exeptions) {
        display(getSorted(getWithExpetions(employees, exeptions), sortFunction));
    }

    void display(vector<function<bool(Employee)> > exeptions) {
        display(getWithExpetions(employees, exeptions));
    }

    void display(function<bool(Employee, Employee)> sortFunction) {
        display(getSorted(employees, sortFunction));
    }

    ~BD() = default;
};

int main() {
    BD db("data.txt");
    cout << "Engeneers: \n";
    db.display({isEngeneer});

    cout << "\nNot chairmans with ascending sort: \n";
    db.display(sortAscendingByBirthYear, {isNotChairman});
    return 0;
}
