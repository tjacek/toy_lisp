import re
from collections import namedtuple

Token=namedtuple('Token',['type','value'])

class Tokens(list):
    def __init__(self, arg=[]):
        super(Tokens, self).__init__(arg)
        self.current=0

    def peek(self):
        return self[self.current]

    def shift(self):
        self.current+=1

    def except_token(self,symbol)
        if(self.peek().type!=symbol)
            raise Exception("parse excep")
#        if(self[self.current].type!=symbol):
#            raise Exception("Parser Error")

class ASTNode(object):
    def __init__(self,node_type,left,right):
        self.type=node_type 
        self.left=left
        self.right=right

class ASTLeaf(object):
    def __init__(self,node_type,var,expr=None):
        self.type=node_type
        self.var=var
        self.expr=expr
    
    def __str__(self):
        return f"{self.type},{self.var}"

def interpret(in_path):
    with open(in_path) as txt_file:
        lines= txt_file.read().split('\n')
        tokens=[tokenize(line_i)  for line_i in lines]
        for raw_i in tokens:
            tree_i=parse_statement(raw_i)
#            print(tree_i)
#        return tokens

def tokenize(line_i):
    tokens=[]
    for raw_i in line_i.split():
        if(re.match(r'-?\d+(?:\.\d*)?', raw_i)):
            tokens.append(Token('number',float(raw_i)))
        elif(re.match(r"[\\+\\-\\*\\/=()]|set|read|print",raw_i)):
            tokens.append(Token(raw_i,None))
        elif(re.match(r"[a-zA-Z][a-zA-Z0-9]*",raw_i)):
            tokens.append(Token('var',raw_i))
    return Tokens(tokens)

def except_token(i,symbol,tokens):
    if(tokens[i].type!=symbol):
        raise Exception("Parser Error")

def parse_statement(tokens):
    if(tokens[0].type=='set'):
        except_token(1,'var',tokens)
        var=tokens[1].value
        except_token(2,'=',tokens)
        expr=parse_expr(tokens[3:])
        return ASTLeaf('set',tokens[1].value,expr=None)
    if(tokens[0].type=='read'):        
        return ASTLeaf('read',tokens[1].value)    
    if(tokens[0].type=='print'):
        return ASTLeaf('print',tokens[1].value)   

def parse_expr(tokens):
    print("OK")#tokens)

in_path="../C/test.math"
tokens=interpret(in_path)