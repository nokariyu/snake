#include <stdio.h>
#include "nsnake.h"


void display(NSengine* engine){
    uint8_t i = 0;
    for(; i < engine->width; i++)
        printf("#");
    printf("##\n");
    for(i = 0; i < engine->height; i++){
        printf("#");
        for(uint8_t j = 0; j < engine->width; j++){
            if(engine->grid[engine->width*i+j].val == NS_APPLE) printf("H");
            else if(engine->grid[engine->width*i+j].val == NS_SNAKE) printf("S");
            else printf(" ");
        }
        printf("#\n");
    }
    for(i = 0; i < engine->width; i++)
        printf("#");
    printf("##\n");
}


int main(){
    NSengine* engine = nsSet(5, 5);

    int input;
    while(nsCheck(engine) == NS_ALIVE){
        system("clear");
        display(engine);
        scanf("%d", &input);
        nsChangeDirection(input, engine);
        nsNext(engine);
    }
    printf("\nyou are %s\n", ((nsCheck(engine) == NS_WIN) ? "win" : "lose"));
    return 0;
}
