//
// Created by Leo on 2/18/25.
//

#include "Book.h"
#include "util.h"
#include <sstream>

Book::Book(const std::string& name, const std::string& isbn, const std::string& author, double price, int qty)
    : Product("book", name, price, qty), isbn_(isbn), author_(author) {}

std::set<std::string> Book::keywords() const{
    std::set<std::string> keys = parseStringToWords(name_);
    std::set<std::string> author_keys = parseStringToWords(author_);
    keys.insert(author_keys.begin(), author_keys.end());
    keys.insert(isbn_);
    return keys;
}
std::string Book::displayString() const {
    std::stringstream ss;
    ss << name_ << "\nAuthor: " << author_ << " ISBN: " << isbn_ << "\n"
       << price_ << " " << qty_ << " left.";
    return ss.str();
}
void Book::dump(std::ostream& os) const {
    os << "book\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n"
       << isbn_ << "\n" << author_ << std::endl;
}
