#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <functional>
#include <algorithm>
using namespace std;

auto sortAscending = [](string s1, string s2) {
    return s1 < s2;
};

class BD {
private:
    vector<string> references_ru;
    vector<string> references_en;
    string fileName;

    vector<string> getSorted(vector<string> arr, function<bool(string, string)> sortFunction) {
        auto a = arr;
        sort(a.begin(), a.end(), sortFunction);
        return a;
    }

    void display(vector<string> arr, bool withNumber) {
        for (int i = 0; i < arr.size(); i++) {
            cout << (withNumber ? to_string(i + 1) + ".\t" : "") << arr[i] << endl;
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
        references_ru.clear();
        references_en.clear();
        string line;
        string number;
        while (getline(file, line)) {
            auto index = line.find(".") + 2;
            auto str = line.substr(index, line.size() - index);
            if (str[0] > 65 && str[0] < 122) references_en.push_back(str);
            else references_ru.push_back(str);
        }
    };

    void display(function<bool(string, string)> sortFunction, bool withNumber) {
        vector<string> commonArr = getSorted(references_ru, sortFunction);
        for (auto el : getSorted(references_en, sortFunction)) commonArr.push_back(el);
        display(commonArr, withNumber);
    }

    ~BD() = default;
};

int main() {
    setlocale(LC_ALL, "Russian");
    BD db("data.txt");
    cout << "References with numbers: \n";
    db.display(sortAscending, true);

    cout << "\nReferences: \n";
    db.display(sortAscending, false);
    return 0;
}