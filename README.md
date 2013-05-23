# Tic-tac-toe

## Description

Compact implementation of the famous game, done in C.

## Compilation
```bash
cc -Wall -o tictactoe tictactoe.c
```

## How to play

On each turn, the player must type the cell they want to play.
The cells are identified by numbers from 0 to 8, according to the following
layout:
```
876
543
210
```
## Current display:
```
4
...
.X.
...

8
O..
.X.
...

1
O..
.X.
.X.

7
OO.
.X.
.X.

2
OO.
.X.
XX.

0
OO.
.X.
XXO

6
OOX
.X.
XXO

Winner is p1

```

## TODO

If more than one char is typed, ignore them.
