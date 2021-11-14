#ifndef STAGE_H
#define STAGE_H

#define BASE 10

#define A_WIN 1
#define B_WIN 2
#define TIE   3
#define PROCESSING 4

#define A_TURN 0
#define B_TURN 1

#define LEFT_ADD_LEFT 0
#define LEFT_ADD_RIGHT 1
#define RIGHT_ADD_LEFT 2
#define RIGHT_ADD_RIGHT 3

typedef struct {
    int a1, a2, b1, b2, round;
} stage;

int hash(const stage* s);
stage add(const stage* s, int type);
int status(const stage* s);
int dfs(const stage* s);
#endif