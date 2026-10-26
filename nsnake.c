#include "nsnake.h"

NSengine* nsSet(uint8_t width, uint8_t height){
    if(width < 4 || height < 4) return NULL;

    NSengine* temp = (NSengine*)malloc(sizeof(NSengine));
    if(temp == NULL) return NULL;

    *temp = (NSengine){
        time(NULL), 2, height/2*width+width/2, width/2-1+height/2*width, width, height,
           NS_RIGHT, NS_LEFT, 1, NS_ALIVE, (struct NSver*)calloc(width*height, sizeof(struct NSver))
    };

    if(temp->grid == NULL) return NULL;

    temp->grid[temp->head_point].val = NS_SNAKE;
    temp->grid[temp->tail_point].val = NS_SNAKE;
    temp->grid[temp->tail_point].direction = NS_RIGHT;
    return temp;
}

void nsKill(NSengine* engine){
    if(engine == NULL) return;
    free(engine->grid);
    free(engine);
    engine = NULL;
}

void nsReset(NSengine* engine){
    if(engine == NULL) return;
    engine->direction = NS_RIGHT;
    engine->cant_direction = NS_LEFT;
    engine->length = 2;
    engine->apple = 1;
    engine->status = NS_ALIVE;
    memset(engine->grid, 0, engine->width*engine->height*sizeof(struct NSver));
    engine->grid[engine->head_point].val = NS_SNAKE;
    engine->grid[engine->tail_point].val = NS_SNAKE;
    engine->grid[engine->tail_point].direction = NS_RIGHT;
}

void nsResize(uint8_t width, uint8_t height, NSengine* engine){
    if(engine == NULL || width < 4 || height < 4) return;    
    engine->width = width;
    engine->height = height;
    engine->head_point = height/2*width+width/2;
    engine->tail_point = width/2-1+height/2*width;
    nsReset(engine);
}

uint8_t nsCheck(NSengine* engine){ return engine->status; }

uint16_t nsGetRandom(uint16_t* seed){
    if(*seed == 0) *seed = time(NULL);
    *seed += *seed;
    *seed ^= *seed << 10;
    *seed ^= *seed >> 7;
    *seed ^= *seed << 9;
    return *seed;
}

void nsChangeDirection(uint8_t toDirection, NSengine* engine){
    if(toDirection == engine->cant_direction) return;
    engine->direction = toDirection;
}

void nsMoveTail(NSengine* engine){
    uint8_t temp_direction = engine->grid[engine->tail_point].direction;
    engine->grid[engine->tail_point].val = NS_EMPTY;
    engine->grid[engine->tail_point].direction = NS_NONE;
    switch(temp_direction){
        case NS_UP:
            engine->tail_point -= engine->width;
            break;
        case NS_DOWN:
            engine->tail_point += engine->width;
            break;
        case NS_RIGHT:
            engine->tail_point++;
            break;
        case NS_LEFT:
            engine->tail_point--;
            break;
        default: break;
    }
}

uint8_t nsMoveHead(NSengine* engine){
    engine->grid[engine->head_point].direction = engine->direction;
    switch(engine->direction){
        case NS_UP:
            if(engine->head_point < engine->width || engine->grid[engine->head_point-=engine->width].val == NS_SNAKE) return NS_LOSE;
            engine->cant_direction = NS_DOWN;
            break;
        case NS_DOWN:
            if(engine->head_point >= (engine->height-1)*engine->width || engine->grid[engine->head_point+=engine->width].val == NS_SNAKE) return NS_LOSE;
            engine->cant_direction = NS_UP;
            break;
        case NS_RIGHT:
            if(engine->head_point%engine->width == engine->width-1 || engine->grid[++engine->head_point].val == NS_SNAKE) return NS_LOSE;
            engine->cant_direction = NS_LEFT;
            break;
        case NS_LEFT:
            if(!(engine->head_point%engine->width) || engine->grid[--engine->head_point].val == NS_SNAKE) return NS_LOSE;
            engine->cant_direction = NS_RIGHT;
            break;
        default:
            return NS_LOSE;
    }
    if(engine->grid[engine->head_point].val == NS_APPLE){
        engine->length++;
        if(engine->length == engine->width*engine->height) return NS_WIN;
    }else nsMoveTail(engine);
    engine->grid[engine->head_point].val = NS_SNAKE;
    return NS_ALIVE;
}

void nsNext(NSengine* engine){
    if(engine->status == NS_ALIVE){
        engine->status = nsMoveHead(engine);
    }
}
