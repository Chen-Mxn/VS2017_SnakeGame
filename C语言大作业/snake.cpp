#include "snake.h"

Snake snake;	//声明蛇
Food food;		//声明食物
int Pflag = 0;	//暂停键
int Bite = 0;	//咬到自己
					//目的是为了刷新提示语（强调咬到自己而不是因为撞墙）

//	游戏初始化
void GameInit()
{
	srand((unsigned int)time(NULL));
	mciSendString("open 菜单BGM.mp3", 0, 0, 0);	//菜单BGM
	mciSendString("play 菜单BGM.mp3 repeat", 0, 0, 0);
	initgraph(800, 600);
	setbkcolor(RGB(46, 33, 33));	//背景色
	cleardevice();	//清屏
	ModeChoose();
	CreateMap();
}

//	菜单界面
void GameMenu()
{
	char gname[] = "贪吃蛇";
	char choice[2][50] = { "1.开始游戏", "2.游戏设置(未完成)" };
	settextstyle(80, 0, "华文琥珀");
	settextcolor(COLORREF RGB(134, 235, 246));
	outtextxy(280, 125, gname);
	settextstyle(25, 0, "宋体");
	settextcolor(COLORREF RGB(205, 179, 107));
	outtextxy(220, 550, "温馨提示: 只能使用英文输入法哦");
	settextcolor(COLORREF RGB(144, 236, 194));
	//outtextxy(320, 285, "按任意键开始");
	outtextxy(250, 285, choice[0]);
	outtextxy(400, 285, choice[1]);
	outtextxy(330, 350, "[游戏说明]");
	outtextxy(320, 380, "w键;向上移动");
	outtextxy(320, 410, "s键;向下移动");
	outtextxy(320, 440, "a键;向左移动");
	outtextxy(320, 470, "d键;向右移动");
}

//	开始游戏
void GameStart()
{
	mciSendString("open BGM.mp3 alias BGM", 0, 0, 0);	//打开BGM
	mciSendString("play BGM repeat", 0, 0, 0);			//播放BGM
	SnakeInit();	//初始化蛇
	while (1)
	{
		cleardevice();	//刷新帧
		CreateMap();	//绘制地图
		SnakeDraw();	//图形化蛇
		FoodDraw();		//图形化食物
		ShowMessage();	//显示信息
		if (_kbhit()) {
			KeyInput();		//按键交互
		}
		SnakeMove();	//蛇的移动
		if (food.flag == 0) {
			FoodInit();	//初始化食物
		}
		Sleep(snake.speed);
		EatFood();		//吃到食物判断
		IfHitWall();	//判断是否撞墙
	}
}

//	 游戏设置
void GameSetting()
{
	int speed;
	scanf_s("%d", &speed);

}

//	创建地图
void CreateMap()
{
	//绘画地图
	setlinecolor(COLORREF RGB(253, 236, 166));	//设置线条颜色
	rectangle(90, 90, 510, 520);	//画矩形（边框）
	rectangle(100, 100, 500, 510);	//双层边框
}

//	模式选择
void ModeChoose()
{
	char mode;
	GameMenu();
	mode = _getch();	
	/*-------此处可进行功能扩展---------*/
	mciSendString("stop 菜单BGM.mp3", 0, 0, 0);
	switch (mode) {
	case '1':
		GameStart(); break;
	case '2':
		GameSetting(); break;
	//case '3':
		//无边框模式...
	//case '4': 
		//地图改变.（增加障碍物、增加食物数量和种类，加速果实，减速果实，掉血果实）
	}
}

//	显示信息
void ShowMessage()
{
	char player_grade[] = "当前分数";
	char player_speed[] = "移动速度";
	char grades[100];
	char speed[50];
	sprintf_s(grades, "%d", food.grade);
	sprintf_s(speed, "%d", snake.speed);
	outtextxy(530, 100, player_grade);	//在右上角界面显示分数
	outtextxy(530, 400, player_speed);	//在右下角界面显示速度
	outtextxy(530, 200, "操作说明");
	outtextxy(530, 225, "w,s,a,d移动");
	outtextxy(530, 250, "按空格键暂停");
	outtextxy(530, 275, "按任意键继续");
	outtextxy(635, 100, grades);
	outtextxy(635, 400, speed);
}

//	初始化蛇
void SnakeInit()
{
	//初始长度：3节
	snake.xy[2].x = 100;
	snake.xy[2].y = 100;

	snake.xy[1].x = 110;
	snake.xy[1].y = 100;

	snake.xy[0].x = 120;
	snake.xy[0].y = 100;

	snake.lenth = 3;
	snake.direct = right;
	snake.speed = 200;
}

//	图形化蛇
void SnakeDraw()
{
	int i;
	for (i = 0; i < snake.lenth; i++) {
		setlinecolor(BLACK);
		setfillcolor(COLORREF RGB(snake.color[0], snake.color[1], snake.color[2]));
		//  填充矩形（蛇的每一节）
		fillrectangle(snake.xy[i].x, snake.xy[i].y, snake.xy[i].x + 10, snake.xy[i].y + 10);
	}
}

