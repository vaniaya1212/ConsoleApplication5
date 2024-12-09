#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>


using namespace std;

enum class SourceType {
    BOOK,
    MAGAZINE,
    NEWSPAPER
};

class Source {
private:
    SourceType type;
    string title;
    string author;
    string category;
    int year;

public:
    Source(SourceType type, const string& title, const string& author = "", const string& category = "", int year = 0)
        : type(type), title(title), author(author), category(category), year(year) {}

    SourceType getType() const { return type; }
    const string& getTitle() const { return title; }
    const string& getAuthor() const { return author; }
    const string& getCategory() const { return category; }
    int getYear() const { return year; }

    void display() const {
        cout << "���: " << (type == SourceType::BOOK ? "�����" : (type == SourceType::MAGAZINE ? "������" : "������")) << "\n"
            << "�����: " << title << "\n";
        if (type == SourceType::BOOK) {
            cout << "�����: " << author << "\n"
                << "��������: " << category << "\n";
        }
        else {
            cout << "г�: " << year << "\n";
        }
        cout << "-------------------------\n";
    }
};

class Library {
private:
    vector<Source*> sources;

public:
    ~Library() {
        for (auto source : sources) {
            delete source;
        }
    }

    void fillDatabase() {
        int count;
        cout << "������ ������ ������: ";
        cin >> count;
        cin.ignore();
        for (int i = 0; i < count; ++i) {
            addSource();
        }
    }

    void addSource() {
        int typeInput;
        cout << "������ ��� (1 - �����, 2 - ������, 3 - ������): ";
        cin >> typeInput;
        cin.ignore();

        SourceType type = static_cast<SourceType>(typeInput - 1);
        string title, author, category;
        int year = 0;

        cout << "������ �����: ";
        getline(cin, title);

        if (type == SourceType::BOOK) {
            cout << "������ ������: ";
            getline(cin, author);
            cout << "������ �������� (����������, �������� ����): ";
            getline(cin, category);
        }
        else {
            cout << "������ ��: ";
            cin >> year;
            cin.ignore();
        }

        sources.push_back(new Source(type, title, author, category, year));
        cout << "������� ������ �� ����.\n";
    }

    void displayAll() const {
        if (sources.empty()) {
            cout << "���� ����� �������.\n";
            return;
        }
        for (const auto& source : sources) {
            source->display();
        }
    }

    void deleteSource(int index) {
        if (index < 0 || index >= sources.size()) {
            cout << "������� ������.\n";
            return;
        }
        delete sources[index];
        sources.erase(sources.begin() + index);
        cout << "������� ��������.\n";
    }

    void sortSources() {
        sort(sources.begin(), sources.end(), [](Source* a, Source* b) {
            if (a->getType() == b->getType()) {
                return a->getTitle() < b->getTitle();
            }
            return a->getType() < b->getType();
            });
        cout << "������� ����������.\n";
    }

    void searchBook(const string& author, const string& title) const {
        for (const auto& source : sources) {
            if (source->getType() == SourceType::BOOK && source->getAuthor() == author && source->getTitle() == title) {
                source->display();
                return;
            }
        }
        cout << "����� �� ��������.\n";
    }

    void searchMagazineByYear(int year) const {
        for (const auto& source : sources) {
            if (source->getType() == SourceType::MAGAZINE && source->getYear() == year) {
                source->display();
                return;
            }
        }
        cout << "������ �� ��������.\n";
    }

    void filterBooksByAuthor(const string& author) const {
        for (const auto& source : sources) {
            if (source->getType() == SourceType::BOOK && source->getAuthor() == author) {
                source->display();
            }
        }
    }

    void removeNewspapersByYear(int year) {
        sources.erase(remove_if(sources.begin(), sources.end(), [&](Source* source) {
            if (source->getType() == SourceType::NEWSPAPER && source->getYear() == year) {
                delete source;
                return true;
            }
            return false;
            }), sources.end());
        cout << "������ �� " << year << " �� ��������.\n";
    }
};

int main() {
    Library library;
    int choice;

    while (true) {
        cout << "\n����:\n"
            << "1. ��������� ���� �����\n"
            << "2. ����������� �� �������\n"
            << "3. ������ �������\n"
            << "4. �������� �������\n"
            << "5. ��������� �������\n"
            << "6. ����� �����\n"
            << "7. ����� ������� �� �����\n"
            << "8. Գ�������� ���� �� �������\n"
            << "9. �������� ������ �� �����\n"
            << "0. �����\n"
            << "��� ����: ";
        cin >> choice;

        switch (choice) {
        case 1: library.fillDatabase(); break;
        case 2: library.displayAll(); break;
        case 3: library.addSource(); break;
        case 4: {
            int index;
            cout << "������ ������ ��� ���������: ";
            cin >> index;
            library.deleteSource(index);
            break;
        }
        case 5: library.sortSources(); break;
        case 6: {
            string author, title;
            cin.ignore();
            cout << "������ ������: ";
            getline(cin, author);
            cout << "������ �����: ";
            getline(cin, title);
            library.searchBook(author, title);
            break;
        }
        case 7: {
            int year;
            cout << "������ ��: ";
            cin >> year;
            library.searchMagazineByYear(year);
            break;
        }
        case 8: {
            string author;
            cin.ignore();
            cout << "������ ������: ";
            getline(cin, author);
            library.filterBooksByAuthor(author);
            break;
        }
        case 9: {
            int year;
            cout << "������ ��: ";
            cin >> year;
            library.removeNewspapersByYear(year);
            break;
        }
        case 0: return 0;
        default: cout << "������� ����.\n";
        }
    }
}