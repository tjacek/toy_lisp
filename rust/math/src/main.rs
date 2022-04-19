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

fn tokenize(line:String) -> TokenSeq{
  let mut tokens_seq = TokenSeq{
     tokens: Vec::new(),
     current: 0
  };
  let splits = line.split_whitespace().into_iter();
  for split_i in splits {
    let token_i=Token{token_type:TokenType::VAR, 
                      data:String::from(split_i)};
    tokens_seq.tokens.push(token_i);
    println!("\"{}\"", split_i);
  }
  tokens_seq
}

fn main() {
  let hello = String::from("read miles");

  tokenize(hello);
}