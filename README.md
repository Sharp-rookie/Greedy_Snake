### 贪吃蛇1.0

##### 规则

​		初始蛇身长为2，向右移动，每吃到一次食物身长加1，积分加10

​		wasd控制移动方向

​		碰到墙壁、障碍物或者吃到自身时死亡，游戏结束

##### 运行方法

​		打开命令行窗口，执行

```_snake
		gcc -o header.h greedy_snake.c greedy
```

​		生成greedy_snake.exe可执行文件

​		运行

```
		./greedy_snake
```

##### 待实现功能

关卡设置，积分达到一定值进入下一关

加入障碍物、巡逻者等
