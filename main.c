#include <stdio.h>
#include "stage.h"

int main() {
    stage s;
    int counts[5] = {0};
    for(int i = 1; i < BASE; ++i)
        for(int j = 1; j < BASE; ++j)
            for(int k = 1; k < BASE; ++k)
                for(int l = 1; l < BASE; ++l) {
                    s = (stage){i,j,k,l,0};
                    counts[dfs(&s)]++;
                }
    printf("A Win:%d\nB Win:%d\nTie:%d", counts[1], counts[2], counts[3]);
    return 0;
}
