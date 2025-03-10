#ifndef BOOK_H
#define BOOK_H
#include "product.h"

class book : public Product {
  public:
      book(const std::string& name, const std::string& isbn, const std::string& author, double price, int qty);
      std::set<std::string> keywords() const override;
      std::string displayString() const override;
      void dump(std::ostream& os) const override;
  private:
    std::string isbn_, author_;
};

#endif //BOOK_H
