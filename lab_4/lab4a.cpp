#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <functional>
#include <algorithm>

struct Employee {
    std::string name;
    std::string birthYear;
    std::string profession;
    std::string structure;
};

auto split = [](std::string& baseString, const std::string& separator) {
    std::vector<std::string> splittedValue;
    baseString += separator;
    while (!baseString.empty()) {
        auto index = baseString.find(separator);
        splittedValue.push_back(baseString.substr(0, index));
        baseString = baseString.replace(0, index + separator.size(), "");
    }
    return splittedValue;
};

auto sortAscendingByBirthYear = [](const Employee& e1, Employee& e2) {
    return e1.birthYear < e2.birthYear;
};

auto isEngeneer = [](const Employee& e) {
    return e.profession == "engineer";
};

auto isNotChairman = [](const Employee& e) {
    return e.profession != "chairman";
};

class BD {
private:
    std::vector<Employee> employees;
    std::string fileName;

    std::vector<Employee> getSorted(std::vector<Employee> arr, std::function<bool(Employee, Employee)> sortFunction) {
        auto a = arr;
        sort(a.begin(), a.end(), sortFunction);
        return a;
    }

    std::vector<Employee> getWithExpetions(std::vector<Employee> arr, const std::vector<std::function<bool(Employee)> > exeptions) {
        auto a = arr;
        a.erase(remove_if(a.begin(), a.end(), [&](const Employee &e) {
            for (auto &ex: exeptions) if (!ex(e)) return true;
            return false;
        }), a.end());
        return a;
    }

    void display(std::vector<Employee>& arr) {
        for (auto employee: arr) {
            std::cout << "Employee: " << "\n";
            std::cout << '\t' << employee.name << "\n";
            std::cout << '\t' << employee.birthYear << "\n";
            std::cout << '\t' << employee.profession << "\n";
            std::cout << '\t' << employee.structure << "\n";
        }
    }

public:
    BD(const std::string& fName) {
        fileName = fName;
        loadFile();
    };

    void loadFile() {
        std::ifstream file(fileName);
        if (!file.is_open()) return;
        employees.clear();
        std::string line;
        while (std::getline(file, line)) {
            auto employeeData = split(line, ", ");
            if (employeeData.size() < 4) continue;
            employees.push_back(Employee{employeeData[0], employeeData[1], employeeData[2], employeeData[3]});
        }
    };

    void display(std::function<bool(Employee, Employee)> sortFunction, std::vector<std::function<bool(Employee)> > exeptions) {
        display(getSorted(getWithExpetions(employees, exeptions), sortFunction));
    }

    void display(std::vector<std::function<bool(Employee)> > exeptions) {
        display(getWithExpetions(employees, exeptions));
    }

    void display(std::function<bool(Employee, Employee)> sortFunction) {
        display(getSorted(employees, sortFunction));
    }

    ~BD() = default;
};

int main() {
    BD db("data.txt");
    std::cout << "Engeneers: \n";
    db.display({isEngeneer});

    std::cout << "\nNot chairmans with ascending sort: \n";
    db.display(sortAscendingByBirthYear, {isNotChairman});
    return 0;
}
