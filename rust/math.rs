//use regex::Regex;

struct TokenSeq {
    tokens: Vec<String>,
    current: u32,
}

fn tokenize(line:String) -> TokenSeq{
  let mut tokens_seq = TokenSeq{
     tokens: Vec::new(),
     current: 0
  };
//  let seperator = Regex::new(r"\\s+").expect("Invalid regex");
  let splits = line.split_whitespace().into_iter();
  for split_i in splits {
    tokens_seq.tokens.push(String::from(split_i));
    println!("\"{}\"", split_i);
  }
  tokens_seq
}

fn main() {
  let hello = String::from("read miles");

  tokenize(hello);
}