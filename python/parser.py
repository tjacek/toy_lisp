import re

def tokenize(raw_str):
    whitespace= r"(\s)+"
    clean_str=re.sub(whitespace," ",raw_str)
    clean_str=clean_str.replace(" (","(").replace(") ",")")
    clean_str=clean_str.replace("("," ( ").replace(")"," )")
    tokens=clean_str.split(" ")
    tokens.pop(0)
    return tokens

print(tokenize("(begin (define r 10)   (* pi (* r r)))"))   