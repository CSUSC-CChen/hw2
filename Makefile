CXX=g++
CXXFLAGS=-g -Wall -std=c++11
# Uncomment for parser DEBUG
#DEFS=-DDEBUG

OBJS=amazon.o Book.o Clothing.o Movie.o mydatastore.o user.o db_parser.o product.o product_parser.o util.o

all: amazon

amazon: $(OBJS)
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ $(OBJS)

amazon.o: amazon.cpp db_parser.h datastore.h product_parser.h mydatastore.h util.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c amazon.cpp
mydatastore.o: mydatastore.cpp mydatastore.h datastore.h product.h user.h util.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c mydatastore.cpp
Book.o: Book.cpp Book.h product.h util.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c Book.cpp
Clothing.o: Clothing.cpp Clothing.h product.h util.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c Clothing.cpp
Movie.o: Movie.cpp Movie.h product.h util.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c Movie.cpp
user.o: user.cpp user.h 
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c user.cpp
db_parser.o: db_parser.cpp db_parser.h product.h product_parser.h user.h datastore.h 
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c db_parser.cpp
product.o: product.cpp product.h 
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c product.cpp
product_parser.o: product_parser.cpp product_parser.h product.h 
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c product_parser.cpp
util.o: util.cpp util.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c util.cpp


clean:
	rm -f *.o amazon
