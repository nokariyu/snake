<h1> Snake Game Engine </h1>

###

Nokariyu Snake(nsnake) is a snake game engine, made with c.
you can use simple function to play the snake.  
<br>

###
<h2> 1. Define </h2>

 ``` c
#define NS_EMPTY 0
```
value of empty cell
``` c
#define NS_APPLE 1
```
value of apple cell
``` c
#define NS_SNAKE 2
```
value of snake cell
``` c
#define NS_NONE 0
```
value of direction none
``` c
#define NS_UP 1
```
value of direction up
``` c
#define NS_DOWN 2
```
value of direction down
``` c
#define NS_RIGHT 3
```
value of direction right
``` c
#define NS_LEFT 4
```
value of direction left
``` c
#define NS_ALIVE 0
```
value of game condition still alive
``` c
#define NS_WIN 1
```
value of game condition win
``` c
#define NS_LOSE 2
```
value of game condition lose

<h2> 2. Structs </h2>
<h3> 1. NSver </h3>

``` c
struct NSver{
  uint8_t val;
  uint8_t direction;
};
```
Noka Snake vertex(NSver) is a struct for storing information about value and direction
if value equals apple or empty, then direction must be none
<br><br>
<h3> 2. NSengine </h3>

```c
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
```

Noka Snake engine(NSengine) is a main struct for storing all game infotmation

 1. seed, is a random seed number
 2. length, is length of the snake
 3. head_point, is a snake head coordinate
 4. tail_point, is a snake tail coordinate
 5. width, is width of the grid or 
