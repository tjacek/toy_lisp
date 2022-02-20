#include <string>
#include <iostream>
#include <regex>
#include <list>
#ifndef CALC
#define CALC

class Calculator{
  std::list<double> stack;
  public:
    void push(double value);
    double apply(std::string operation);
    double peek();
};

double reverse_polish(std::string);

#endif