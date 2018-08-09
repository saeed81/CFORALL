#!/bin/bash

gcc -O2 -std=c99 -Wall -pedantic $1 -o main.x
#icc  -O2 -parallel -std=c99 $1 -o main.x
