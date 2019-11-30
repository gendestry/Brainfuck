# Brainfuck
#### A simple brainfuck parser and interpreter made in c++.

Example code (x = x * x):
```
temp0[-]
temp1[-]
temp2[-]
x[temp2+temp1+x-]
temp1[
  temp2[x+temp0+temp2-]
  temp0[temp2+temp0-]
  temp1-
]
```
