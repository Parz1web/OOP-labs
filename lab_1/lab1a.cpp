#include <iostream>
#include <vector>
#include <crtdbg.h>
#include <string>

enum BookType { ARTISTIC, TECHNICAL };

struct Book {
    std::string author;
    std::string title;
    BookType type;
};

class Library {
private:
    std::vector<Book *> books;

public:
    Library(
        const std::string& author, 
        const std::string& title, 
        const BookType type
    ) {
        addBook(author, title, type);
    };

    ~Library() {
        for (int i = 0; i < books.size(); i++) delete books[i];
    }

    void addBook(
        const std::string& author, 
        const std::string& title, 
        const BookType type
    ) {
        if (author.empty() || title.empty()) return;
        books.push_back(new Book{author, title, type});
    }

    void displayBySwitch() {
        std::cout << "Display count of books by switch:\n";
        int aCount = 0, tCount = 0;
        for (int i = 0; i < books.size(); i++) {
            switch (books[i]->type) {
                case ARTISTIC:
                    aCount++;
                    break;
                case TECHNICAL:
                    tCount++;
                    break;
            }
        }
        std::cout << "\tArtistic books count: " << aCount << "\n";
        std::cout << "\tTechnical books count: " << tCount << "\n";
    }

    void display() {
        std::cout << "Display count of books:\n";
        int aCount = 0, tCount = 0;
        for (int i = 0; i < books.size(); i++) {
            if (books[i]->type == ARTISTIC) aCount++;
            if (books[i]->type == TECHNICAL) tCount++;
        }
        std::cout << "\tArtistic books count: " << aCount << "\n";
        std::cout << "\tTechnical books count: " << tCount << "\n";
    }
};

int main() {
    Library library("AUTHOR-0", "BOOK-0", ARTISTIC);
    for (int i = 0; i < 20; i++) {
        library.addBook("AUTHOR-" + std::to_string(i + 1), "BOOK-" + std::to_string(i + 1), i % 2 == 0 ? ARTISTIC : TECHNICAL);
    }
    library.display();
    library.displayBySwitch();
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtDumpMemoryLeaks();
    return 0;
}
