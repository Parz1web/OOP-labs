#include <iostream>
#include <string>
#include <vector>

class Detail {
public:
    std::string name = "Detail";

    virtual void displayInfo() {
        std::cout << "It's a Detail Class with args: " << name << "\n";
    }

    template<typename T, typename... Args>
    friend T *create(Args &&... args);

    template<typename T>
    friend void destroy(const T *obj);

protected:
    Detail() = default;

    Detail(const std::string &n) {
        name = n;
    };

    ~Detail() = default;
};

class Build : public Detail {
public:
    int buildId = 90127367;

    void displayInfo() override {
        std::cout << "It's a Build Class with args: " << buildId << "\n";
    }

    template<typename T, typename... Args>
    friend T *create(Args &&... args);

    template<typename T>
    friend void destroy(const T *obj);

protected:
    Build() = default;

    Build(const int &id) {
        buildId = id;
    }

    ~Build() = default;
};

template<typename T, typename... Args>
T *create(Args &&... args) {
    return new T(forward<Args>(args)...);
}

template<typename T>
void destroy(const T *obj) {
    delete obj;
}

int main() {
    std::vector<Detail *> db;
    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            db.push_back(create<Detail>("STRING-" + std::to_string(i)));
        } else {
            db.push_back(create<Build>(i));
        }
    }
    for (int i = 0; i < db.size(); i++) {
        db[i]->displayInfo();
        destroy(db[i]);
    }
    db.clear();
    return 0;
}