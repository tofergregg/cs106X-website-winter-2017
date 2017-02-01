#!/usr/bin/env python

import sys

# read in characters
with open('nearLetters.grid','r') as f:
    lines = f.readlines()

lines = [x[:-1] for x in lines]

neighbors = {}
for row,line in enumerate(lines):
    for col,letter in enumerate(line):
        if letter == ' ':
            continue
        neighbors[letter] = ''
        # find neighbors in grid a radius of 2 away horizontally
        # and 1 away vertically
        for x in range(-2,3):
            for y in range(-1,2):
                if x == 0 and y == 0:
                    continue
                checkX = col+x
                checkY = row+y
                if (checkX >= 0 and checkX < len(line)
                        and checkY >=0 and checkY < len(lines)):
                    neighbor = lines[checkY][checkX]
                    if neighbor != ' ':
                        neighbors[letter] += neighbor

mapStr = '{'
for n in neighbors:
    mapStr += n+':"'+neighbors[n]+'", '
# remove last comma and space
mapStr = mapStr[:-2]
mapStr += '}'
print(mapStr)
