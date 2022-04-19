#[macro_use]
extern crate lazy_static;
use regex::Regex;

enum TokenType{
  SYNTAX,
  NUMBER,
  VAR,
}    

struct Token{
  token_type:TokenType,
  data:String,
}

struct TokenSeq {
  tokens: Vec<Token>,
  current: u32,
}

impl TokenSeq {
  fn print(&self){
    for token_i in &self.tokens{
      print!("{} ",token_i.data);
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
    let mut type_i:TokenType=TokenType::VAR;
    if NUMBER_RE.is_match(split_i){
      type_i=TokenType::NUMBER;
    }else if SYNTAX_RE.is_match(split_i){
      type_i=TokenType::SYNTAX;
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