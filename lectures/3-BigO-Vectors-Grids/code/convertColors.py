#!/usr/bin/env python

# converts colors pasted from www.coulorlovers.com

# read in a string that looks like this:
# #655643,#80BCA3,#F6F7BD,#E6AC27,#BF4D28,#655643,#80BCA3,#F6F7BD
colorStr = raw_input()
colors = colorStr.split(',')
for color in colors:
    print('colors.add(convertColorToRGB("'+color+'"));')

