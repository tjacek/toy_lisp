import re

def tokenize(raw_str):
    whitespace= r"(\s)+"
    clean_str=re.sub(whitespace," ",raw_str)
    clean_str=clean_str.replace("(","( ").replace(")"," )")
    return clean_str.split(" ")

print(tokenize("(begin (define r 10)   (* pi (* r r)))"))   