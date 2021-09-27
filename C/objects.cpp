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

NumberObject::NumberObject(float value){
//  this->type=ObjectType::number_type;
  this->value=value;
}

std::string NumberObject::to_str(){
   return std::to_string(this->value);
}

bool NumberObject::to_bool(){
	return this->value!=0;
}

StringObject::StringObject(std::string value){
//  this->type=ObjectType::string_type;
  this->value=value;
}

std::string StringObject::to_str(){
   return this->value;
}