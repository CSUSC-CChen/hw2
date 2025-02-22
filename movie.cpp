#include "movie.h"
#include "util.h"
#include <sstream>

movie::movie(const std::string& name, double price, int qty, const std::string& genre, const std::string& rating)
    : Product("movie", name, price, qty), genre_(genre), rating_(rating) {}
std::set<std::string> movie::keywords() const {
    std::set<std::string> keys = parseStringToWords(name_);
    std::set<std::string> genreWords = parseStringToWords(genre_);
    std::set<std::string> ratingWords = parseStringToWords(rating_);
    keys.insert(genreWords.begin(), genreWords.end());
    keys.insert(ratingWords.begin(), ratingWords.end());
    return keys;
}
std::string movie::displayString() const {
    std::ostringstream oss;
    oss << name_ << "\n";
    oss << "Genre: " << genre_ << " Rating: " << rating_ << "\n";
    oss << price_ << " " << qty_ << " left.";
    return oss.str();
}
void movie::dump(std::ostream& os) const {
    os << "movie\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << std::endl;
}