#!/usr/bin/env python3

# Script written by J.-B. Camps

import sys
import random

if __name__ == '__main__':

    train = open("train.txt", "w")
    val = open("val.txt", "w")
    test = open("test.txt", "w")

    random.seed('1214')

    for i in sys.argv[1:]:
        monRand = random.random()
        if monRand <= 0.1:
            test.write(i+"\n")
        elif 0.1 < monRand <= 0.2:
            val.write(i+"\n")
        else:
            train.write(i+"\n")

    test.close()
    val.close()
    train.close()
