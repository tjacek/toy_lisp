#include "lisp.h"

Object * Object::eval(Envir envir){
	return this;
}

Object * Object::call(std::list<Object*> args,Envir envir){
  return this;
}

bool Object::to_bool(){
	return true;
}

std::string Object::to_str(){
  return "";
}

NumberObject::NumberObject(float value){
  this->value=value;
}

std::string NumberObject::to_str(){
   return std::to_string(this->value);
}

bool NumberObject::to_bool(){
	return this->value!=0;
}

StringObject::StringObject(std::string value){
  this->value=value;
}

std::string StringObject::to_str(){
  return this->value;
}