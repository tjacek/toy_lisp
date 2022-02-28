import re
from collections import namedtuple
from dataclasses import dataclass

Token=namedtuple('Token',['type','value'])

@dataclass
class ASTNode(object):
    def __init__(self,node_type,left,right):
        self.type=node_type 
        self.left=left
        self.right=right

@dataclass
class ASTLeaf(object):
    def __init__(self,node_type,value):
        self.type=node_type
        self.value=value


def interpret(in_path):
    with open(in_path) as txt_file:
        lines= txt_file.read().split('\n')
        tokens=[tokenize(line_i)  for line_i in lines]
        for raw_i in tokens:
            tree_i=parse_statement(raw_i)
            print(tree_i.type)
#        return tokens

def tokenize(line_i):
    tokens=[]
    for raw_i in line_i.split():
        if(re.match(r'-?\d+(?:\.\d*)?', raw_i)):
            tokens.append(Token('number',float(raw_i)))
        elif(re.match(r"[\\+\\-\\*\\/=()]|set|read|print",raw_i)):
            tokens.append(Token('instr',raw_i))
        elif(re.match(r"[a-zA-Z][a-zA-Z0-9]*",raw_i)):
            tokens.append(Token('var',raw_i))
    return tokens

def parse_statement(tokens):
    key_words=set(['read','set','print'])
    if(tokens[0].value in key_words):
        return ASTLeaf(tokens[0].value,'dummy')
    

in_path="../C/test.math"
tokens=interpret(in_path)
