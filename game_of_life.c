#include<stdio.h>
#include<stdbool.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>

const int SIZE = 10;

typedef struct {
    bool alive;
    int neighboors;
} c;

bool calcNewC(c c){
    return (c.neighboors == 3) || (c.neighboors == 2 && c.alive);  
}

void initMap(c **cMap){

    //random initial mapping
    srand(time(NULL));
    int ACTIVE_CHANCE = 20;

    for(int i = 0; i < SIZE; ++i){
        for(int j = 0; j < SIZE; ++j){
            int ran = rand() % 100;
            cMap[i][j].alive = (ran < 20) ? true : false;
        }
    }
}

void calcNeighboors(c **cMap){
    for(int i = 0; i < SIZE; ++i){
        for(int j = 0; j < SIZE; ++j){
            //calculate neighboors
            int neighboors = 0;

            for(int k = i - 1; k <= i + 1; ++k){
                for(int l = j - 1; l <= j + 1; ++l){

                    if(k < 0 || k > SIZE - 1)
                        continue;
                    if(l < 0 || l > SIZE - 1)
                        continue;
                    if(k == i && l == j)
                        continue;
                    if(cMap[k][l].alive == true)
                        neighboors++;
                }
            }
            cMap[i][j].neighboors = neighboors;
        }
    }
}

void printMap(c **cMap, bool initial, int iteration){
    if(!initial){
        printf("\033[%dA", SIZE + 3);  
        printf("\033[J");  
    }
    printf(" Generation: %d\n", iteration);
    printf("\u250c");
    for(int i = 0; i < SIZE; i++)
        printf("\u2500\u2500");
    printf("\u2510");  
    printf("\n");
    for(int i = 0; i < SIZE; ++i){
        printf("\u2502");
        for(int j = 0; j < SIZE; ++j){
            if(cMap[i][j].alive)
                printf("\033[47m  \033[0m");
            else 
                printf("  ");
        }
        printf("\u2502");
        printf("\n");
    }
    printf("\u2514");
    for(int i = 0; i < SIZE; i++)
        printf("\u2500\u2500");
    printf("\u2518");
    printf("\n");
}

int main() {
    const int ITERATIONS = 10;
    c **cMap = malloc(SIZE * sizeof(c*));
    for(int i = 0; i < SIZE; i++){
        cMap[i] = malloc(SIZE * sizeof(c));
    }
    initMap(cMap);
    calcNeighboors(cMap);
    printMap(cMap, true, 0);
    sleep(2);

    for(int i = 0; i < ITERATIONS; ++i){
        for(int j = 0; j < SIZE; ++j){
            for(int k = 0; k < SIZE; ++k){
                cMap[j][k].alive = calcNewC(cMap[j][k]);
            }
        }
        calcNeighboors(cMap);
        printMap(cMap, false, i + 1);
        sleep(2);
    }

    return 0;
}
