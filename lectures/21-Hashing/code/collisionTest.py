#!/usr/bin/env python

import random
import sys

while 1:
    collisionCount = 0
    for test in range(100):
        bucketChoices = set() 
        for i in range(2500):
            r = random.randint(0,10**6 - 1)
            if r in bucketChoices:
                collisionCount += 1
                break
            else:
                bucketChoices.add(r)
        if test % 10 == 0:
            sys.stdout.write("%d..." % test)
    sys.stdout.write(": %d%%\n" % collisionCount)
