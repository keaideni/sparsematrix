#!/bin/sh

mkdir block
mkdir result
mkdir trunc
cat>Parameter<<EOF
nmax= 4
D= 200
LatticeSize= 50
gr= 0.1
gcr= 0.1
Jr= 0.1
Jcr= 0.1
EOF