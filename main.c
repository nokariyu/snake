#include <stdio.h>
#include "nsnake.h"
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>

void setRaw(struct termios* og){
    struct termios raw = *og;
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void resetRaw(struct termios* og){
    tcsetattr(STDIN_FILENO, TCSAFLUSH, og);
}

int press(){
    struct timeval tv = {0, 0};
    fd_set fds;

    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    select(STDIN_FILENO +1, &fds, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &fds);
}

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

void get(int* num){
    if(press())
        *num = getchar();
}    

uint8_t movement(int num){
    switch(num){
        case 97:
            return 4;
        case 100:
            return 3;
        case 115:
            return 2;
        case 119:
            return 1;
        default:
            return 0;
    }
}

int main(){
    struct termios og;
    tcgetattr(STDIN_FILENO, &og);
    setRaw(&og);
    NSengine* engine = nsSet(40, 10);

    int input = 3;
    clock_t last;
    while(nsCheck(engine) == NS_ALIVE){
        last = clock();
        printf("\033[0;0H");
        nsAddApple(engine);
        display(engine);
        get(&input);
        if(input == 119 || input == 97 || input == 115 || input == 100) nsChangeDirection(movement(input), engine);
        nsNext(engine);
        while(clock()-last < 200000) { get(&input); }
    }
    printf("\nyou are %s\n", ((nsCheck(engine) == NS_WIN) ? "win" : "lose"));
    resetRaw(&og);
    return 0;
}
