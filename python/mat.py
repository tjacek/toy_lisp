import re

def tokenize(in_path):
    with open(in_path) as txt_file:
        lines= txt_file.read().split('\n')
        lines=[line_i.split()  for line_i in lines]
        print(lines)

in_path="../C/test.math"
tokenize(in_path)