import re

def parse(raw_str):
    return syntax_tree(tokenize(raw_str))

def syntax_tree(tokens):
    if len(tokens)==0:
        raise SyntaxError('unexpected EOF while reading')
    next_token=tokens.pop(0)
    if next_token=='(':
        statements=[]
        while tokens[0]!=')':
	        statements.append(syntax_tree(tokens))
        tokens.pop(0)
        return statements
    elif next_token==')':
        raise SyntaxError('unexpected )')
    else:
        return make_atom(next_token)

def make_atom(token):
    try: return int(token) 	
    except ValueError:
        try: return float(token)
        except ValueError:
            return str(token)

def tokenize(raw_str):
    whitespace= r"(\s)+"
    clean_str=re.sub(whitespace," ",raw_str)
    clean_str=clean_str.replace(" (","(").replace(") ",")")
    clean_str=clean_str.replace("("," ( ").replace(")"," )")
    tokens=clean_str.split(" ")
    tokens.pop(0)
    return tokens

print(parse("(begin (define r 10)   (* pi (* r r)))"))