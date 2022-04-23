#[macro_use]
extern crate lazy_static;
use regex::Regex;
use std::fs::File;
use std::io::{self, prelude::*, BufReader};

enum TokenType{
  Syntax,
  Number,
  Var,
}    

struct Token{
  token_type:TokenType,
  data:String,
}

struct TokenSeq {
  tokens: Vec<Token>,
  current: usize,
}

enum ASTree{
  Leaf {id:String,data:String},
  ASTreeNode {id:String,
              left:Box<ASTree>,
              right:Box<ASTree>},
}

impl Token{
  fn get_type(&self)->&str{
    match &self.token_type {
      TokenType::Syntax => "syntax",
      TokenType::Number => "number",
      TokenType::Var => "var",
    }
  }
}

impl TokenSeq {

//  fn peek(&mut self)->Token{
//    self.tokens[self.current]
//  }

  fn shift(&mut self)->usize{
    if self.current<self.tokens.len() { 
      self.current+=1
    } 
    self.current
  }

  fn print(&self){
    for token_i in &self.tokens{
      print!("{}:{} ",token_i.get_type(),token_i.data);
    }
    println!("");
  }
}

fn tokenize(line:String) -> TokenSeq{
  let mut tokens_seq = TokenSeq{
     tokens: Vec::new(),
     current: 0
  };
  lazy_static! {
    static ref NUMBER_RE: Regex = Regex::new("-?\\d+(\\.\\d+)?").unwrap();
    static ref SYNTAX_RE: Regex = Regex::new("[\\+\\-\\*=()]|set|read|print").unwrap();
  }
  let splits = line.split_whitespace().into_iter();
  for split_i in splits {
    let mut type_i:TokenType=TokenType::Var;
    if NUMBER_RE.is_match(split_i){
      type_i=TokenType::Number;
    }else if SYNTAX_RE.is_match(split_i){
      type_i=TokenType::Syntax;
    }
    let token_i=Token{token_type:type_i, 
                      data:String::from(split_i)};
    tokens_seq.tokens.push(token_i);
  }
  tokens_seq
}

fn parse_statement(tokens:TokenSeq) -> ASTree{
  ASTree::Leaf{id:String::from("NULL"),data:String::from("NULL")}
}

fn interpret(in_path:String){
  let file = File::open(in_path).unwrap();
  let reader = BufReader::new(file);
  for line in reader.lines() {
    let line = line.unwrap();
    let tokens=tokenize(line);
    tokens.print();
  }  
}

fn main() {
  let in_path = String::from("../../C/test.math");
  interpret(in_path);
}