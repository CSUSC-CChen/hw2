//
// Created by Leo on 2/20/25.
//

#ifndef MYDATASTORE_H
#define MYDATASTORE_H


#include <string>
#include <set>
#include <vector>
#include <map>
#include "product.h"
#include "user.h"
#include "datastore.h"
#include "util.h"

class MyDataStore : public DataStore {
  public:
    MyDataStore();
    ~MyDataStore();

    void addProduct(Product* p) override;
    void addUser(User* u) override;
    std::vector<Product*> search(std::vector<std::string>& terms, int type) override;
    void dump(std::ostream& ofile) override;
    void addToCart(const std::string& username, Product* p);
    void viewCart(const std::string& username);
    void buyCart(const std::string& username);
  private:
    std::set<Product*> products_;
    std::map<std::string, User*> users_;
    std::map<std::string,std::vector<Product*> > carts_;
};



#endif //MYDATASTORE_H
