#include "lisp.h"

typedef float (*Raw_fun)(float, float) ;

class NumericOperation:public Object{
   public:
   	std::string str;
       Raw_fun raw_fun;
       float (*fun)(float, float);
   	 
       NumericOperation(std::string name,Raw_fun raw_fun) 
       : Object(name){
         this->raw_fun=raw_fun;
   	 }

       Object * call(Object * args,Envir envir){
         float value=0; 
         Object * left= (*args->objects.begin());
         Object * right= (*args->objects.end());
         if(left->type==ObjectType::number_type &&
            right->type==ObjectType::number_type ){
            value=this->raw_fun(left->number,right->number);  
         }
         Object * result=new Object(value);
         return result;
       }
};

float raw_mult(float x,float y){
   return x*y;
}

float raw_add(float x,float y){
   return x+y;
}