#include <string>
#include <iostream>
#include <regex>
#include <list>
#ifndef CALC
#define CALC

class Calculator{
  std::list<double> stack;
  void push(double value);
  double apply(double value);
};

double reverse_polish(std::string);

#endif