#[macro_use]
extern crate lazy_static;
use regex::Regex;

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
  current: u32,
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

  fn shift(&mut self)->u32{
    let size:u32=self.tokens.len().try_into().unwrap();
    if self.current<size { 
      self.current+=1
    } 
    self.current
  }

  fn print(&self){
    for token_i in &self.tokens{
      print!("{}:{} ",token_i.get_type(),token_i.data);
    }
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

fn main() {
  let hello = String::from("read miles");
  let tokens = tokenize(hello);
  tokens.print();
}