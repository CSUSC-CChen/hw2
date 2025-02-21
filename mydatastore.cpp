//
// Created by Leo on 2/20/25.
//

#include "mydatastore.h"
#include <iostream>

MyDataStore::MyDataStore() {}
MyDataStore::~MyDataStore() {
  for (auto p : products_) delete p;
  for (auto u : users_) delete u.second;
}
void MyDataStore::addProduct(Product* p) {
  products_.insert(p);
}
void MyDataStore::addUser(User* u) {
  users_[u->getName()] = u;
}
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
  std::set<Product*> result;
  for (const auto& term : terms){
    for (auto& p : products_) {
      if (p->keywords().count(term)) {
        result.insert(p);
      }
    }
  }
  return std::vector<Product*>(result.begin(), result.end());
}
void MyDataStore::dump(std::ostream& ofile) {
  ofile << "<products>\n";
  for (auto& p : products_) {p->dump(ofile);}
  ofile << "</products>\n<users>\n";
  for (auto& u : users_) {u.second->dump(ofile);}
  ofile << "</users>\n";
}
void MyDataStore::addToCart(const std::string& username, Product* p){
  if (users_.count(username)) {
    carts_[username].push_back(p);
  }
  else {
    std::cout << "Invalid user name" << std::endl;
  }
}
void MyDataStore::viewCart(const std::string& username){
  if (users_.count(username)) {
    for (auto& p : carts_[username]) std::cout << p->displayString() << std::endl;
  }
  else std::cout << "Invalid user name" << std::endl;
}
void MyDataStore::buyCart(const std::string& username){
  if (users_.count(username)) {
    std::vector<Product*>& cart = carts_[username];
    std::vector<Product*>::iterator it = cart.begin();
    while (it != cart.end()) {
      if ((*it)->getQty()>0) {
        (*it)->subtractQty(1);
        it = cart.erase(it);
      }
      else ++it;
    }
  }
  else std::cout << "Invalid user name" << std::endl;
}