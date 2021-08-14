#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#define WIDE 60 //地图宽
#define HIGH 20 //地图高

typedef struct _body //蛇身一块的坐标信息
{
    int x;
    int y;
} BODY;

typedef struct snake //蛇的信息
{
    int size;
    BODY list[WIDE * HIGH]; //蛇身坐标
    BODY food;              //当前食物的坐标
    COORD coord;            //光标位置
    BODY tail;              //原本蛇尾的坐标
    int dx;                 //蛇的移动方向，默认向右
    int dy;
} SNAKE;

void hide_cur();                    //终端窗口隐藏光标
void init_snake(SNAKE *snake);      //初始化蛇的信息
void init_food(SNAKE *snake);       //随机生成食物位置
void init_wall();                   //初始化墙
void show_ui(SNAKE *snake);         //显示蛇、食物
void start_game(SNAKE *snake);      //开始游戏
void move_snake(SNAKE *snake);      //根据按键改变蛇坐标信息
void snake_direction(SNAKE *snake); //根据按键改变蛇的移动方向
void eat_food(SNAKE *snake);        //蛇是否碰到食物
int eat_self(SNAKE *snake);         //判断蛇是否吃到自己，吃到返回 1，否则 0
void game_over(SNAKE *snake);       //游戏结束