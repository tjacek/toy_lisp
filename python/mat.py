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
        if(self.current<len(self)-1):
            self.current+=1
        return self.peek()

    def next_token_is(self,types):
        token=self.peek()
        is_type=[token.type==type_i 
                for type_i in types]
        return any(is_type)
 
    def except_token(self,types):
        token=self.peek()
        if( not self.next_token_is(types)):
            raise Exception("Parse error")
        self.shift()
        return token

class ASTNode(object):
    def __init__(self,node_type,left,right):
        self.type=node_type 
        self.left=left
        self.right=right

    def print(self,s=""):
        print_helper(self.right," "+s)
        print_helper(self.type,s)
        print_helper(self.left," "+s)

def print_helper(obj, s=""):
    if(type(obj)==ASTNode or type(obj)==ASTLeaf):
        obj.print(s)
    if(obj):
        print(s+ str(obj))

class ASTLeaf(object):
    def __init__(self,node_type,var,expr=None):
        self.type=node_type
        self.var=var
        self.expr=expr
    
    def print(self,s=""):
        print(s+self.type)
        print(s+self.var)
        if(self.expr):
            self.expr.print(s)

    def __str__(self):
        return f"{self.type},{self.var}"

def interpret(in_path):
    envir={}
    with open(in_path) as txt_file:
        lines= txt_file.read().split('\n')
        tokens=[tokenize(line_i)  for line_i in lines]
        for raw_i in tokens:
            tree_i=parse_statement(raw_i)
            eval_statement(tree_i,envir)
            print(envir)

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

def parse_statement(tokens):
    token_i=tokens.except_token(['read','set','print'])
    type_i=token_i.type
    if(type_i=="read"):
        return ASTLeaf('read',tokens.peek().value)
    if(type_i=="print"):
        return ASTLeaf('print',tokens.peek().value)
    if(type_i=="set"):
        var_token=tokens.except_token(['var'])
        tokens.except_token(['='])
        expr_i=parse_expr(tokens)
        return ASTLeaf('set',var_token.value,expr=expr_i)

def parse_expr(tokens):
    result=parse_product(tokens)
    while(tokens.next_token_is(['+','-'])):
        type_i=tokens.peek().type
        op_token= tokens.shift()
        result=ASTNode(type_i,result,parse_product(tokens))
    return result
    
def parse_product(tokens):
    result = parse_factor(tokens)
    while(tokens.next_token_is(['*','/'])):
        type_i=tokens.peek().type
        op_token= tokens.shift()
        result=ASTNode(type_i,result,parse_factor(tokens))
    return result

def parse_factor(tokens):
    token_i = tokens.except_token(['number','var','('])
    if( token_i.type=='var' or token_i.type=='number' ):
        return token_i
    if(token_i.type=="("):
        result=parse_expr(tokens)
        tokens.except_token([")"])
        return result

def eval_statement(tree_i,envir:dict):
    if(tree_i.type=="read"):
        var_i=tree_i.var
        envir[var_i]=float(input(var_i))
    if(tree_i.type=="print"):
        var_i=tree_i.var
    if(tree_i.type=="set"):
        var_i=tree_i.var
        envir[var_i]=eval_expr(tree_i.expr,envir)

def eval_expr(tree_i,envir:dict):
    if(tree_i.type=='number'):
        return tree_i.value
    if(tree_i.type=='var'):
        return envir[tree_i.value]
    if(tree_i.type=='*'):
        left=eval_expr(tree_i.left,envir)
        right=eval_expr(tree_i.right,envir)
        return left * right
    if(tree_i.type=='/'):
        return eval_expr(tree_i.left,envir) / eval_expr(tree_i.right,envir)    
    if(tree_i.type=='-'):
        return eval_expr(tree_i.left,envir) - eval_expr(tree_i.right,envir)     
    if(tree_i.type=='+'):
        return eval_expr(tree_i.left,envir) + eval_expr(tree_i.right,envir) 
    return 0
in_path="../C/test.math"
tokens=interpret(in_path)