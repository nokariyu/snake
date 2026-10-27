#ifndef NSNAKE_H
#define NSNAKE_H

#ifdef __cplusplus
extern "C"{
#endif
  
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>

#define NS_NONE 0
#define NS_UP 1
#define NS_DOWN 2
#define NS_RIGHT 3
#define NS_LEFT 4
#define NS_EMPTY 0
#define NS_APPLE 1
#define NS_SNAKE 2
#define NS_ALIVE 0
#define NS_WIN 1
#define NS_LOSE 2

struct NSver{
  uint8_t val;
  uint8_t direction;
};

typedef struct{
  uint16_t seed;
  uint16_t length;
  uint16_t head_point;
  uint16_t tail_point;
  uint8_t width;
  uint8_t height;
  uint8_t direction;
  uint8_t cant_direction;
  uint8_t apple;
  uint8_t status;
  struct NSver* grid;
} NSengine;

NSengine* nsSet(uint8_t width, uint8_t height);

void nsKill(NSengine* engine);

void nsReset(NSengine* engine);

void nsResize(uint8_t width, uint8_t height, NSengine* engine);

uint8_t nsCheck(NSengine* engine);

uint16_t nsGetRandom(uint16_t* seed);

void nsAddApple(NSengine* engine);

void nsChangeDirection(uint8_t toDirection, NSengine* engine);

void nsMoveTail(NSengine* engine);

uint8_t nsMoveHead(NSengine* engine);

void nsNext(NSengine* engine);

#ifdef __cplusplus
}
#endif

#endif
