//
// Created by Leo on 2/20/25.
//

#include "mydatastore.h"
#include <iostream>

MyDataStore::MyDataStore() {}
MyDataStore::~MyDataStore() {
  //delete product memory
  for (Product* p : products_)
    delete p;
  //delete user memory
  for (std::pair<const std::string, User*> u : users_)
    delete u.second;
}
void MyDataStore::addProduct(Product* p) {
  products_.insert(p);
}
void MyDataStore::addUser(User* u) {
  users_[u->getName()] = u;
}
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
  std::set<Product*> result;
  if (terms.empty()) {
    return std::vector<Product*>();  // Return an empty vector if no search terms are given
  }
  for (size_t i = 0; i < terms.size(); ++i) {
    std::set<Product*> matchingProducts;
    // Find all products containing the current search term
    for (Product* const& p : products_) {
      if (p->keywords().count(terms[i])) {
        matchingProducts.insert(p);
      }
    }
    // If this is the first term, initialize result with the matching products
    if (i == 0) {
      result = matchingProducts;
    } else {
      if (type == 0) { // AND search
        result = setIntersection(result, matchingProducts);
      } else if (type == 1) { // OR search
        result = setUnion(result, matchingProducts);
      }
    }
  }
  return std::vector<Product*>(result.begin(), result.end());
}
void MyDataStore::dump(std::ostream& ofile) {
  ofile << "<products>\n";
  for (Product* const& p : products_) {
    p->dump(ofile);
  }
  ofile << "</products>\n<users>\n";
  for (std::pair<const std::string, User*>& u : users_) {
    u.second->dump(ofile);
  }
  ofile << "</users>\n";
  // Dump carts to maintain user purchase history
  ofile << "<carts>\n";
  for (const std::pair<const std::string, std::vector<Product*>>& cart : carts_) {
    ofile << cart.first << " ";
    for (Product* const& p : cart.second) {
      ofile << p->getName() << " ";
    }
    ofile << "\n";
  }
  ofile << "</carts>\n";
}
void MyDataStore::addToCart(const std::string& username, Product* p) {
  //check user
  if (users_.find(username) == users_.end()) {
    std::cout << "Invalid username" << std::endl;
    return;
  }
  //wrong product
  if (p == nullptr) {
    std::cout << "Invalid request" << std::endl;
    return;
  }
  carts_[username].push_back(p);
}
void MyDataStore::viewCart(const std::string& username) {
  //check user
  if (users_.find(username) == users_.end()) {
    std::cout << "Invalid username" << std::endl << std::flush;  // Force output immediately
    return;
  }
  //check cart if empty
  if (carts_[username].empty()) {
    std::cout << "Cart is empty" << std::endl;
    return;
  }
  int i = 1;
  for (Product*& p : carts_[username]) {
    std::cout << "Item " << i << ":\n" << p->displayString() << std::endl;
    i++;
  }
}

void MyDataStore::buyCart(const std::string& username) {
  //check user
  std::map<std::string, User*>::iterator userIt = users_.find(username);
  if (userIt == users_.end()) {
    std::cout << "Invalid username" << std::endl;
    return;
  }
  User* user = userIt->second;
  std::vector<Product*>& cart = carts_[username];
  //cart for items user cant afford
  std::vector<Product*> remainingCart;
  //buy what user can afford
  for (std::vector<Product*>::iterator it = cart.begin(); it != cart.end(); ++it) {
    Product* product = *it;
    if (product->getQty() > 0 && user->getBalance() >= product->getPrice()) {
      user->deductAmount(product->getPrice());
      product->subtractQty(1);
    } else {
      remainingCart.push_back(product);  // Keep items the user couldn't afford
    }
  }

  //If the user has insufficient funds, exit without modifying stock
  cart = remainingCart;

  //If nothing was purchased, warn the user
  if (cart.size() == remainingCart.size()) {
    std::cout << "Insufficient funds" << std::endl << std::flush;
  }
}
bool MyDataStore::userExists(const std::string& username) const {
  return users_.find(username) != users_.end();
}