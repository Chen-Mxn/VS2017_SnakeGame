#pragma once
#ifndef __SNAKE__H
#define __SNAKE__H

/*---------------头文件---------------*/
#include <stdio.h>			//标准输入输出
#include <easyx.h>			//图形界面(graphics.h)
#include <conio.h>			//键盘交互
#include <time.h>			//随机数种子使用
#include <mmsystem.h>		//多媒体设备接口头文件
#pragma comment(lib, "winmm.lib")	//播放音乐库文件	


/*---------------宏定义----------------*/
#define SnakeMaxLenth 100	//蛇的最大长度
#define SnakeMaxSpeed 50
//	方向键的虚拟键值
#define	INPUT_UP 72
#define	INPUT_DOWN 80
#define INPUT_LEFT 75
#define	INPUT_RIGHT 77
#define INPUT_PAUSE 32


/*---------------结构体----------------*/
//	表示坐标
typedef struct Point
{
	int x;
	int y;
}point;

//	蛇的属性
typedef struct Snake
{
	int lenth;						//蛇的节数
	point xy[SnakeMaxLenth];		//蛇最大长度
	char direct;					//标记方向
	int speed;						//蛇的速度
	int color[3] = {88, 88, 88};	//蛇的颜色
}Snake;

//	食物的属性
typedef struct Food
{
	point foodxy;	//食物坐标
	int flag;		//食物存在标志
	int grade;		//分数
}Food;

//	把蛇的方向判断枚举
enum SnakeDirection { right, left, up, down, pause };



/*------功能函数（模块化设计）--------*/
void GameInit();			//游戏初始化
void GameMenu();			//游戏菜单界面
void GameStart();			//开始游戏
void GameSettint();			//游戏设置
void GameOver();			//游戏结束
void ModeChoose();			//模式选择
void ShowMessage();			//显示信息
void CreateMap();			//创建地图

void SnakeInit();			//初始化蛇
void SnakeDraw();			//图形化蛇
void SnakeMove();			//蛇的移动
void KeyInput();			//键盘交互

void FoodInit();			//初始化食物
void FoodDraw();			//图形化食物
void EatFood();				//吃食物

void IfHitWall();			//判断撞墙


#endif