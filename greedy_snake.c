#include "header.h"

int main()
{
    system("cls"); //清屏

    hide_cur(); //终端窗口隐藏光标

    SNAKE *snake = (SNAKE *)malloc(sizeof(SNAKE));
    init_snake(snake); //初始化蛇的信息

    start_game(snake); //开始游戏
    return 0;
}

void hide_cur()
{
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = sizeof(cci);
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}

void init_ui()
{
    for (int i = 0; i < HIGH; i++)
    {
        for (int j = 0; j < WIDE; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}

void init_snake(SNAKE *snake)
{
    //初始化蛇首坐标
    snake->list[0].x = WIDE / 2;
    snake->list[0].y = HIGH / 2;
    //初始化蛇尾坐标
    snake->list[1].x = WIDE / 2 - 1;
    snake->list[1].y = HIGH / 2;
    //初始化蛇身长度
    snake->size = 2;
    //随机生成初始食物位置
    init_food(snake);
    //默认移动方向向右
    snake->dx = 1;
    snake->dy = 0;
}

void init_food(SNAKE *snake)
{
    srand(time(NULL));

    snake->food.x = rand() % (WIDE - 3) + 1; //-2、+1都是防止出界
    snake->food.y = rand() % (HIGH - 3) + 1; //-2、+1都是防止出界
}

void init_wall()
{
    //显示墙
    for (int i = 0; i < HIGH; i++)
    {
        for (int j = 1; j < WIDE + 1; j++)
        {
            if (i == 0 || i == HIGH - 1 || j == 1 || j == WIDE)
                printf("#");
            else
                printf(" ");
        }
        printf("\n");
    }
}

void show_ui(SNAKE *snake)
{
    //显示蛇
    for (int i = 0; i < snake->size; i++)
    {
        if (!snake->list[i].x && !snake->list[i].y)
            return;

        //设置光标位置
        snake->coord.X = snake->list[i].x;
        snake->coord.Y = snake->list[i].y + 1; //加 1是避免和终端窗口中的命令语句重叠
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), snake->coord);

        if (i == 0) //蛇头
        {
            printf("@");
        }
        else //蛇身
        {
            printf("*");
        }
    }

    //清除屏幕上原本蛇尾部分
    snake->coord.X = snake->tail.x;
    snake->coord.Y = snake->tail.y + 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), snake->coord);
    printf(" ");

    //显示食物
    snake->coord.X = snake->food.x;
    snake->coord.Y = snake->food.y + 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), snake->coord);
    printf("+");
}

void start_game(SNAKE *snake)
{
    init_wall(); //初始化墙

    while (snake->list[0].x < WIDE - 1 && snake->list[0].x > 0 && snake->list[0].y < HIGH - 2 && snake->list[0].y > -1) //没撞墙时
    {
        snake_direction(snake); //控制蛇的方向

        move_snake(snake); //更新蛇的坐标

        show_ui(snake); //显示蛇、食物

        eat_food(snake); //蛇是否碰到食物

        if (eat_self(snake)) //判断蛇是否吃到自己
            break;

        Sleep(200); //延时0.2s
    }

    game_over(snake);
}

void snake_direction(SNAKE *snake)
{
    char key = 0;
    while (_kbhit())    //按下按键进入循环
        key = _getch(); //获取按键值
    switch (key)
    {
    case 'w':
        snake->dx = 0;
        snake->dy = -1;
        break;

    case 's':
        snake->dx = 0;
        snake->dy = 1;
        break;
    case 'a':
        snake->dx = -1;
        snake->dy = 0;
        break;
    case 'd':
        snake->dx = 1;
        snake->dy = 0;
        break;
    default:
        break;
    }
}

void move_snake(SNAKE *snake)
{
    //记录原本蛇尾位置
    snake->tail.x = snake->list[snake->size - 1].x;
    snake->tail.y = snake->list[snake->size - 1].y;

    //蛇身位置改变
    for (int i = snake->size - 1; i > 0; i--)
        snake->list[i] = snake->list[i - 1];

    //蛇首位置改变
    snake->list[0].x += snake->dx;
    snake->list[0].y += snake->dy;
}

void game_over(SNAKE *snake)
{
    system("chcp 65001"); //防止终端汉字乱码
    system("cls");        //清屏，美观

    //居中打印结果
    COORD coord;
    coord.X = WIDE / 2 - 10;
    coord.Y = HIGH / 2;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf("游戏结束，得分：%d\n", 10 * (snake->size - 2));

    //美观考虑，移动光标
    coord.X = 0;
    coord.Y = HIGH;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    Sleep(2000); //延时2s
    exit(0);
}

int eat_self(SNAKE *snake)
{
    for (int i = 1; i < snake->size; i++)
        if (snake->list[0].x == snake->list[i].x && snake->list[0].y == snake->list[i].y)
            return 1;

    return 0;
}

void eat_food(SNAKE *snake)
{
    if (snake->list[0].x == snake->food.x && snake->list[0].y == snake->food.y)
    {
        //重新生成初始食物位置
        init_food(snake);

        //蛇身长度加 1
        snake->size++;
    }
}