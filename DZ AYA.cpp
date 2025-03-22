#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <set>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Book {
public:
    string author;
    string title;
    string publisher;
    int year;
    int pages;

    Book() : author(""), title(""), publisher(""), year(0), pages(0) {}
    Book(const string& m_author, const string& m_title, const string& m_publisher, int m_year, int m_pages)
        : author(m_author), title(m_title), publisher(m_publisher), year(m_year), pages(m_pages) {}

    Book(const Book& other) = default;

    Book& operator=(const Book& other) = default;

    friend ostream& operator<<(ostream& os, const Book& book) {
        os << "Author: " << book.author << ", Title: " << book.title
            << ", Publisher: " << book.publisher << ", Year: " << book.year
            << ", Pages: " << book.pages;
        return os;
    }

    bool operator<(const Book& other) const {
        return author < other.author;
    }

    bool operator==(const Book& other) const {
        return author == other.author && title == other.title && publisher == other.publisher && year == other.year && pages == other.pages;
    }
};

struct BookHash {
    size_t operator()(const Book& book) const {
        return hash<string>()(book.author) ^ hash<string>()(book.title) ^ hash<string>()(book.publisher) ^ hash<int>()(book.year) ^ hash<int>()(book.pages);
    }
};

int main() {
    list<Book> booksList;
    vector<Book> booksVector;
    set<Book> booksSet;
    unordered_set<Book, BookHash> booksUnorderedSet;

    ifstream inputFile("input.txt");
    string author, title, publisher;
    int year, pages;

    while (inputFile >> author >> title >> publisher >> year >> pages) {
        Book book(author, title, publisher, year, pages);
        booksList.emplace_back(book);
        booksSet.insert(book);
        booksUnorderedSet.insert(book);
    }
    inputFile.close();

    ofstream outputFile("output.txt");
    outputFile << "Original list:\n";
    for (const auto& book : booksList) {
        outputFile << book << "\n";
    }

    booksList.sort();

    outputFile << "\nSorted list:\n";
    for (const auto& book : booksList) {
        outputFile << book << "\n";
    }

    copy(booksList.begin(), booksList.end(), back_inserter(booksVector));

    outputFile << "\nCopied vector:\n";
    for (const auto& book : booksVector) {
        outputFile << book << "\n";
    }

    outputFile << "\nSet:\n";
    for (const auto& book : booksSet) {
        outputFile << book << "\n";
    }

    outputFile << "\nUnordered Set:\n";
    for (const auto& book : booksUnorderedSet) {
        outputFile << book << "\n";
    }

    outputFile.close();
    return 0;
}