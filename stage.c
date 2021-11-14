#include "stage.h"

int all_status[BASE*BASE*BASE*BASE*2];

int hash(const stage* s) {
    return s->round*BASE*BASE*BASE*BASE + s->a1*BASE*BASE*BASE + s->a2*BASE*BASE + s->b1*BASE + s->b2;
}

stage add(const stage* s, int type) {
    switch (s->round) {
        case A_TURN:
            switch (type) {
                case LEFT_ADD_LEFT:
                    return s->a1 == 0 || s->b1 == 0 ? (stage){0,0,0,0,0}
                            : (stage){(s->a1 + s->b1)%10, s->a2, s->b1, s->b2, B_TURN};
                case LEFT_ADD_RIGHT:
                    return s->a1 == 0 || s->b2 == 0? (stage){0,0,0,0,0}
                            : (stage){(s->a1 + s->b2)%10, s->a2, s->b1, s->b2, B_TURN};
                case RIGHT_ADD_LEFT:
                    return s->a2 == 0 || s->b1 == 0? (stage){0,0,0,0,0}
                            : (stage){s->a1, (s->a2 + s->b1)%10, s->b1, s->b2, B_TURN};
                case RIGHT_ADD_RIGHT:
                    return s->a2 == 0 || s->b2 == 0? (stage){0,0,0,0,0}
                            : (stage){s->a1, (s->a2 + s->b2)%10, s->b1, s->b2, B_TURN};
            }
            break;
        case B_TURN:
            switch (type) {
                case LEFT_ADD_LEFT:
                    return s->b1 == 0 || s->a1 == 0? (stage){0,0,0,0,0}
                            : (stage){s->a1, s->a2, (s->b1 + s->a1)%10, s->b2, A_TURN};
                case LEFT_ADD_RIGHT:
                    return s->b1 == 0 || s->a2 == 0? (stage){0,0,0,0,0}
                            : (stage){s->a1, s->a2, (s->b1 + s->a2)%10, s->b2, A_TURN};
                case RIGHT_ADD_LEFT:
                    return s->b2 == 0 || s->a1 == 0?(stage){0,0,0,0,0}
                            : (stage){s->a1, s->a2, s->b1, (s->b2 + s->a1)%10, A_TURN};
                case RIGHT_ADD_RIGHT:
                    return s->b2 == 0 || s->a2 == 0? (stage){0,0,0,0,0}
                            : (stage){s->a1, s->a2, s->b1, (s->b2 + s->a2)%10, A_TURN};
            }
            break;
    }
}

int status(const stage* s) {
    if(s->a1 == s->a2 && s->a1 == 0)
        return A_WIN;
    if(s->b1 == s->b2 && s->b1 == 0)
        return B_WIN;
    return TIE;
}

int check(const stage* s, int type) {
    stage next_stage = add(s, type);
    int res = dfs(&next_stage);
    return res;
}

int dfs(const stage* s) {
    if(all_status[hash(s)] != 0)
        return all_status[hash(s)];
    int res = status(s);
    if(res != TIE)
        return all_status[hash(s)] = res;
    all_status[hash(s)] = PROCESSING;
    int counts[5] = {0};
    stage next_stage = add(s, LEFT_ADD_LEFT);
    if(hash(&next_stage) != 0)
        ++counts[0], ++counts[dfs(&next_stage)];
    next_stage = add(s, LEFT_ADD_RIGHT);
    if(hash(&next_stage) != 0)
        ++counts[0], ++counts[dfs(&next_stage)];
    next_stage = add(s, RIGHT_ADD_LEFT);
    if(hash(&next_stage) != 0)
        ++counts[0], ++counts[dfs(&next_stage)];
    next_stage = add(s, RIGHT_ADD_RIGHT);
    if(hash(&next_stage) != 0)
        ++counts[0], ++counts[dfs(&next_stage)];
    if(counts[0] == counts[PROCESSING])
        return all_status[hash(s)] = TIE;
    if(s->round == A_TURN) {
        if(counts[A_WIN] > 0)
            return all_status[hash(s)] = A_WIN;
        if(counts[TIE] > 0)
            return all_status[hash(s)] = TIE;
        if(counts[B_WIN] == counts[0])
            return all_status[hash(s)] = B_WIN;
    }
    else {
        if(counts[B_WIN] > 0)
            return all_status[hash(s)] = B_WIN;
        if(counts[TIE] > 0)
            return all_status[hash(s)] = TIE;
        if(counts[A_WIN] == counts[0])
            return all_status[hash(s)] = A_WIN;
    }
    return all_status[hash(s)] = TIE;
}