//	蛇的移动
void SnakeMove()
{
	int i, j;
	//除了第一节外,后一节蛇身的坐标是前一节的坐标
	//蛇身移动原理：替换
	for (i = snake.lenth - 1; i > 0; i--)
	{
		snake.xy[i].x = snake.xy[i - 1].x;
		snake.xy[i].y = snake.xy[i - 1].y;
	}
	//蛇头运动方向,根据方向标志来移动
	switch (snake.direct)
	{
		case up:
			snake.xy[0].y -= 10;break;
		case down:
			snake.xy[0].y += 10;break;
		case right:
			snake.xy[0].x += 10;break;
		case left:
			snake.xy[0].x -= 10;break;
		case pause:
			while (_getch() != INPUT_PAUSE);
			Pflag = 0;  break;
	}
	//判断蛇撞到自己时
	//当蛇头坐标等于蛇身时,撞到自己
	for (j = 2; j < snake.lenth; j++)
	{
		if (snake.xy[0].x == snake.xy[j].x && snake.xy[0].y == snake.xy[j].y) {
			mciSendString("open 咬.mp3 from 0", 0, 0, 0);	//咬到自己音效
			mciSendString("play 咬.mp3", 0, 0, 0);
			Bite = 1;	//标记死亡原因：咬到自己而不是撞墙
			GameOver();
		}
	}
}

//	按键交互
void KeyInput()
{
	//读取键值
	char key = _getch();
	//键值对应操作
	switch (key)
	{
		case INPUT_UP:
		case 'w':
		case 'W':
			//实现蛇的移动逻辑判断,不能往相反的方向移动
			if (snake.direct != down)
				snake.direct = up;
			break;
		case INPUT_DOWN:
		case 's':
		case 'S':
			if (snake.direct != up)
				snake.direct = down;
			break;
		case INPUT_LEFT:
		case 'a':
		case 'A':
			if (snake.direct != right)
				snake.direct = left;
			break;
		case INPUT_RIGHT:
		case 'd':
		case 'D':
			if (snake.direct != left)
				snake.direct = right;
			break;
		case INPUT_PAUSE:
			if (!Pflag) {
				snake.direct = pause;
				Pflag = 1;
			}
			break;
	}
}

//	初始化食物
void FoodInit()
{
	int i;
	//	随机产生
	food.foodxy.x = (rand() % 40 + 10) * 10;	//[100, 490]
	food.foodxy.y = (rand() % 41 + 10) * 10;	//[100, 500]
	//食物不与蛇身重叠
	for (i = 0; i < snake.lenth; i++)
	{
		if (food.foodxy.x == snake.xy[i].x && food.foodxy.y == snake.xy[i].y)
		{
			food.foodxy.x = (rand() % 40 + 10) * 10;	//[100, 490]
			food.foodxy.y = (rand() % 41 + 10) * 10;	//[100, 500]
		}
	}
	//	食物存在
	food.flag = 1;
}

//	图形化食物
void FoodDraw()
{
	setfillcolor(COLORREF RGB(rand() % 255, rand() % 255, rand() % 255));
	//	非填充圆
	solidcircle(food.foodxy.x + 5, food.foodxy.y + 5, 5);
}

//	判断吃食物
void EatFood()
{
	//	原理：蛇头碰到食物
	if (snake.xy[0].x == food.foodxy.x && snake.xy[0].y == food.foodxy.y)
	{
		mciSendString("open start.mp3 from 0", 0, 0, 0);	//吃到食物音效
		mciSendString("play start.mp3", 0, 0, 0);
		snake.color[0] = rand() % 255;
		snake.color[1] = rand() % 255;
		snake.color[2] = rand() % 255;
		snake.lenth++;
		food.grade += 10;
		food.flag = 0;
		if(snake.speed > SnakeMaxSpeed){
			snake.speed -= 10;
		}
	}
}

//	判断蛇是否撞墙
void IfHitWall()
{
	if (snake.xy[0].x > 490 || snake.xy[0].x < 100 || snake.xy[0].y > 500 || snake.xy[0].y < 100)
	{
		//mciSendString("pause BGM", 0, 0, 0);	//暂停BGM
		mciSendString("open boom.mp3 from 0", 0, 0, 0);	//撞墙音效
		mciSendString("play boom.mp3", 0, 0, 0);
		GameOver();		//撞墙时,游戏结束
	}
}

//	游戏结束
void GameOver()
{
	char endWall[] = "撞到墙啦，别灰心，";
	char endBite[] = "咬到自己啦，别灰心，";
	char end1[] = "也许下一次能做的更好。";
	char tips[] = "按任意键继续";
	settextstyle(25, 0, "宋体");
	outtextxy(530, 200, endWall);
	if (Bite)outtextxy(530, 200, endBite);
	outtextxy(530, 250, tips);
	outtextxy(530, 225, end1);
	_getch();
	cleardevice();
	mciSendString("pause BGM", 0, 0, 0);	//暂停BGM
	mciSendString("open gameover.mp3 from 0", 0, 0, 0);	//撞墙音效
	mciSendString("play gameover.mp3 repeat", 0, 0, 0);
	char choose;
	char End[] = "GAME OVER";
	char goon[] = "按y开始下一局";
	char gexit[] = "按其他任意键退出";
	settextstyle(60, 0, "华文琥珀");
	settextcolor(COLORREF RGB(134, 235, 246));
	outtextxy(260, 125, End);
	settextstyle(25, 0, "宋体");
	outtextxy(330, 200, goon);
	outtextxy(320, 250, gexit);
	settextcolor(COLORREF RGB(144, 236, 194));
	choose = _getch();
	switch (choose)
	{
		case 'y':
		case 'Y':
			mciSendString("stop gameover.mp3", 0, 0, 0);
			mciSendString("play BGM from 0", 0, 0, 0);	//播放BGM
			GameStart(); break;
		case 'n':
		case 'N':
			exit(0); break;
	}
	exit(0);
}
