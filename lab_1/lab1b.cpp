#include <iostream>
#include <string>
#include <fstream>
#include <vector>

class Auto {
protected:
    std::string name;
    std::string model;

public:
    Auto(const std::string& model) {
        this->model = model;
    }

    virtual ~Auto() {
        std::cout << "Automobile: " << name << "-" << model << "\n";
    }
};

class Audi : public Auto {
public:
    Audi(const std::string& model): Auto(model) {
        name = "Audi";
    }

    virtual ~Audi() = default;
};

class Kia : public Auto {
public:
    Kia(const std::string& model): Auto(model) {
        name = "Kia";
    }

    virtual ~Kia() = default;
};

class Hyundai : public Auto {
public:
    Hyundai(const std::string& model): Auto(model) {
        name = "Hyundai";
    }

    virtual ~Hyundai() = default;
};

int main() {
    std::ifstream file("automobiles.txt");
    std::vector<Auto *> automobiles;

    int linesCount = 0;
    if (file.is_open()) {
        std::string temp;
        while (std::getline(file, temp)) linesCount++;
        file.close();
    } else {
        std::cerr << "Unable to open file" << "\n";
    }

    file.open("automobiles.txt");
    for (int i = 0; i < linesCount; i++) {
        std::string automobile;
        std::getline(file, automobile);
        std::string name, model;
        bool spaceFound = false;
        for (int i = 0; i < automobile.size(); i++) {
            if (automobile[i] == ' ') {
                spaceFound = true;
                continue;
            }
            if (!spaceFound) name += automobile[i];
            else model += automobile[i];
        }
        if (name == "Audi") automobiles.push_back(&Audi(model));
        if (name == "Kia") automobiles.push_back(&Kia(model));
        if (name == "Hyundai") automobiles.push_back(&Hyundai(model));
    }
    for (int i = 0; i < automobiles.size(); i++) delete automobiles[i];
    return 0;
}
