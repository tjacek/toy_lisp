#include "lisp.h"

class Plus:Object{
  public:
    ObjectType type=ObjectType::operator_type;

    Object * call(std::list<Object*> args,Envir envir){
        float value=0; 
    	Object * left= (*args.begin());
    	Object * right= (*args.end());
    	if(left->type==ObjectType::number_type &&
    	   right->type==ObjectType::number_type ){
           value= ((NumberObject*)  right)->value; 
    	}

        Object * result=new NumberObject(value);
        return result;
    }

    std::string to_str(){
   	  return "+";
    }	
};