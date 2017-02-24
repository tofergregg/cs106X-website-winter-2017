#!/usr/bin/env python

# calculates the SHA-1 hash of The Declaration of Independence and
# the U.S. Constitution

import hashlib

with open("declaration_of_independence.txt") as f:
        decl = f.read()
        
with open("us_constitution.txt") as f:
        const = f.read()
        
print("The hash of the Declaration of Independence text is:")
print("   0x" + hashlib.sha1(decl).hexdigest())

print("The hash of U.S. Constitution text is:")
print("   0x" + hashlib.sha1(const).hexdigest())
