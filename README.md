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

## Known error

On some system, the winner is set in the first turn.
